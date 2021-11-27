cmake_minimum_required(VERSION 3.20)
project(big_project)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(big_project main.cpp Map/map.cpp Enemys/enemy.cpp Enemys/enemy.hpp Map/map.hpp Defenders/defender.cpp Defenders/defender.hpp Defenders/wall.hpp Defenders/tower.hpp Defenders/tower.cpp Defenders/wall.cpp Enemys/hero.cpp Enemys/hero.hpp Cell/cell.cpp Cell/cell.hpp Cell/castle.cpp Cell/castle.hpp Cell/lair.cpp Cell/lair.hpp)

target_link_libraries(big_project sfml-graphics sfml-audio)