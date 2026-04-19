cmake_minimum_required(VERSION 3.16)
project(RestaurantSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/external/SFML-2.6.2/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS system window graphics audio REQUIRED)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(RestaurantSimulator ${SOURCES}
    include/enums/TablesTypesEnum.hpp)

target_include_directories(RestaurantSimulator PRIVATE include)

target_link_libraries(RestaurantSimulator
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)

add_custom_command(TARGET RestaurantSimulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/external/SFML-2.6.2/bin"
    $<TARGET_FILE_DIR:RestaurantSimulator>
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    $<TARGET_FILE_DIR:RestaurantSimulator>/assets)