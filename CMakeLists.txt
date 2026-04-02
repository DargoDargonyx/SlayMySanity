cmake_minimum_required(VERSION 3.10)
project(SlayMySanity)

set(CMAKE_C_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

include_directories(
    include
    ${SDL2_INCLUDE_DIRS}
    ${SDL2_TTF_INCLUDE_DIRS}
    ${SDL2_IMAGE_INCLUDE_DIRS}
)

add_executable(
    SlayMySanity
    src/main.c
    src/util/error.c
    src/util/window.c
    src/core/engine.c
    src/core/render.c
    src/core/ui/font.c
    src/core/ui/widget.c
)

target_link_libraries(
    SlayMySanity 
    ${SDL2_LIBRARIES} 
    ${SDL2_TTF_LIBRARIES}
    ${SDL2_IMAGE_LIBRARIES}
)

target_compile_options(
    SlayMySanity
    PRIVATE
    ${SDL2_CFLAGS_OTHER}
    ${SDL2_TTF_CFLAGS_OTHER}
    ${SDL2_IMAGE_CFLAGS_OTHER}
)
