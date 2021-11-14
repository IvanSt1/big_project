//
// Created by ivan on 05.11.2021.
//

#ifndef BIG_PROJECT_DEFENDER_HPP
#define BIG_PROJECT_DEFENDER_HPP

#include <vector>
#include "../Enemys/enemy.hpp"

namespace Defend{
    class Defender{
    protected:
        int type;
        int price;
        const int max_hp=100;
        int hp;
        int level;
    public:
        Defender(){
            price=100;
            type=0;
            hp=max_hp;
            level=1;
        }
        [[nodiscard]] int get_price() const{
            return price;
        };
        [[nodiscard]] int get_type() const{
            return type;
        };
        virtual int atack(int )=0;
        virtual int atack(std::vector<Enemy::Enemies> )=0;
        virtual void levelup()=0;
    };

    class Wall :public Defender{
    private:
    public:
        Wall(){
        type=1;
    };
        int atack(int damage) override;
    };

    class  Tower : public Defender{
    private:
        int radius;
        int damage;
        int speed;
    public:
        Tower(){
            type=2;
            radius=2;
            damage=10;
            speed=10;
        };
        void levelup () override;
        int atack(std::vector<Enemy::Enemies>) override;
    };
}
#endif //BIG_PROJECT_DEFENDER_HPP
