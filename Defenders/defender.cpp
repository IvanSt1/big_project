#include "defender.hpp"
 void Defend::Tower::levelup() {
    level++;
    damage+=10;
    speed+=5;
    radius++;

}

int Defend::Tower::atack(std::vector<Enemy::Enemies>) {
    return 0;
}

int Defend::Wall::atack(int damage) {
    return 0;
}
