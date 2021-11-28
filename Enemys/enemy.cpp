#include "enemy.hpp"


namespace Enemy {
    int Enemies::get_damage(int d) {
        hp -= d;
        if ((hp+aura_hp) < 0) {
            return 0;
        } else {
            return 1;
        }
    }
    int Enemies::regeneration() {
        hp += regeneration_speed+aura_reg;
        if (hp > max_hp+aura_hp) {
            hp = max_hp+aura_hp;
        }
        return 0;
    }

    int Enemies::get_aura(int sp, int regen, int h) {
        return 0;
    }

    int Enemies::lost_aura() {
        return 0;
    }

}