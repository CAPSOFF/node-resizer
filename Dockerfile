# -- Stage 1
FROM ubuntu:20.04 AS dependencies

WORKDIR /tmp

RUN apt-get -yq update \
    && DEBIAN_FRONTEND=noninteractive apt-get -yq --no-install-recommends install \
    libgtk-3-dev \
    libssl-dev \
    pkg-config \
    net-tools \
    unzip \
    clang \
    nano \
    curl \
    make \
    wget \
    git \
    g++

    
RUN wget --no-check-certificate https://github.com/Kitware/CMake/releases/download/v3.18.4/cmake-3.18.4.tar.gz \
    && tar -xzvf cmake-3.18.4.tar.gz \
    && cd cmake-3.18.4 \
    && ./bootstrap -- -DCMAKE_BUILD_TYPE:STRING=Release \
    && make -j4 --quiet \
    && make install \
    && cd .. \
    && rm -rf cmake-3.18.4*

RUN wget --no-check-certificate https://github.com/opencv/opencv/archive/4.5.0.tar.gz \
    && tar -xzvf 4.5.0.tar.gz \
    && mkdir -p opencv-4.5.0/build \
    && cd opencv-4.5.0 \
    && cmake -H. -B./build \
    && cmake --build ./build --config Release --target all -- -j4 \
    && cmake --build ./build --config Release --target install -- -j4 \
    && cd .. \
    && rm -rf 4.5.0*

RUN git clone -b v3.7.0 --recursive https://github.com/nlohmann/json.git \
    && mkdir -p json/build \
    && cd json \
    && cmake -H. -B./build \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_TESTING=OFF \
    && cmake --build ./build --config Release --target all -- -j4 \
    && cmake --build ./build --config Release --target install -- -j4 \
    && cd .. \
    && rm -rf json

RUN ldconfig

# -- Stage 2
FROM dependencies AS builder

ADD . /app/resizer

WORKDIR /app/resizer

RUN cmake --no-warn-unused-cli \
    -B./build \
    && cmake --build ./build --config Release --target all -- --quiet -j4

RUN ldconfig

# -- Stage 3
FROM ubuntu:20.04 AS final

COPY --from=builder \
    /app/resizer/build/bin/resizer \
    /usr/local/bin/

COPY --from=builder \
    /usr/local/lib/libopencv_imgcodecs.so.4.5 \
    /usr/local/lib/libopencv_imgproc.so.4.5 \
    /usr/local/lib/libopencv_core.so.4.5 \
    /usr/local/lib/

COPY --from=builder \
    /lib/x86_64-linux-gnu/libpthread.so.0 \
    /lib/x86_64-linux-gnu/libstdc++.so.6 \
    /lib/x86_64-linux-gnu/libgcc_s.so.1 \
    /lib/x86_64-linux-gnu/libc.so.6 \
    /lib/x86_64-linux-gnu/libpng16.so.16 \
    /lib/x86_64-linux-gnu/libm.so.6 \
    /lib/x86_64-linux-gnu/libz.so.1 \
    /lib/x86_64-linux-gnu/libdl.so.2 \
    /lib/x86_64-linux-gnu/

RUN ldconfig

WORKDIR /root
