cmake_minimum_required(VERSION 3.23)
project(vuilib_cmake)

set(CMAKE_CXX_STANDARD 11)

aux_source_directory(src/core/object DIR_SRCS)
aux_source_directory(src/core/render DIR_SRCS)
aux_source_directory(src/core/signal DIR_SRCS)
aux_source_directory(src/core/uibasic DIR_SRCS)
aux_source_directory(src/core/widget DIR_SRCS)
aux_source_directory(src/core/control DIR_SRCS)
aux_source_directory(src/core/ DIR_SRCS)

aux_source_directory(include/core/object DIR_SRCS)
aux_source_directory(include/core/render DIR_SRCS)
aux_source_directory(include/core/signal DIR_SRCS)
aux_source_directory(include/core/uibasic DIR_SRCS)
aux_source_directory(include/core/widget DIR_SRCS)
aux_source_directory(include/core/ DIR_SRCS)
aux_source_directory(include/core/control DIR_SRCS)

aux_source_directory(. DIR_SRCS)

add_library(vuilib STATIC ${DIR_SRCS})


add_executable(vuilib_cmake main.cpp)
target_link_libraries(vuilib_cmake vuilib)

