#include "enemy.hpp"


namespace Enemy {
    int Enemies::get_damage(int d) {
        hp-=d;
        if (hp<0){
            return 0;
        }
        else{
            return 1;
        }
    }



    int Enemies::move() {
        return 0;
    }

    int Enemies::regeneration() {
        hp+=regeneration_speed;
        if (hp>max_hp){
            hp=max_hp;
        }
        return 0;
    }

    int Enemies::get_aura(int sp, int regen, int h) {
        return 0;
    }

    int Enemies::lost_aura() {
        return 0;
    }

    void Hero::give_aura(std::vector<Enemies> v) {
        std::vector<Enemies>::iterator i;
        for (i=v.begin();i!=v.end();i++){

        }
    }
}