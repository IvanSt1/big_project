//
// Created by ivan on 27.11.2021.
//

#ifndef BIG_PROJECT_TABLE_HPP
#define BIG_PROJECT_TABLE_HPP
template<typename Key, typename Info>
class Table {
private:
    struct Elem{
        Key key;
        Info info;
    };
    Elem * mas;
    int n;
public:
    Table();
    void push(Key key1, Info info1);
    Info find(Key key1);
    ~Table();
};

template<typename Key, typename Info>
Table<Key, Info>::Table() {
    mas = nullptr;
    n = 0;
}

template<typename Key, typename Info>
void Table<Key, Info>::push(Key key1, Info info1) {
    Elem new_elem{};
    Elem* new_mas = new Elem[n+1];
    for (int i=0;i<n;i++){
        new_mas[i]=mas[i];
    }
    delete[] mas;
    mas=new_mas;
    new_elem.key=key1;
    new_elem.info=info1;
    mas[n]=new_elem;
    n++;
}

template<typename Key, typename Info>
Info Table<Key, Info>::find(Key key1) {
    Info x;
    int i;
    for(i=0;i<n;i++){
        if(mas[i].key==key1){
            x=mas[i].info;
        }
    }
    if(i == n){
        throw(std::runtime_error("Not Found"));
    }
    return x;
}

template<typename Key, typename Info>
Table<Key, Info>::~Table() {
    delete[] mas;
}

#endif //BIG_PROJECT_TABLE_HPP
