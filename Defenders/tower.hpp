
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

    Tower(My_table::Table<int, std::vector<int>> &table, std::pair<int, int> p) {
        type = 2;
        level = 1;
        std::vector<int> mas = (table.find(1))->second;
        price = mas.at(0);
        radius = mas.at(1);
        damage = mas.at(2);
        speed = mas.at(3);
        coor = p;
    }

    void levelup( std::vector<int> &table) override {
            level++;
        price = table.at(0);
        radius = table.at(1);
        damage = table.at(2);
        speed = table.at(3);
    }

    bool dist(std::pair<int, int> pair1, std::pair<int, int> pair2) const {
        return ((abs(pair1.first - pair2.first) <= radius)) && (abs(pair1.second - pair2.second) <= radius);
    }

    int get_damage(int) override {
        return 0;
    }
    int get_level() const{
        return level;
    }
    void atack(std::vector<Enemy::Enemies *> &enemies, int &money) override {
        int i, choice, hp;
        auto j = enemies.begin();
        i = 0;
        while (i < speed && j != enemies.end()) {
            if (dist(coor, (*j)->get_coor())) {
                choice=(*j)->get_damage(damage);

                if ((*j)->get_hp()<=0 and choice==0) {
                    money += 10;
                    enemies.erase(j);
                }
                i++;

            } else {
                j++;
            }
        }


    }

    std::pair<int, int> get_coor() const {
        return coor;
    }

};

#endif //BIG_PROJECT_TOWER_HPP
