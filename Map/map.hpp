//
// Created by ivan on 03.11.2021.
//

#ifndef BIG_PROJECT_MAP_HPP
#define BIG_PROJECT_MAP_HPP


#include <vector>
#include <queue>
#include "../Defenders/defender.hpp"

namespace map1 {

    class Cell {
    protected:
        int type = 0;
        std::pair<int, int> coordinate;
        std::vector<Enemy::Enemies> en;
        Defend::Defender *defend;
    public:
        Cell(){
            coordinate=std::make_pair(0,0);
            defend=nullptr;
        }
        Cell(int x, int y) {
            coordinate=std::make_pair(x, y);
            defend = nullptr;
        }

        [[nodiscard]] std::pair<int,int> get_coordinate() const {
            return coordinate;
        }

        [[nodiscard]] int get_type() const {
            return type;
        }
        [[nodiscard]] Defend::Defender* get_defend() const {
            return defend;
        }
        int add_enemy(Enemy::Enemies x);

        int add_defend(Defend::Defender &x);
    };

    class Plain : public Cell {
    private:
    public:
        Plain(int x, int y) : Cell(x,y){
            type = 1;
        }
    };

    class Mountain : public Cell {
    public:
        Mountain(int x, int y) : Cell(x,y){
            type = 2;
        }
    };

    class Water : public Cell {
    public:
        Water(int x, int y) : Cell(x,y){
            type = 3;
        }
    };

    class Castle : public Cell {
    private:
    public:
        Castle(int x, int y) : Cell(x,y){
            type = 4;
        }
    };

    class Lair : public Cell {
    public:
        Lair(int x, int y) : Cell(x,y) {
            type = 5;
        }
    };
    struct search{
        map1::Cell el;
        int weight=0;
        search *previous= nullptr;
    };

    class Map {
    private:
        int max_x;
        int max_y;
        std::vector<std::vector<Cell>> Cells;
        std::vector<Cell> way1;
        std::vector<Cell> way2;
        std::vector<Cell> way3;
        Castle* C;
        Lair *L;
    public:
        Map(int x1, int y1);
        std::vector<Cell> light_way(const Castle &castle, const Lair &lair) const;
        std::vector<Cell> heavy_way(const Castle &castle, const Lair &lair) const;
        std::vector<Cell> plane_way(const Castle &castle, const Lair &lair) const;
        [[nodiscard]] std::vector<std::vector<Cell>> get_map() const{
            return Cells;
        }
        void draw_to_terminal();
        void draw();
    };
}
#endif //BIG_PROJECT_DEFENDER_HPP

