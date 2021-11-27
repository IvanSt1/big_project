#include "defender.hpp"
 void Defend::Tower::levelup() {

    level++;

}

int Defend::Tower::atack(std::vector<Enemy::Enemies>) {
    return 0;
}

int Defend::Wall::atack(int damage) {
    hp-=damage;
    if (hp>0){
        return 1;
    }
    else{
        return 0;
    }
}

Defend::Wall::Wall() {
    type=1;
    max_hp=500;
    hp=max_hp;
}
