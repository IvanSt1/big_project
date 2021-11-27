//
// Created by ivan on 05.11.2021.
//

#ifndef BIG_PROJECT_DEFENDER_HPP
#define BIG_PROJECT_DEFENDER_HPP

#include <vector>
#include <stdexcept>
#include "../Enemys/enemy.hpp"
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

namespace Defend {
    class Defender {
    protected:
        int type{};
    public:
        virtual int atack(int) = 0;
        int get_type() const{
            return type;
        }
        virtual int atack(std::vector<Enemy::Enemies>) = 0;

        virtual void levelup() = 0;
    };

    class Wall : public Defender {
    private:
        int max_hp;
        int hp;

    public:
        Wall();
        int atack(int damage) override;
    };

    class Tower : public Defender {
    private:
        int level;
        int price;
        int radius;
        int damage;
        int speed;
    public:
        Tower() {
            type = 2;
            radius = 0;
            damage = 0;
            speed = 0;
            price=100;
            level=0;
        };
        Tower(Table <int, std::vector<int>> table){
            type=2;
            level=1;
            std:: vector<int> mas=table.find(1);
            price=mas[0];
            radius=mas[1];
            damage=mas[2];
            speed=mas[3];
        }
        void levelup() override;

        int atack(std::vector<Enemy::Enemies>) override;
    };
}
#endif //BIG_PROJECT_DEFENDER_HPP
