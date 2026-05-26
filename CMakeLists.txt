cmake_minimum_required(VERSION 3.15)
project(mik64_logger LANGUAGES CXX)
if(NOT TARGET mik64_logger)
    set(LOGGER_SOURCES 
        "cpp/mik64_logger.cpp"
        "cpp/logger_factory.cpp"
        "cpp/file_writer.cpp"
        "cpp/console_writer.cpp"
    )
    add_library(mik64_logger STATIC ${LOGGER_SOURCES})
    add_library(mik64::logger ALIAS mik64_logger)
    target_include_directories(mik64_logger PUBLIC 
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/h>
    )
    target_compile_features(mik64_logger PRIVATE cxx_std_17)
endif()
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    add_executable(mik64_logger_test main.cpp)
    target_link_libraries(mik64_logger_test PRIVATE mik64::logger)
endif()
