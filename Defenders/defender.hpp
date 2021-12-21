
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

        virtual void atack(std::vector<Enemy::Enemies*> &, int &) = 0;

        virtual void levelup( std::vector<int> &table) = 0;
    };
}
#endif //BIG_PROJECT_DEFENDER_HPP
