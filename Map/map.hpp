
#ifndef BIG_PROJECT_MAP_HPP
#define BIG_PROJECT_MAP_HPP


#include <vector>
#include <queue>
#include "../Defenders/tower.hpp"
#include "../Defenders/wall.hpp"
#include "../Cell/cell.hpp"
#include "../Cell/lair.hpp"
#include <random>
#include <iostream>

namespace map1 {
    class Map {
    private:
        int max_x;
        int max_y;
        std::vector<std::vector<Cell>> Cells;
        Cell *C;
        int hp;
        int money;
        Lair *L;
        std::vector<Enemy::Enemies *> enemies;
        std::vector<Tower *> towers;
        My_table::Table<int, std::vector<int>> Tower_Table;

        void distance();

        void add_enemies(std::vector<Enemy::Enemies *>);

        void distance_for_plane();

        int where_to_go(int x, int y);

        int where_to_go_for_heavy(int x, int y);

        int where_to_go_for_plane(int x, int y);

        void go();

        void towers_atack();

        My_table::Table<int, std::vector<int>> get_table() {
            return Tower_Table;
        };

    public:
        Map();

        std::vector<std::vector<Cell>> get_map() const {
            return Cells;
        }

        int get_max_x() const { return max_x; };

        int get_max_y() const { return max_x; };

        std::vector<Enemy::Enemies *> get_enemies() const { return enemies; };

        Map(int x1, int y1);

        void resize(int x1, int y1);

        std::vector<Tower *>::iterator find(int x, int y);

        void play();

        void play(int n, bool t, bool w, bool u, int x, int y);

        ~Map();

        int get_hp() const { return hp; };

        int get_money() const { return money; };

        std::vector<Tower *> get_towers() const { return towers; };
    };
}
#endif //BIG_PROJECT_MAP_HPP

