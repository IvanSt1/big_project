#include <iostream>
#include "Map/map.hpp"
int main() {
    int x,y;
    x=5;
    y=5;
    map1::Map karta(x,y,1);
    karta.play();
    return 0;
}
