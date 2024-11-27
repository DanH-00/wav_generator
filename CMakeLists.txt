cmake_minimum_required(VERSION 3.30)

project(WavGenerator
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0 IMPORTED_TARGET)

add_executable(${PROJECT_NAME}
    file_writer.cpp
    header_generator.cpp
    main.cpp
    options.cpp
    sine_wave_generator.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE
    PkgConfig::GLIB)
