//
// Created by ivan on 03.11.2021.
//

#ifndef BIG_PROJECT_ENEMY_HPP
#define BIG_PROJECT_ENEMY_HPP

#include <vector>

namespace Enemy {
    class Enemies {
    protected:
        int hp;
        int max_hp;
        int regeneration_speed;
        int speed;
        int k;
        int type;
        int aura_hp;
        int aura_reg;
        int aura_speed;
    public:
        Enemies() {
            hp = 0;
            max_hp = 0;
            regeneration_speed = 0;
            speed = 0;
            k = 0;
            type = 0;
            aura_hp = 0;
            aura_reg = 0;
            aura_speed = 0;
        };

        int get_hp() {
            return hp;
        }

        int get_k() {
            return k;
        }

        int get_type() {
            return type;
        }

        int get_damage(int d);

        virtual bool moving() {
            return true;
        };

        int regeneration();

        int get_aura(int sp, int regen, int h);

        int lost_aura();


    };

    class Light : public Enemies {
    private:
    public:
        Light() {
            type = 1;
            hp = 100;
            max_hp = 100;
            regeneration_speed = 5;
            speed = 3;
            k = 1;
        };

        bool moving() {
            speed--;
            if (speed == 0) {
                speed = 3;
                return true;
            } else {
                return false;
            }
        }
    };

    class Heavy : public Enemies {
    private:
    public:
        Heavy() {
            type = 2;
            hp = 100;
            max_hp = 100;
            regeneration_speed = 5;
            speed = 5;
            k = 1;
        };

        bool moving() {
            speed--;
            if (speed == 0) {
                speed = 5;
                return true;

            } else {
                return false;
            }
        }

    };

    class Plane : public Enemies {
    private:
    public:
        Plane() {
            type = 3;
            hp = 100;
            max_hp = 100;
            regeneration_speed = 5;
            speed = 3;
            k = 1;
        };

        bool moving() {
            speed--;
            if (speed == 0) {
                speed = 3;
                return true;
            } else {
                return false;
            }
        }
    };

    class Hero : public Enemies {
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

        bool moving() {
            speed--;
            return true;
        }

        void give_aura(std::vector<Enemies>);

    };
}
#endif //BIG_PROJECT_ENEMY_HPP
