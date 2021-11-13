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
            static std::uniform_int_distribution<int> distr(0, 3);
            return distr(rng);
        };
        auto gen_y = [this]() {
            static std::mt19937 rng{std::random_device()()};
            static std::uniform_int_distribution<int> distr(0, 3);
            return distr(rng);
        };
        auto gen_choice = []() {
            static std::mt19937 rng{std::random_device()()};
            static std::uniform_int_distribution<int> distr(1, 7);
            return distr(rng);
        };
        Cells.resize(x1);
        std::vector<std::vector<Cell>>::iterator i;
        std::vector<Cell>::iterator j;
        for (i = Cells.begin(); i != Cells.end(); i++) {
            i->resize(y1);
        }
        int x, y, choice;
        x = gen_x();
        y = gen_y();
        Castle castle(x, y);
        Cells[x][y] = castle;
        x = max_x-gen_x();
        y = max_y-gen_y();
        Lair lair(x, y);
        Cells[x][y] = lair;
        L = &lair;
        C = &castle;
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
                        }
                    }
                    y++;
                }
                x++;
            }
        } while (light_way(castle, lair).empty());
        way1 = light_way(castle, lair);
        way2 = heavy_way(castle, lair);
        way3 = plane_way(castle, lair);
    }

    std::vector<Cell> Map::light_way(const Castle &castle, const Lair &lair) const {
        std::vector<Cell> way;
        std::vector<std::vector<int>> colour;
        colour.resize(max_x);
        std::vector<std::vector<int>>::iterator i;
        for (i = colour.begin(); i != colour.end(); i++) {
            i->resize(max_y);
        }
        search **que = new search *[max_x * max_y];
        int xL, yL, x, y, k, j;
        xL = lair.get_coordinate().first;
        yL = lair.get_coordinate().second;
        search start, z;
        auto *new_el = new search;
        search *end = nullptr;
        new_el->el = castle;
        new_el->weight = 0;
        new_el->previous = nullptr;
        start = *new_el;
        j = 0;
        k = 0;
        que[j] = new_el;
        k++;
        while (j < k) {
            x = que[j]->el.get_coordinate().first;
            y = que[j]->el.get_coordinate().second;
            colour[x][y] = 2;
            if (x == xL and y == yL) {
                end = que[j];
                break;
            }
            if (x - 1 > -1) {
                if ((Cells[x - 1][y].get_type() == 1 or Cells[x - 1][y].get_type() == 5) and
                    Cells[x - 1][y].get_defend() == nullptr and colour[x - 1][y] == 0) {
                    new_el = new search;
                    new_el->el = Cells[x - 1][y];
                    new_el->weight = que[j]->weight + 1;
                    new_el->previous = que[j];
                    que[k] = new_el;
                    colour[x - 1][y]++;
                    k++;
                }
            }
            if (x + 1 < max_x) {
                if ((Cells[x + 1][y].get_type() == 1 or Cells[x + 1][y].get_type() == 5) and
                    Cells[x + 1][y].get_defend() == nullptr and colour[x + 1][y] == 0) {
                    new_el = new search;
                    new_el->el = Cells[x + 1][y];
                    new_el->weight = que[j]->weight + 1;
                    new_el->previous = que[j];
                    que[k] = new_el;
                    colour[x + 1][y]++;
                    k++;
                }
            }
            if (y - 1 > -1) {
                if ((Cells[x][y - 1].get_type() == 1 or Cells[x][y - 1].get_type() == 5) and
                    Cells[x][y - 1].get_defend() == nullptr and colour[x][y - 1] == 0) {
                    new_el = new search;
                    new_el->el = Cells[x][y - 1];
                    new_el->weight = que[j]->weight + 1;
                    new_el->previous = que[j];
                    que[k] = new_el;
                    colour[x][y - 1]++;
                    k++;
                }
            }
            if (y + 1 < max_y) {
                if ((Cells[x][y + 1].get_type() == 1 or Cells[x][y + 1].get_type() == 5) and
                    Cells[x][y + 1].get_defend() == nullptr and colour[x][y + 1] == 0) {
                    new_el = new search;
                    new_el->el = Cells[x][y + 1];
                    new_el->weight = que[j]->weight + 1;
                    new_el->previous = que[j];

                    que[k] = new_el;
                    k++;
                    colour[x][y + 1]++;
                }
            }
            j++;
        }
        search *el;
        while (end != nullptr) {
            way.push_back(end->el);
            el = end;
            end = end->previous;
        }
        for (j = 0; j < k; j++) {
            delete que[j];
        }
        delete[] que;
        return way;

    }

    std::vector<Cell> Map::heavy_way(const Castle &castle, const Lair &lair) const {
        std::vector<Cell> way;
        std::vector<std::vector<int>> colour;
        colour.resize(max_x);
        std::vector<std::vector<int>>::iterator i;
        for (i = colour.begin(); i != colour.end(); i++) {
            i->resize(max_y);
        }
        search **que = new search *[max_x * max_y];
        int xL, yL, x, y, k, j;
        xL = lair.get_coordinate().first;
        yL = lair.get_coordinate().second;
        search start, z;
        auto *new_el = new search;
        search *end = nullptr;
        new_el->el = castle;
        new_el->weight = 0;
        new_el->previous = nullptr;
        start = *new_el;
        j = 0;
        k = 0;
        que[j] = new_el;
        k++;
        while (j < max_x * max_y) {
            x = que[j]->el.get_coordinate().first;
            y = que[j]->el.get_coordinate().second;
            colour[x][y] = 2;
            if (x == xL and y == yL) {
                end = que[j];
                break;
            }
            if (x - 1 > -1) {
                if ((Cells[x - 1][y].get_type() == 1 or Cells[x - 1][y].get_type() == 5) and
                    (Cells[x - 1][y].get_defend() ==
                     nullptr or (Cells[x - 1][y].get_defend() !=
                                 nullptr and Cells[x - 1][y].get_defend()->get_type() == 1)) and
                    colour[x - 1][y] == 0) {
                    new_el = new search;
                    new_el->el = Cells[x - 1][y];
                    new_el->weight = que[j]->weight + 1;
                    new_el->previous = que[j];
                    que[k] = new_el;
                    colour[x - 1][y]++;
                    k++;
                }
            }
            if (x + 1 < max_x) {
                if ((Cells[x + 1][y].get_type() == 1 or Cells[x + 1][y].get_type() == 5) and
                    Cells[x + 1][y].get_defend() == nullptr and colour[x + 1][y] == 0) {
                    new_el = new search;
                    new_el->el = Cells[x + 1][y];
                    new_el->weight = que[j]->weight + 1;
                    new_el->previous = que[j];
                    que[k] = new_el;
                    colour[x + 1][y]++;
                    k++;
                }
            }
            if (y - 1 > -1) {
                if ((Cells[x][y - 1].get_type() == 1 or Cells[x][y - 1].get_type() == 5) and
                    Cells[x][y - 1].get_defend() == nullptr and colour[x][y - 1] == 0) {
                    new_el = new search;
                    new_el->el = Cells[x][y - 1];
                    new_el->weight = que[j]->weight + 1;
                    new_el->previous = que[j];
                    que[k] = new_el;
                    colour[x][y - 1]++;
                    k++;
                }
            }
            if (y + 1 < max_y) {
                if ((Cells[x][y + 1].get_type() == 1 or Cells[x][y + 1].get_type() == 5) and
                    Cells[x][y + 1].get_defend() == nullptr and colour[x][y + 1] == 0) {
                    new_el = new search;
                    new_el->el = Cells[x][y + 1];
                    new_el->weight = que[j]->weight + 1;
                    new_el->previous = que[j];

                    que[k] = new_el;
                    k++;
                    colour[x][y + 1]++;
                }
            }
            j++;
        }
        search *el;
        while (end != nullptr) {
            way.push_back( end->el);
            el = end;
            end = end->previous;
        }
        for (j = 0; j < k; j++) {
            delete que[j];
        }
        delete[] que;
        return way;
    }

    std::vector<Cell> Map::plane_way(const Castle &castle, const Lair &lair) const {
        std::vector<Cell> way;
        std::vector<std::vector<int>> colour;
        colour.resize(max_x);
        std::vector<std::vector<int>>::iterator i;
        for (i = colour.begin(); i != colour.end(); i++) {
            i->resize(max_y);
        }
        search **que = new search *[max_x * max_y];
        int xL, yL, x, y, k, j;
        xL = lair.get_coordinate().first;
        yL = lair.get_coordinate().second;
        search start, z;
        auto *new_el = new search;
        search *end = nullptr;
        new_el->el = castle;
        new_el->weight = 0;
        new_el->previous = nullptr;
        start = *new_el;
        j = 0;
        k = 0;
        que[j] = new_el;
        k++;
        while (j < max_x * max_y) {
            x = que[j]->el.get_coordinate().first;
            y = que[j]->el.get_coordinate().second;
            colour[x][y] = 2;
            if (x == xL and y == yL) {
                end = que[j];
                break;
            }
            if (x - 1 > -1) {
                if ((Cells[x - 1][y].get_type() == 1 or Cells[x - 1][y].get_type() == 5 or
                     Cells[x - 1][y].get_type() == 3) and colour[x - 1][y] == 0) {
                    new_el = new search;
                    new_el->el = Cells[x - 1][y];
                    new_el->weight = que[j]->weight + 1;
                    new_el->previous = que[j];
                    que[k] = new_el;
                    colour[x - 1][y]++;
                    k++;
                }
            }
            if (x + 1 < max_x) {
                if ((Cells[x + 1][y].get_type() == 1 or Cells[x + 1][y].get_type() == 5 or
                     Cells[x + 1][y].get_type() == 3) and colour[x + 1][y] == 0) {
                    new_el = new search;
                    new_el->el = Cells[x + 1][y];
                    new_el->weight = que[j]->weight + 1;
                    new_el->previous = que[j];
                    que[k] = new_el;
                    colour[x + 1][y]++;
                    k++;
                }
            }
            if (y - 1 > -1) {
                if ((Cells[x][y - 1].get_type() == 1 or Cells[x][y - 1].get_type() == 5 or
                     Cells[x][y - 1].get_type() == 3) and colour[x][y - 1] == 0) {
                    new_el = new search;
                    new_el->el = Cells[x][y - 1];
                    new_el->weight = que[j]->weight + 1;
                    new_el->previous = que[j];
                    que[k] = new_el;
                    colour[x][y - 1]++;
                    k++;
                }
            }
            if (y + 1 < max_y) {
                if ((Cells[x][y + 1].get_type() == 1 or Cells[x][y + 1].get_type() == 5 or
                     Cells[x][y + 1].get_type() == 3) and colour[x][y + 1] == 0) {
                    new_el = new search;
                    new_el->el = Cells[x][y + 1];
                    new_el->weight = que[j]->weight + 1;
                    new_el->previous = que[j];

                    que[k] = new_el;
                    k++;
                    colour[x][y + 1]++;
                }
            }
            j++;
        }
        search *el;
        while (end != nullptr) {
            way.push_back(end->el);
            el = end;
            end = end->previous;
        }
        for (j = 0; j < k; j++) {
            delete que[j];
        }
        delete[] que;
        return way;
    }

    void Map::draw_to_terminal() {
        int t;
        std::cout << "|  |";
        for (int i = 0; i < max_x; i++) {
            std::cout << i << "|";
        }
        std::cout << std::endl;

        for (int i = 0; i < max_y; i++) {
            if (i < 10) {
                std::cout << " ";
            }
            std::cout << "|" << i << "|";
            for (int j = 0; j < max_x; j++) {
                t = get_map()[j][i].get_type();
                switch (t) {
                    case 0:
                        break;
                    case 1:
                        std::cout << "P";
                        break;
                    case 2:
                        std::cout << "M";
                        break;
                    case 3:
                        std::cout << "W";
                        break;
                    case 4:
                        std::cout << "C";
                        break;
                    case 5:
                        std::cout << "L";
                        break;
                }
                if (j > 9) {
                    std::cout << " ";
                }
                std::cout << "|";
            }
            std::cout << std::endl;
        }
    }

    void Map::draw() {
        int t;
        std::vector<Cell>::iterator way,next;
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

