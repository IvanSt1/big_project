//
// Created by ivan on 27.11.2021.
//

#ifndef BIG_PROJECT_LAIR_HPP
#define BIG_PROJECT_LAIR_HPP
#include "cell.hpp"
class Lair : public Cell {
public:
    Lair(int x, int y) : Cell(x, y) {
        type = 5;
    }

    std::vector<Enemy::Enemies*> spawn(int n);
};
#endif //BIG_PROJECT_LAIR_HPP
