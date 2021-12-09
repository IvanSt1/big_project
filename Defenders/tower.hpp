//
// Created by ivan on 27.11.2021.
//

#ifndef BIG_PROJECT_TOWER_HPP
#define BIG_PROJECT_TOWER_HPP

#include "defender.hpp"
#include "../Table/table.hpp"
class Tower : public Defend::Defender {
private:
    int level;
    int price;
    int radius;
    int damage;
    int speed;
    std::pair<int, int> coor;
public:
    Tower() {
        type = 2;
        radius = 0;
        damage = 0;
        speed = 0;
        price = 100;
        level = 0;
        coor = std::make_pair(0, 0);
    };

    Tower(My_table::Table<int, std::vector<int>> table, std::pair<int, int> p) {
        type = 2;
        level = 1;
        std::vector<int> mas = (*table.find(1)).second;
        price = mas.at(0);
        radius = mas.at(1);
        damage = mas.at(2);
        speed = mas.at(3);
        coor = p;
    }

    void levelup() override {

    }

    bool dist(std::pair<int, int> pair1, std::pair<int, int> pair2) const {
        return ((abs(pair1.first-pair2.first)<=radius)) &&(abs(pair1.second-pair2.second)<radius);
    }
    int get_damage(int) override{
        return 0;
    }
    void atack(std::vector<Enemy::Enemies *> enemies)  override {
        int i;
        std::vector<Enemy::Enemies *>::iterator j;
        j = enemies.begin();
        i = 0;
        while (i < speed && j != enemies.end()) {
            if (dist(coor, (*j)->get_coor())) {
                if ((*j)->get_damage(damage)) {
                    j = enemies.erase(j);

                }
                i++;

            }
            else{
                j++;
            }
        }


    }

};

#endif //BIG_PROJECT_TOWER_HPP
