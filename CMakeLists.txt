cmake_minimum_required(VERSION 3.7)

project(Aster)

add_subdirectory(SDL2)

add_executable(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME} PRIVATE sources/main.c sources/init.c sources/input.c sources/draw.c sources/stage.c sources/bullet.c sources/ship.c sources/asteroid.c "sources/font.c")
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2main SDL2-static)

