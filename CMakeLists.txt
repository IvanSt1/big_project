cmake_minimum_required(VERSION 3.20)
project(big_project)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(big_project main.cpp Map/map.cpp Enemys/enemy.cpp Enemys/enemy.hpp Map/map.hpp Defenders/defender.hpp Defenders/wall.hpp Defenders/tower.hpp Enemys/hero.cpp Enemys/hero.hpp Cell/cell.hpp Cell/lair.cpp Cell/lair.hpp Table/table.hpp)
add_executable(drawing Map/map.cpp Enemys/enemy.cpp Enemys/enemy.hpp Map/map.hpp Defenders/defender.hpp Defenders/wall.hpp Defenders/tower.hpp Enemys/hero.cpp Enemys/hero.hpp Cell/cell.hpp Cell/lair.cpp Cell/lair.hpp Table/table.hpp Map/drawing.cpp)
add_executable(table Table/table.hpp Table/tablec_test.cpp)
target_link_libraries(big_project sfml-graphics sfml-audio)
target_link_libraries(drawing sfml-graphics sfml-audio)