project(Google_test)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Test_run test.cpp ../Map/map.cpp ../Map/map.hpp ../Enemys/enemy.cpp ../Enemys/enemy.hpp ../Defenders/defender.hpp ../Defenders/tower.hpp ../Defenders/wall.hpp ../Cell/cell.hpp ../Cell/lair.cpp ../Cell/lair.hpp)
target_link_libraries(Google_Test_run gtest gtest_main)