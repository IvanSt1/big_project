//
// Created by ivan on 27.11.2021.
//

#ifndef BIG_PROJECT_WALL_HPP
#define BIG_PROJECT_WALL_HPP

#include "defender.hpp"

namespace wall {
    class Wall : public Defend::Defender {
    private:
        int max_hp;
        int hp;

    public:
        Wall() {
            type = 1;
            max_hp = 500;
            hp = max_hp;
        }

        int get_damage(int damage) override{
            hp-=damage;
            if (hp>0){
                return 1;
            }
            else{
                return 0;
            }
        }
        void atack(std::vector<Enemy::Enemies *>) override{}
        void levelup() override{}
    };
}
#endif //BIG_PROJECT_WALL_HPP
