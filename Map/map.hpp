//
// Created by ivan on 03.11.2021.
//

#ifndef BIG_PROJECT_MAP_HPP
#define BIG_PROJECT_MAP_HPP


#include <vector>
#include <queue>
#include "../Defenders/defender.hpp"
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

namespace map1 {

    class Cell {
    protected:
        int type = 0;
        std::pair<int, int> coordinate;
        std::vector<Enemy::Enemies *> en;
        Defend::Defender *defend;
        int distance_from_castle;
        int distance_for_plane;
    public:
        Cell() {
            coordinate = std::make_pair(0, 0);
            distance_from_castle = -1;
            distance_for_plane = -1;
            defend = nullptr;
        }

        Cell(int x, int y) {
            coordinate = std::make_pair(x, y);
            distance_from_castle = -1;
            distance_for_plane = -1;
            defend = nullptr;
        }
        Cell(int x, int y, int t) {
            coordinate = std::make_pair(x, y);
            distance_from_castle = -1;
            distance_for_plane = -1;
            defend = nullptr;
            type=t;
        }

        [[nodiscard]] std::pair<int, int> get_coordinate() const {
            return coordinate;
        }

        [[nodiscard]] int get_type() const {
            return type;
        }

        [[nodiscard]] Defend::Defender *get_defend() const {
            return defend;
        }

        std::vector<Enemy::Enemies *>  get_enemies() {
            return en;
        }

        [[nodiscard]] int get_distance() const {
            return distance_from_castle;
        }

        [[nodiscard]] int get_distance_for_plane() const {
            return distance_for_plane;
        }

        int add_enemy(Enemy::Enemies *x);

        int add_defend(Defend::Defender &x);
        void kill( Enemy::Enemies *x);

        bool change_distance(int x) {
            if (distance_from_castle == -1) {
                distance_from_castle = x + 1;
                return true;
            } else {
                if ((distance_from_castle > (x + 1))) {
                    distance_from_castle = x + 1;
                    return true;
                } else {
                    return false;
                }
            }
        }

        bool change_distance_for_plane(int x) {
            if (distance_for_plane == -1) {
                distance_for_plane = x + 1;
                return true;
            } else {
                if ((distance_for_plane > (x + 1))) {
                    distance_for_plane = x + 1;
                    return true;
                } else {
                    return false;
                }
            }
        }
    };

    class Castle : public Cell {
    private:
    public:
        Castle(int x, int y) : Cell(x, y) {
            type = 4;
            distance_from_castle = 0;
            distance_for_plane = 0;
        }
    };

    class Lair : public Cell {
    public:
        Lair(int x, int y) : Cell(x, y) {
            type = 5;
        }

        void spawn();
    };


    class Map {
    private:
        int max_x;
        int max_y;
        std::vector<std::vector<Cell>> Cells;
        Castle *C;
        int hp;
        int money;
        Lair *L;
        std::vector<Cell*> Cells_with_enemy;
        sf::RenderWindow window;
        void distance();

        void distance_for_plane();

        int where_to_go(int x, int y);

        int where_to_go_for_heavy(int x, int y);

        int where_to_go_for_plane(int x, int y);
        Table<int, std::vector<int>> Tower_Table;
        [[nodiscard]] std::vector<std::vector<Cell>> get_map() const {
            return Cells;
        }
        void draw() ;
        void draw_enemies();
        void go();
        Table<int, std::vector<int>> get_table(){
            return Tower_Table;
        };
    public:
        Map();

        Map(int x1, int y1);

        void resize(int x1, int y1);
        void play();
    };
}
#endif //BIG_PROJECT_MAP_HPP

