#include "SFML/Graphics.hpp"
#include "map.hpp"

int main() {
    int x, y;
    x = 15;
    y = 15;
    sf::RenderWindow window(sf::VideoMode(x * 64, y * 64), "Tower_defence");
    sf::Sprite sprite;
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
    map1::Map karta(x, y);
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        int t;
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
            }
        }
        std::vector<Enemy::Enemies*> enemies=karta.get_enemies();
        std::vector<Enemy::Enemies*>::iterator i;
        for(auto i:enemies){
            switch (i->get_type()){
                case 0:
                    break;
                case 1:
                    sprite.setTexture(light_texture);
                    break;
                case 2:
                    sprite.setTexture(heavy_texture);
                    break;
                case 3:
                    sprite.setTexture(plain_texture);
                    break;
                case 4:
                    break;
            }
            sprite.setPosition(i->get_coor().first*64,i->get_coor().second*64);
            window.draw(sprite);
        }
        window.display();
        karta.play(1,false, false,0,0,0,0);
    }

}


