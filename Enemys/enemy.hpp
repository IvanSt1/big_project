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
        int max_speed;
        int k;
        int type;
        int aura_hp;
        int aura_reg;
        int aura_speed;
        std::pair<int,int> coordinate;
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
            max_speed=speed;
            coordinate= std::make_pair(0,0);
        };

        Enemies(int t,std::pair<int,int> p) {
            type = t;
            aura_hp = 0;
            aura_reg = 0;
            aura_speed = 0;
            coordinate= p;
            if (t == 1) {
                hp = 100;
                max_hp = 100;
                regeneration_speed = 5;
                speed = 100;
                k = 1;
            }
            if (t == 2) {
                hp = 100;
                max_hp = 100;
                regeneration_speed = 5;
                speed = 100;
                k = 1;
            }
            if (t == 3) {
                hp = 100;
                max_hp = 100;
                regeneration_speed = 5;
                speed = 100;
                k = 1;
            }
            max_speed=speed;

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

        int regeneration();

        int get_aura(int sp, int regen, int h);

        int lost_aura();

        bool moving() {
            speed -= (1 + aura_speed);
            if (speed == 0) {
                speed = max_speed;
                return true;
            } else {
                return false;
            }

        };
        void change_coor(std::pair<int,int> p){
            coordinate=p;
        }
        std::pair<int,int> get_coor(){
            return coordinate;
        }
    };


}

#endif //BIG_PROJECT_ENEMY_HPP
