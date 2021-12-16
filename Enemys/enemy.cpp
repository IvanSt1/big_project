#include "enemy.hpp"


namespace Enemy {
    int Enemies::get_damage(int d) {
        hp -= d;
        if (hp >0 ) {
            return 1;
        } else {
            return 0;
        }
    }
    void Enemies::regeneration() {
        hp += regeneration_speed;
        if (hp > max_hp) {
            hp = max_hp;
        }
    }


}