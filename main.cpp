#include <iostream>
#include "Map/map.hpp"
int main() {
    int x,y;
    x=5;
    y=5;
    map1::Map karta(x,y);
    karta.play();
    return 0;
}
