//
// Created by ivan on 03.11.2021.
//

#ifndef BIG_PROJECT_MAP_HPP
#define BIG_PROJECT_MAP_HPP


#include <vector>
#include <queue>
#include "../Defenders/tower.hpp"
#include "../Defenders/wall.hpp"
#include "../Cell/cell.hpp"
#include "../Cell/lair.hpp"
#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>

namespace map1 {
    class Map {
    private:
        int max_x;
        int max_y;
        std::vector<std::vector<Cell>> Cells;
        Castle *C;
        int hp;
        int money;
        Lair *L;
        std::vector<Enemy::Enemies*> enemies;
        std::vector<Tower*> towers;
        sf::RenderWindow window;
        void distance();
        void add_enemies(std::vector<Enemy::Enemies*>);
        void distance_for_plane();

        int where_to_go(int x, int y);

        int where_to_go_for_heavy(int x, int y);

        int where_to_go_for_plane(int x, int y);
        Table<int, std::vector<int>> Tower_Table;
        [[nodiscard]] std::vector<std::vector<Cell>> get_map() const {
            return Cells;
        }
        void draw() ;
        //void draw_enemies();
        void go();
        Table<int, std::vector<int>> get_table(){
            return Tower_Table;
        };
    public:
        Map();

        Map(int x1, int y1);

        void resize(int x1, int y1);
        void play();
    };
}
#endif //BIG_PROJECT_MAP_HPP

