#include <iostream>
#include "Map/map.hpp"
int main() {
    int x,y;
    x=15;
    y=15;
    map1::Map karta(x,y);
    karta.play();
    return 0;
}
