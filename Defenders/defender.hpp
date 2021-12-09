//
// Created by ivan on 05.11.2021.
//

#ifndef BIG_PROJECT_DEFENDER_HPP
#define BIG_PROJECT_DEFENDER_HPP

#include <vector>
#include <stdexcept>
#include "../Enemys/enemy.hpp"

namespace Defend {
    class Defender {
    protected:
        int type{};
    public:
        virtual int get_damage(int) = 0;

        int get_type() const {
            return type;
        }

        virtual void atack(std::vector<Enemy::Enemies*>) = 0;

        virtual void levelup() = 0;
    };
}
#endif //BIG_PROJECT_DEFENDER_HPP
