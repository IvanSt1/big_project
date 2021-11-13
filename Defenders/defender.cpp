#include "defender.hpp"
int Defend::Wall::attack(int damage) {
    hp-=damage;
    if (hp>0) {
        return 1;
    }
    else{
        return 0;
    }
}
 void Defend::Tower::levelup() {
    level++;
    damage+=10;
    speed+=5;
    radius++;

}

int Defend::Tower::attack(std::vector<Enemy::Enemies>) const{

    return 0;
}
