#include <iostream>
#include "map.hpp"
#include <random>
#include <SFML/Graphics.hpp>

namespace map1 {
    int Cell::add_enemy(Enemy::Enemies *x) {
        en.push_back(x);
        return 0;
    }

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


    Map::Map(int x1, int y1) {
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
        Castle castle(x, y);
        Cells[x][y] = castle;
        C = &Cells[x][y];
        x = gen_x();
        y = gen_y();
        Lair lair(x, y);
        Cells[x][y] = lair;
        L = &(Cells[x][y]);
        do {
            x = 0;
            for (i = Cells.begin(); i != Cells.end(); i++) {
                y = 0;
                for (j = i->begin(); j != i->end(); j++) {
                    choice = gen_choice();
                    if (j->get_type() == 0 or j->get_type() == 1 or j->get_type() == 2 or j->get_type() == 3) {
                        Plain plain(x, y);
                        Mountain mountain(x, y);
                        Water water(x, y);
                        switch (choice) {
                            case 1:
                                *j = plain;
                                break;
                            case 2:
                                *j = mountain;
                                break;
                            case 3:
                                *j = plain;
                                break;
                            case 4:
                                *j = plain;
                                break;
                            case 5:
                                *j = water;
                                break;
                            case 6:
                                *j = plain;
                                break;
                            case 7:
                                *j = plain;
                                break;
                            case 8:
                                *j = water;
                                break;
                        }
                    }
                    y++;
                }
                x++;
            }
            distance();
        } while (L->get_distance() == -1);
        distance_for_plane();
        Cells_with_enemy.push_back(L);
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

    void Map::draw() const {
        int t;
        std::vector<Cell>::iterator way, next;
        sf::RenderWindow window(sf::VideoMode(max_x * 64, max_y * 64), "SFML works!");
        sf::Image plain_image, water_image, mountain_image, castle_image, lair_image, light_image, heavy_image, plane_image;
        plain_image.loadFromFile("../Map/Image/plain.png");
        water_image.loadFromFile("../Map/Image/water.png");
        mountain_image.loadFromFile("../Map/Image/mountain.png");
        castle_image.loadFromFile("../Map/Image/castle.png");
        lair_image.loadFromFile("../Map/Image/lair.png");
        light_image.loadFromFile("../Map/Image/Light.png");
        heavy_image.loadFromFile("../Map/Image/Heavy.png");
        plane_image.loadFromFile("../Map/Image/plane.png");
        sf::Texture plain_texture, water_texture, mountain_texture, castle_texture, lair_texture, light_texture, heavy_texture, plane_texture;
        plain_texture.loadFromImage(plain_image);
        water_texture.loadFromImage(water_image);
        mountain_texture.loadFromImage(mountain_image);
        castle_texture.loadFromImage(castle_image);
        lair_texture.loadFromImage(lair_image);
        light_texture.loadFromImage(light_image);
        heavy_texture.loadFromImage(heavy_image);
        plane_texture.loadFromImage(plane_image);
        sf::Sprite map_sprite, enemy_sprite;
        while (window.isOpen()) {
            sf::Event event{};
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            window.clear();
            for (int i = 0; i < max_y; i++) {
                for (int j = 0; j < max_x; j++) {
                    t = get_map()[j][i].get_type();
                    switch (t) {
                        case 0:
                            break;
                        case 1:
                            map_sprite.setTexture(plain_texture);
                            break;
                        case 2:
                            map_sprite.setTexture(mountain_texture);
                            break;
                        case 3:
                            map_sprite.setTexture(water_texture);
                            break;
                        case 4:
                            map_sprite.setTexture(castle_texture);
                            break;
                        case 5:
                            map_sprite.setTexture(lair_texture);
                            break;
                    }
                    if (!get_map()[j][i].get_enemies().empty()) {
                        t = get_map()[j][i].get_enemies()[0]->get_type();
                        enemy_sprite.setPosition(j * 64 + 16, i * 64 + 16);
                        switch (t) {
                            case 0:
                                break;
                            case 1:
                                enemy_sprite.setTexture(light_texture);
                                break;
                            case 2:
                                enemy_sprite.setTexture(heavy_texture);
                                break;
                            case 3:
                                enemy_sprite.setTexture(plane_texture);
                                break;
                        }
                        window.draw(enemy_sprite);
                    }
                    map_sprite.setPosition(j * 64, i * 64);
                    window.draw(map_sprite);

                }
            }
            window.display();


        }
    }

    void Map::play() {
        int x;
        Enemy::Enemies *new_enemy;
        auto gen = []() {
            static std::mt19937 rng{std::random_device()()};
            static std::uniform_int_distribution<int> distr(1, 3);
            return distr(rng);
        };

        while (hp > 0) {
            for (int i = 0; i < 3; i++) {
                switch (gen()) {
                    case 1:
                        new_enemy = new Enemy::Light;
                        break;
                    case 2:
                        new_enemy = new Enemy::Heavy;
                        break;
                    case 3:
                        new_enemy = new Enemy::Plane;
                        break;
                }
                L->add_enemy(new_enemy);
            }
            go();
            //draw();
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
        int x = 0, y = 0, k, t, kol = 0;
        bool b1, b2, b3, b4;
        std::vector<Enemy::Enemies *> p;
        std::vector<Cell *>::iterator i;
        std::vector<Cell *> plus;
        std::vector<Enemy::Enemies *>::iterator e;
        for (i = Cells_with_enemy.begin(); i != Cells_with_enemy.end(); ++i) {
            p = (*i)->get_enemies();
            x = (*i)->get_coordinate().first;
            y = (*i)->get_coordinate().second;
            b1 = true;
            b2 = true;
            b3 = true;
            b4 = true;
            for (e = p.begin(); e != p.end(); e++) {
                if (x == C->get_coordinate().first and y == C->get_coordinate().second) {
                    hp -= (*e)->get_hp() * (*e)->get_k();
                } else {
                    Enemy::Enemies enemy;
                    if ((*(*e)).moving()) {
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
                                Cells[x - 1][y].add_enemy(*e);
                                Cells[x][y].kill(*e);
                                if (b1) {
                                    plus.push_back(&Cells[x - 1][y]);
                                    b1 = false;
                                }

                                break;
                            case 2:
                                Cells[x + 1][y].add_enemy(*e);
                                Cells[x][y].kill(*e);
                                if (b2) {
                                    b2 = false;
                                    plus.push_back(&Cells[x + 1][y]);

                                }
                                break;
                            case 3:
                                Cells[x][y - 1].add_enemy(*e);
                                Cells[x][y].kill(*e);
                                if (b3) {
                                    b3 = false;
                                    plus.push_back(&Cells[x][y - 1]);

                                }
                                break;
                            case 4:
                                Cells[x][y + 1].add_enemy(*e);
                                Cells[x][y].kill(*e);
                                if (b4) {
                                    b4 = false;
                                    plus.push_back(&Cells[x][y + 1]);

                                }
                                break;

                        }
                        kol++;
                    }
                }
            }
            if ((*i)->get_enemies().empty()) {
                Cells_with_enemy.erase(i);
            }
        }
        if (!plus.empty()) {
            for (i = plus.begin(); i != plus.end(); ++i) {
                Cells_with_enemy.push_back(*i);
            }
        }
    }

    int Map::where_to_go(int x, int y) {
        int d, t, dmin = max_y * max_x;
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


    void Lair::spawn() {
        int choice;
        Enemy::Enemies *new_enemy;
        auto gen = []() {
            static std::mt19937 rng{std::random_device()()};
            static std::uniform_int_distribution<int> distr(1, 3);
            return distr(rng);
        };
        for (int i = 0; i < 10; i++) {
            choice = gen();
            switch ((choice)) {
                case 1:
                    new_enemy = new Enemy::Light;
                    break;
                case 2:
                    new_enemy = new Enemy::Heavy;
                    break;
                case 3:
                    new_enemy = new Enemy::Plane;
                    break;
            }
            add_enemy(new_enemy);
        }
    }
}

