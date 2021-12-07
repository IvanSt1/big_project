#include <iostream>
#include "table.hpp"
int main(){
    My_table::Table<int, int> t;
    t.insert(1, 1);
    t.insert(2, 3);
    t.insert(3, 4);
    t.insert(4, 5);
    t.insert(5, 6);
    auto x=t.find(5);
    if(x==t.end()){
        std::cout<<" ничего";
    }
    else {
        std::cout << (*x).first << (*x).second;
    }
    return 0;
}