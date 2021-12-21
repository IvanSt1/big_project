#include "SFML/Graphics.hpp"
#include "map.hpp"

int main() {
    int x, y;
    x = 15;
    y = 15;
    bool add_tower = false, add_wall = false, upgrade = false;
    int x1, y1, x2, y2;
    sf::RenderWindow window(sf::VideoMode(x * 64 + 100, y * 64), "Tower_defence");

    sf::RectangleShape rectangle(sf::Vector2f(400.f, 150.f));
    rectangle.setFillColor(sf::Color::Red);

    sf::Font font;//шрифт
    font.loadFromFile("../Map/Image/CyrilicOld.TTF");

    sf::Text text_tower("TOWER", font, 50);
    text_tower.setStyle(sf::Text::Bold);
    text_tower.setPosition(100, 100);

    sf::Text text_wall("WALL", font, 50);
    text_wall.setStyle(sf::Text::Bold);
    text_wall.setPosition(100, 300);

    sf::Text text_upgrade("Upgrade", font, 50);
    text_upgrade.setStyle(sf::Text::Bold);
    text_upgrade.setPosition(100, 500);


    sf::Text text_hp("HP", font, 30);
    text_hp.setStyle(sf::Text::Bold);
    sf::Text text_money("Money", font, 30);
    text_money.setStyle(sf::Text::Bold);

    sf::Text hp("", font, 30);
    hp.setStyle(sf::Text::Bold);
    sf::Text money("", font, 30);
    money.setStyle(sf::Text::Bold);

    sf::Sprite sprite, enemy_sprite, potracheno, wall_sprite, tower_sprite;

    sf::Image plain_image, water_image, mountain_image, castle_image, lair_image, light_image, heavy_image, plane_image, potracheno_image, wall_image, tower_image;
    plain_image.loadFromFile("../Map/Image/plain.png");
    water_image.loadFromFile("../Map/Image/water.png");
    mountain_image.loadFromFile("../Map/Image/mountain.png");
    castle_image.loadFromFile("../Map/Image/castle.png");
    lair_image.loadFromFile("../Map/Image/lair.png");
    light_image.loadFromFile("../Map/Image/Light.png");
    heavy_image.loadFromFile("../Map/Image/Heavy.png");
    plane_image.loadFromFile("../Map/Image/plane.png");
    potracheno_image.loadFromFile("../Map/Image/potracheno.png");
    wall_image.loadFromFile("../Map/Image/Wall.png");
    tower_image.loadFromFile("../Map/Image/Tower.png");

    sf::Texture plain_texture, water_texture, mountain_texture, castle_texture, lair_texture, light_texture, heavy_texture, plane_texture, potracheno_texture, wall_texture, tower_texture;
    plain_texture.loadFromImage(plain_image);
    water_texture.loadFromImage(water_image);
    mountain_texture.loadFromImage(mountain_image);
    castle_texture.loadFromImage(castle_image);
    lair_texture.loadFromImage(lair_image);
    light_texture.loadFromImage(light_image);
    heavy_texture.loadFromImage(heavy_image);
    plane_texture.loadFromImage(plane_image);
    potracheno_texture.loadFromImage(potracheno_image);
    wall_texture.loadFromImage(wall_image);
    tower_texture.loadFromImage(tower_image);

    wall_sprite.setTexture(wall_texture);
    tower_sprite.setTexture(tower_texture);

    potracheno.setTexture(potracheno_texture);
    potracheno.setPosition(32 * x - 384, 32 * y - 216);

    map1::Map karta(x, y);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        int t;
        if (karta.get_hp() > 0) {
            window.clear();
            for (int i = 0; i < karta.get_max_x(); i++) {
                for (int j = 0; j < karta.get_max_y(); j++) {
                    t = karta.get_map()[j][i].get_type();
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
                    if (karta.get_map()[j][i].get_defend() != nullptr) {
                        wall_sprite.setPosition(j * 64, i * 64);
                        window.draw(wall_sprite);
                    }
                }
            }

            std::vector<Enemy::Enemies *> enemies = karta.get_enemies();
            for (auto i: enemies) {
                switch (i->get_type()) {
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
                    case 4:
                        break;
                }
                enemy_sprite.setPosition(i->get_coor().first * 64 + 8, i->get_coor().second * 64 + 8);
                window.draw(enemy_sprite);
            }

            std::vector<Tower *> towers = karta.get_towers();
            for (auto i: towers) {
                tower_sprite.setPosition(i->get_coor().first * 64 + 16, i->get_coor().second * 64 + 16);
                window.draw(tower_sprite);
            }
            text_hp.setFillColor(sf::Color::Red);
            text_hp.setPosition(64 * x + 1, 50);
            text_money.setFillColor(sf::Color::Red);
            text_money.setPosition(64 * x + 1, 150);
            hp.setString(std::to_string(karta.get_hp()));
            money.setString(std::to_string(karta.get_money()));

            hp.setPosition(64 * x + 1, 100);
            money.setPosition(64 * x + 1, 200);
            window.draw(hp);
            window.draw(money);
            window.draw(text_hp);
            window.draw(text_money);
            window.display();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                x1 = sf::Mouse::getPosition(window).x;
                y1 = sf::Mouse::getPosition(window).y;
                sf::RenderWindow window1(sf::VideoMode(500, 700), "Choose option");
                while (window1.isOpen()) {
                    sf::Event event1{};
                    while (window1.pollEvent(event1)) {
                        if (event1.type == sf::Event::Closed)
                            window1.close();
                    }

                    rectangle.setPosition(50, 50);
                    window1.draw(rectangle);
                    rectangle.setPosition(50, 250);
                    window1.draw(rectangle);
                    rectangle.setPosition(50, 450);
                    window1.draw(rectangle);

                    window1.draw(text_upgrade);
                    window1.draw(text_tower);
                    window1.draw(text_wall);
                    window1.display();
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                        x2 = sf::Mouse::getPosition(window1).x;
                        y2 = sf::Mouse::getPosition(window1).y;
                        add_tower = (x2 >= 50 and x2 <= 500 and y2 >= 50 and y2 <= 200);
                        add_wall = (x2 >= 50 and x2 <= 500 and y2 >= 250 and y2 <= 400);
                        upgrade = (x2 >= 50 and x2 <= 500 and y2 >= 450 and y2 <= 600);
                        window1.close();
                    }
                }
            }


            karta.play(1, add_tower, add_wall, upgrade, int(x1 / 64), int(y1 / 64));
            add_tower = false;
            add_wall = false;
            upgrade = false;
        } else {
            window.clear();
            window.draw(potracheno);
            window.display();
        }
    }

}


