#include <iostream>
#include "table.hpp"

int main(){
    Table<int,int> t;
    t.insert(1,1);
    t.insert(2,2);
    Table<int,int>::iterator j(t.begin());
    std::cout<<(*j).first;
    for(auto i:t){
        std::cout<<i.first;
    }
    return 0;
}
