#include <random>
#include "lair.hpp"

std::vector<Enemy::Enemies*> Lair::spawn(int n) {
    int choice;
    std::vector<Enemy::Enemies*> enemies;
    Enemy::Enemies *new_enemy;
    auto gen = []() {
        static std::mt19937 rng{std::random_device()()};
        static std::uniform_int_distribution<int> distr(1, 3);
        return distr(rng);
    };
    for (int i = 0; i < n; i++) {
        new_enemy = new Enemy::Enemies(gen(),get_coordinate() );
        enemies.push_back(new_enemy);
    }
    return enemies;
}

