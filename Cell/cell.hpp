//
// Created by ivan on 27.11.2021.
//

#ifndef BIG_PROJECT_CELL_HPP
#define BIG_PROJECT_CELL_HPP

#include <utility>
#include <vector>
#include "../Enemys/enemy.hpp"
#include "../Defenders/wall.hpp"

class Cell {
protected:
    int type = 0;
    std::pair<int, int> coordinate;
    std::vector<Enemy::Enemies *> en;
    wall::Wall *defend;
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
        if(t==4){
            coordinate = std::make_pair(x, y);
            distance_from_castle = 0;
            distance_for_plane = 0;
            defend = nullptr;
            type = t;
        }
        else {
            coordinate = std::make_pair(x, y);
            distance_from_castle = -1;
            distance_for_plane = -1;
            defend = nullptr;
            type = t;
        }
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

    int add_defend(wall::Wall *x){
        defend=x;
    }

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


#endif //BIG_PROJECT_CELL_HPP
