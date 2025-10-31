cmake_minimum_required(VERSION 3.15)
project(my_project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Экспортировать compile_commands.json для clangd / cpptools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(GTest REQUIRED)
include(GoogleTest)

# Добавление исполняемого файла
add_executable(figure
    src/figures.h
    src/base.h
    src/point.h
    src/main.cpp
    src/array.h
)

add_executable(test_figure
    test/test_figure.cpp
    src/figures.h
    src/base.h
    src/array.h
)

# Связывание тестов с Google Test
target_link_libraries(test_figure GTest::GTest GTest::Main)

# Добавление тестов в CTest
gtest_discover_tests(test_figure)

# Настройка компилятора
target_compile_features(figure PRIVATE cxx_std_14)
target_compile_options(figure PRIVATE -Wall -Wextra -Wpedantic)
target_compile_features(test_figure PRIVATE cxx_std_14)
target_compile_options(test_figure PRIVATE -Wall -Wextra -Wpedantic)