#include <iostream>
#include "map.hpp"
#include <random>


namespace map1 {


    Map::Map(int x1, int y1) {
        hp = 10000000;
        int t;
        Tower_Table.insert(1, {200, 1, 10, 10});
        Tower_Table.insert(2, {200, 2, 15, 15});
        Tower_Table.insert(3, {400, 2, 20, 20});
        Tower_Table.insert(4, {500, 3, 30, 30});
        Tower_Table.insert(5, {600, 3, 40, 40});
        max_x = x1;
        max_y = y1;
        auto gen_x = [this]() {
            static std::mt19937 rng{std::random_device()()};
            static std::uniform_int_distribution<int> distr(0, 2);
            return distr(rng);
        };
        auto gen_y = [this]() {
            static std::mt19937 rng{std::random_device()()};
            static std::uniform_int_distribution<int> distr(0, 2);
            return distr(rng);
        };
        auto gen_choice = []() {
            static std::mt19937 rng{std::random_device()()};
            static std::uniform_int_distribution<int> distr(1, 8);
            return distr(rng);
        };
        Cells.resize(max_x);
        std::vector<std::vector<Cell>>::iterator i;
        std::vector<Cell>::iterator j;
        for (i = Cells.begin(); i != Cells.end(); i++) {
            i->resize(max_y);
        }
        int x, y, choice;
        x = max_x - 1 - gen_x();
        y = max_y - 1 - gen_y();
        Cell castle(x, y,4);
        Cells[x][y] = castle;
        C = &Cells[x][y];
        x = gen_x();
        y = gen_y();
        Lair lair(x, y);
        Cells[x][y] = lair;
        L = static_cast<Lair *>(&(Cells[x][y]));
        do {
            x = 0;
            for (i = Cells.begin(); i != Cells.end(); i++) {
                y = 0;
                for (j = i->begin(); j != i->end(); j++) {
                    if (j->get_type() == 0 or j->get_type() == 1 or j->get_type() == 2 or j->get_type() == 3) {
                        switch ( gen_choice()) {
                            case 1:
                                t = 1;
                                break;
                            case 2:
                                t = 2;
                                break;
                            case 3:
                                t = 1;
                                break;
                            case 4:
                                t = 3;
                                break;
                            case 5:
                                t = 1;
                                break;
                            case 6:
                                t = 3;
                                break;
                            case 7:
                                t = 1;
                                break;
                            case 8:
                                t = 2;
                                break;
                        }
                        *j = Cell(x, y, t);
                    }
                    y++;
                }
                x++;
            }
            distance();
        } while (L->get_distance() == -1);
        distance_for_plane();
    }

    void Map::distance() {
        std::vector<Cell> que;
        int x, y, d;
        que.push_back(*C);

        while (!que.empty()) {
            x = que.begin()->get_coordinate().first;
            y = que.begin()->get_coordinate().second;
            d = Cells[x][y].get_distance();
            if (x - 1 > -1) {
                if (Cells[x - 1][y].get_type() == 1 or Cells[x - 1][y].get_type() == 5) {
                    if ((Cells.at(x - 1).at(y)).change_distance(d)) {
                        que.push_back(Cells[x - 1][y]);
                    }
                }
            }
            if (x + 1 < max_x) {
                if (Cells[x + 1][y].get_type() == 1 or Cells[x + 1][y].get_type() == 5) {
                    if ((Cells.at(x + 1).at(y)).change_distance(d)) {
                        que.push_back(Cells[x + 1][y]);
                    }
                }
            }
            if (y - 1 > -1) {
                if (Cells[x][y - 1].get_type() == 1 or Cells[x][y - 1].get_type() == 5) {
                    if ((Cells.at(x).at(y - 1)).change_distance(d)) {
                        que.push_back(Cells[x][y - 1]);
                    }
                }
            }
            if (y + 1 < max_y) {
                if (Cells[x][y + 1].get_type() == 1 or Cells[x][y + 1].get_type() == 5) {
                    if ((Cells.at(x).at(y + 1)).change_distance(d)) {
                        que.push_back(Cells[x][y + 1]);
                    }
                }
            }
            que.erase(que.begin());
        };
    }

    void Map::draw() {
        int t;
        std::vector<Cell>::iterator way, next;
        sf::Sprite sprite;
        sf::Image plain_image, water_image, mountain_image, castle_image, lair_image, light_image, heavy_image, plane_image;
        plain_image.loadFromFile("../Map/Image/plain.png");
        water_image.loadFromFile("../Map/Image/water.png");
        mountain_image.loadFromFile("../Map/Image/mountain.png");
        castle_image.loadFromFile("../Map/Image/castle.png");
        lair_image.loadFromFile("../Map/Image/lair.png");
        sf::Texture plain_texture, water_texture, mountain_texture, castle_texture, lair_texture, light_texture, heavy_texture, plane_texture;
        plain_texture.loadFromImage(plain_image);
        water_texture.loadFromImage(water_image);
        mountain_texture.loadFromImage(mountain_image);
        castle_texture.loadFromImage(castle_image);
        lair_texture.loadFromImage(lair_image);
        for (int i = 0; i < max_y; i++) {
            for (int j = 0; j < max_x; j++) {
                t = get_map()[j][i].get_type();
                switch (t) {
                    case 0:
                        break;
                    case 1:
                        sprite.setTexture(plain_texture);
                        break;
                    case 2:
                        sprite.setTexture(mountain_texture);
                        break;
                    case 3:
                        sprite.setTexture(water_texture);
                        break;
                    case 4:
                        sprite.setTexture(castle_texture);
                        break;
                    case 5:
                        sprite.setTexture(lair_texture);
                        break;
                }
                sprite.setPosition(j * 64, i * 64);
                window.draw(sprite);
            }
        }

    }


    void Map::play() {
        int x=0,y=0;
        Tower *tower;
        wall::Wall* wall;
        while (hp > 0) {
            add_enemies(L->spawn(2));
            go();
            if(false){
                tower=new Tower(Tower_Table, std::make_pair(x,y));
                towers.push_back(tower);
            }
            if(false){
                wall=new wall::Wall();
                Cells[x][y].add_defend(wall);
            }
            towers_atack();
        }
        if (hp <= 0) {
            std::cout << "ПРОИГРАЛ";
        }
    }

    void Map::distance_for_plane() {
        std::vector<Cell> que;
        int x, y, d;
        que.push_back(*C);

        while (!que.empty()) {
            x = que.begin()->get_coordinate().first;
            y = que.begin()->get_coordinate().second;
            d = Cells[x][y].get_distance_for_plane();
            if (x - 1 > -1) {
                if (Cells[x - 1][y].get_type() == 1 or Cells[x - 1][y].get_type() == 5 or
                    Cells[x - 1][y].get_type() == 3) {
                    if ((Cells.at(x - 1).at(y)).change_distance_for_plane(d)) {
                        que.push_back(Cells[x - 1][y]);
                    }
                }
            }
            if (x + 1 < max_x) {
                if (Cells[x + 1][y].get_type() == 1 or Cells[x + 1][y].get_type() == 5 or
                    Cells[x + 1][y].get_type() == 3) {
                    if ((Cells.at(x + 1).at(y)).change_distance_for_plane(d)) {
                        que.push_back(Cells[x + 1][y]);
                    }
                }
            }
            if (y - 1 > -1) {
                if (Cells[x][y - 1].get_type() == 1 or Cells[x][y - 1].get_type() == 5 or
                    Cells[x][y - 1].get_type() == 3) {
                    if ((Cells.at(x).at(y - 1)).change_distance_for_plane(d)) {
                        que.push_back(Cells[x][y - 1]);
                    }
                }
            }
            if (y + 1 < max_y) {
                if (Cells[x][y + 1].get_type() == 1 or Cells[x][y + 1].get_type() == 5 or
                    Cells[x][y + 1].get_type() == 3) {
                    if ((Cells.at(x).at(y + 1)).change_distance_for_plane(d)) {
                        que.push_back(Cells[x][y + 1]);
                    }
                }
            }
            que.erase(que.begin());
        };
    }

    void Map::go() {
        int x = 0, y = 0, k, t;
        std::vector<Enemy::Enemies *>::iterator e;
        for (e = enemies.begin(); e != enemies.end(); e++) {
            x = (*e)->get_coor().first;
            y = (*e)->get_coor().second;
            if (x == C->get_coordinate().first and y == C->get_coordinate().second) {
                hp -= (*e)->get_hp() * (*e)->get_k();
                e = enemies.erase(e);
            } else if (Cells[x][y].get_defend() != nullptr and Cells[x][y].get_defend()->get_type() == 1) {
                Cells[x][y].get_defend()->get_damage((*e)->get_hp() * (*e)->get_k());
                e = enemies.erase(e);
            } else {
                if ((*e)->moving()) {
                    k = (*e)->get_type();
                    switch (k) {
                        case 1:
                            t = where_to_go(x, y);
                            break;
                        case 2:
                            t = where_to_go_for_heavy(x, y);
                            break;
                        case 3:
                            t = where_to_go_for_plane(x, y);
                            break;
                        case 4:
                            t = where_to_go(x, y);
                            break;
                    }
                    switch (t) {
                        case 0:
                            break;
                        case 1:
                            (*e)->change_coor(std::make_pair(x - 1, y));
                            break;
                        case 2:
                            (*e)->change_coor(std::make_pair(x + 1, y));
                            break;
                        case 3:
                            (*e)->change_coor(std::make_pair(x, y - 1));
                            break;
                        case 4:
                            (*e)->change_coor(std::make_pair(x, y + 1));
                            break;

                    }
                }
            }
        }

    }

    int Map::where_to_go(int x, int y) {
        int d, t, dmin = max_y * max_x;
        t=0;
        if (x - 1 > -1) {
            if ((Cells[x - 1][y].get_type() == 1 or Cells[x - 1][y].get_type() == 4) and
                Cells[x - 1][y].get_defend() == nullptr) {

                d = Cells[x - 1][y].get_distance();
                if (d < dmin) {
                    t = 1;
                    dmin = d;
                }
            }
        }
        if (x + 1 < max_x) {
            if ((Cells[x + 1][y].get_type() == 1 or Cells[x + 1][y].get_type() == 4) and
                Cells[x + 1][y].get_defend() == nullptr) {
                d = Cells[x + 1][y].get_distance();
                if (d < dmin) {
                    t = 2;
                    dmin = d;
                }
            }
        }
        if (y - 1 > -1) {
            if ((Cells[x][y - 1].get_type() == 1 or Cells[x][y - 1].get_type() == 4) and
                Cells[x][y - 1].get_defend() == nullptr) {
                d = Cells[x][y - 1].get_distance();
                if (d < dmin) {
                    t = 3;
                    dmin = d;
                }
            }
        }
        if (y + 1 < max_y) {
            if ((Cells[x][y + 1].get_type() == 1 or Cells[x][y + 1].get_type() == 4) and
                Cells[x][y + 1].get_defend() == nullptr) {
                d = Cells[x][y + 1].get_distance();
                if (d < dmin) {
                    t = 4;
                    dmin = d;
                }
            }
        }
        return t;
    }

    int Map::where_to_go_for_plane(int x, int y) {
        int d, t, dmin = max_y * max_x;
        if (x - 1 > -1) {
            if (Cells[x - 1][y].get_type() == 1 or Cells[x - 1][y].get_type() == 4 or Cells[x - 1][y].get_type() == 3) {

                d = Cells[x - 1][y].get_distance_for_plane();
                if (d < dmin) {
                    t = 1;
                    dmin = d;
                }
            }
        }
        if (x + 1 < max_x) {
            if (Cells[x + 1][y].get_type() == 1 or Cells[x + 1][y].get_type() == 4 or Cells[x + 1][y].get_type() == 3) {
                d = Cells[x + 1][y].get_distance_for_plane();
                if (d < dmin) {
                    t = 2;
                    dmin = d;
                }
            }
        }
        if (y - 1 > -1) {
            if (Cells[x][y - 1].get_type() == 1 or Cells[x][y - 1].get_type() == 4 or Cells[x][y - 1].get_type() == 3) {
                d = Cells[x][y - 1].get_distance_for_plane();
                if (d < dmin) {
                    t = 3;
                    dmin = d;
                }
            }
        }
        if (y + 1 < max_y) {
            if (Cells[x][y + 1].get_type() == 1 or Cells[x][y + 1].get_type() == 4 or Cells[x][y + 1].get_type() == 3) {
                d = Cells[x][y + 1].get_distance_for_plane();
                if (d < dmin) {
                    t = 4;
                    dmin = d;
                }
            }
        }
        return t;
    }

    int Map::where_to_go_for_heavy(int x, int y) {
        int d, t, dmin = max_y * max_x;
        if (x - 1 > -1) {
            if ((Cells[x - 1][y].get_type() == 1 or Cells[x - 1][y].get_type() == 4)) {
                d = Cells[x - 1][y].get_distance();
                if (d < dmin) {
                    t = 1;
                    dmin = d;
                }
            }
        }
        if (x + 1 < max_x) {
            if ((Cells[x + 1][y].get_type() == 1 or Cells[x + 1][y].get_type() == 4)) {
                d = Cells[x + 1][y].get_distance();
                if (d < dmin) {
                    t = 2;
                    dmin = d;
                }
            }
        }
        if (y - 1 > -1) {
            if ((Cells[x][y - 1].get_type() == 1 or Cells[x][y - 1].get_type() == 4)) {
                d = Cells[x][y - 1].get_distance();
                if (d < dmin) {
                    t = 3;
                    dmin = d;
                }
            }
        }
        if (y + 1 < max_y) {
            if ((Cells[x][y + 1].get_type() == 1 or Cells[x][y + 1].get_type() == 4)) {
                d = Cells[x][y + 1].get_distance();
                if (d < dmin) {
                    t = 4;
                    dmin = d;
                }
            }
        }
        return t;
    }

    Map::Map() {
        max_x = 0;
        max_y = 0;
        money = 0;
        hp = 0;
        C = nullptr;
        L = nullptr;
        Tower_Table.insert(1, {200, 1, 10, 10});
        Tower_Table.insert(2, {200, 2, 15, 15});
        Tower_Table.insert(3, {400, 2, 20, 20});
        Tower_Table.insert(4, {500, 3, 30, 30});
        Tower_Table.insert(5, {600, 3, 40, 40});
    }

    void Map::resize(int x1, int y1) {
        max_x = x1;
        max_y = y1;
        Cells.resize(max_x);
        std::vector<std::vector<Cell>>::iterator i;
        std::vector<Cell>::iterator j;
        for (i = Cells.begin(); i != Cells.end(); i++) {
            i->resize(max_y);
        }
    }

    void Map::add_enemies(std::vector<Enemy::Enemies *> mas) {
        for (auto i: mas) {
            enemies.push_back(i);
        }
    }

    void Map::towers_atack() {
        for(auto tower:towers){
            tower->atack(enemies);
        }
    }

    Map::Map(int x1, int y1, int t) {
        hp = 10000000;
        Tower_Table.insert(1, {200, 1, 10, 10});
        Tower_Table.insert(2, {200, 2, 15, 15});
        Tower_Table.insert(3, {400, 2, 20, 20});
        Tower_Table.insert(4, {500, 3, 30, 30});
        Tower_Table.insert(5, {600, 3, 40, 40});
        max_x = x1;
        max_y = y1;
        Cells.resize(max_x);
        std::vector<std::vector<Cell>>::iterator i;
        std::vector<Cell>::iterator j;
        for (i = Cells.begin(); i != Cells.end(); i++) {
            i->resize(max_y);
        }
        int x, y;
        x = max_x - 1;
        y = max_y - 1;
        Cell castle(x, y,4);
        Cells[x][y] = castle;
        C = &Cells[x][y];
        x =0;
        y =0;
        Lair lair(x, y);
        Cells[x][y] = lair;
        L = static_cast<Lair *>(&(Cells[x][y]));
        do {
            x = 0;
            for (i = Cells.begin(); i != Cells.end(); i++) {
                y = 0;
                for (j = i->begin(); j != i->end(); j++) {
                    if (j->get_type() == 0 or j->get_type() == 1 or j->get_type() == 2 or j->get_type() == 3) {

                        *j = Cell(x, y, t);
                    }
                    y++;
                }
                x++;
            }
            distance();
        } while (L->get_distance() == -1);
        distance_for_plane();
        auto *tower = new Tower(Tower_Table, std::make_pair(3, 4));
        towers.push_back(tower);
    }

    void Map::play(int n, bool t, bool w, int xt, int yt, int xw, int yw) {
        int i=0;
        Tower *tower;
        wall::Wall* wall;
        while (hp > 0 and i<n) {
            add_enemies(L->spawn(2));
            go();
            if(t){
                tower=new Tower(Tower_Table, std::make_pair(xt,yt));
                towers.push_back(tower);
            }
            if(w){
                wall=new wall::Wall();
                Cells[xw][yw].add_defend(wall);
            }
            towers_atack();
        }
        if (hp <= 0) {
            std::cout << "ПРОИГРАЛ";
        }
        i++;
    }
}

