cmake_minimum_required(VERSION 3.16)
project(RestaurantSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "${CMAKE_SOURCE_DIR}/external/SFML-2.6.2/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS system window graphics audio REQUIRED)

file(GLOB_RECURSE SOURCES
    src/*.cpp
)

set(RESOURCE_FILES resources.rc)

add_executable(RestaurantSimulator ${SOURCES} ${RESOURCE_FILES})

target_include_directories(RestaurantSimulator PRIVATE include)

target_link_libraries(RestaurantSimulator
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mwindows")

add_custom_command(TARGET RestaurantSimulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/external/SFML-2.6.2/bin"
    $<TARGET_FILE_DIR:RestaurantSimulator>
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    $<TARGET_FILE_DIR:RestaurantSimulator>/assets)