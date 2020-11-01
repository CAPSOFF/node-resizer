cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project( ResizerNode )

find_package( OpenCV REQUIRED )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR}/bin)

set(PARENT_BUILD_DIR                ${PROJECT_BINARY_DIR})
set(PROJECT_PATH                    ${PROJECT_SOURCE_DIR})
set(MODULES_PATH                    ${PROJECT_PATH}/modules)
set(RESIZER_PATH                    ${MODULES_PATH}/resizer)

add_subdirectory(${RESIZER_PATH})