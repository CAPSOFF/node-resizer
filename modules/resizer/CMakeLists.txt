cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

set(RESIZER_LIB         "libresizer")
set(RESIZER_EXE         "resizer")
set(RESIZER_SRC         ${RESIZER_PATH}/src)

add_library(${RESIZER_LIB})
add_library(resizer::node ALIAS ${RESIZER_LIB})

target_sources(${RESIZER_LIB}
    PUBLIC
        ${RESIZER_SRC}/resizer.cpp
        ${RESIZER_SRC}/base64.cpp
        )

target_include_directories(${RESIZER_LIB}
    PUBLIC
        ${RESIZER_SRC}
        ${OpenCV_INCLUDE_DIRS}
        )

target_link_libraries(${RESIZER_LIB}
    PUBLIC
        ${OpenCV_LIBS}
        -lpthread
        )

# 

add_executable(${RESIZER_EXE})

target_sources(${RESIZER_EXE}
    PUBLIC
        ${RESIZER_SRC}/main.cpp
        )

target_link_libraries(${RESIZER_EXE}
    PUBLIC
        resizer::node
        )