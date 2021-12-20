#include <iostream>
#include <vector>
#include "table.hpp"
int main(){
    My_table::Table<int, std::vector<int>> t;
    t.insert(1, {200, 1, 10, 10});
    t.insert(2, {200, 2, 15, 15});
    t.insert(3, {400, 2, 20, 20});
    t.insert(4, {500, 3, 30, 30});
    t.insert(5, {600, 3, 40, 40});
    My_table::Table<int,std::vector<int>>::iterator x;
    t.erase(1);
    return 0;
}