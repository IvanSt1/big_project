#include "cell.hpp"

int Cell::add_defend(Defend::Defender &x) {
    defend = &x;
    return 0;
}

void Cell::kill(Enemy::Enemies *x) {
    std::vector<Enemy::Enemies *>::iterator i;
    for (i = en.begin(); i != en.end(); i++) {
        if (((*i)) == x) {
            en.erase(i);
            break;
        }
    }

}