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

    class Plain : public Cell {
    private:
    public:
        Plain(int x, int y) : Cell(x, y) {
            type = 1;
        }
    };

    class Mountain : public Cell {
    public:
        Mountain(int x, int y) : Cell(x, y) {
            type = 2;
        }
    };

    class Water : public Cell {
    public:
        Water(int x, int y) : Cell(x, y) {
            type = 3;
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
        Cell *C;
        int hp=1000;
        int money;
        Cell *L;
        std::vector<Cell*> Cells_with_enemy;

        void distance();

        void distance_for_plane();

        int where_to_go(int x, int y);

        int where_to_go_for_heavy(int x, int y);

        int where_to_go_for_plane(int x, int y);

    public:
        Map(int x1, int y1);

        [[nodiscard]] std::vector<std::vector<Cell>> get_map() const {
            return Cells;
        }

        void draw() const;

        void go();

        void play();

    };
}
#endif //BIG_PROJECT_DEFENDER_HPP

