#include <iostream>
#include "map.hpp"
#include <random>
#include <SFML/Graphics.hpp>

namespace map1 {
    int Cell::add_enemy(Enemy::Enemies x) {
        en.push_back(x);
        return 0;
    }

    int Cell::add_defend(Defend::Defender &x) {
        defend = &x;
        return 0;
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
        C = static_cast<Castle *>(&(Cells[x][y]));
        x = gen_x();
        y = gen_y();
        Lair lair(x, y);
        Cells[x][y] = lair;
        L = static_cast<Lair *>(&(Cells[x][y]));;
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
            distance(*C, *L);
        } while (L->get_distance() == -1);
    }

    void Map::distance(const Castle &castle, const Lair &lair) {
        std::vector<Cell> que;
        int x, y, d;
        que.push_back(castle);

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
                if (Cells[x - 1][y].get_type() == 3) {
                    (Cells.at(x - 1).at(y)).change_distance(d);
                }
            }
            if (x + 1 < max_x) {
                if (Cells[x + 1][y].get_type() == 1 or Cells[x + 1][y].get_type() == 5) {
                    if ((Cells.at(x + 1).at(y)).change_distance(d)) {
                        que.push_back(Cells[x + 1][y]);
                    }
                }
                if (Cells[x + 1][y].get_type() == 3) {
                    (Cells.at(x + 1).at(y)).change_distance(d);
                }
            }
            if (y - 1 > -1) {
                if (Cells[x][y - 1].get_type() == 1 or Cells[x][y - 1].get_type() == 5) {
                    if((Cells.at(x).at(y-1)).change_distance(d)) {
                        que.push_back(Cells[x][y - 1]);
                    }
                }
                if (Cells[x][y-1].get_type() == 3) {
                    (Cells.at(x).at(y-1)).change_distance(d);
                }
            }
            if (y + 1 < max_y) {
                if (Cells[x][y + 1].get_type() == 1 or Cells[x][y + 1].get_type() == 5) {
                    if ((Cells.at(x).at(y + 1)).change_distance(d)) {
                        que.push_back(Cells[x][y + 1]);
                    }
                    if (Cells[x][y+1].get_type() == 3) {
                        (Cells.at(x).at(y+1)).change_distance(d);
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
        sf::Image plain_image, water_image, mountain_image, castle_image, lair_image;
        plain_image.loadFromFile("../Map/Image/plain.png");
        water_image.loadFromFile("../Map/Image/water.png");
        mountain_image.loadFromFile("../Map/Image/mountain.png");
        castle_image.loadFromFile("../Map/Image/castle.png");
        lair_image.loadFromFile("../Map/Image/lair.png");
        sf::Texture plain_texture, water_texture, mountain_texture, castle_texture, lair_texture;
        plain_texture.loadFromImage(plain_image);
        water_texture.loadFromImage(water_image);
        mountain_texture.loadFromImage(mountain_image);
        castle_texture.loadFromImage(castle_image);
        lair_texture.loadFromImage(lair_image);
        sf::Sprite map_sprite;
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
                    map_sprite.setPosition(j * 64, i * 64);
                    window.draw(map_sprite);
                }
            }
            window.display();

        }
    }

}

