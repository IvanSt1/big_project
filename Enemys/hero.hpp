//
// Created by ivan on 27.11.2021.
//

#ifndef BIG_PROJECT_HERO_HPP
#define BIG_PROJECT_HERO_HPP
#include "enemy.hpp"
#include <vector>
class Hero : public Enemy::Enemies {
private:
public:
    Hero() {
        aura_speed = 1;
        aura_reg = 1;
        aura_hp = 1;
        type = 4;
    }

    Hero(int sp, int regen, int health) {
        aura_hp = health;
        aura_reg = regen;
        aura_speed = sp;
        type = 4;
    }
    void give_aura(std::vector<Enemy::Enemies>);

};
#endif //BIG_PROJECT_HERO_HPP
