//
// Created by ivan on 27.11.2021.
//

#ifndef BIG_PROJECT_TABLE_HPP
#define BIG_PROJECT_TABLE_HPP

template<typename Key, typename Info>
class Table {
private:
    std::pair<Key, Info> *mas;
    int n;
public:
    class iterator;

    Table();

    iterator begin() { return mas; }

    iterator end() { return mas + n; }

    void insert(Key key1, Info info1);

    void insert(std::pair<Key, Info>);

    Info find(Key key1);

    ~Table();

    class iterator {
        std::pair<Key, Info> *cur;
    public:
        iterator(std::pair<Key, Info> *first) : cur(first) {};

        std::pair<Key, Info> &operator+(int k) { return *(cur + k); }

        std::pair<Key, Info> &operator-(int k) { return *(cur - k); }

        std::pair<Key, Info> &operator++() { return *cur++; }

        std::pair<Key, Info> &operator--() { return *cur--; }

        bool operator!=(const iterator &it) { return cur != it.cur; }

        bool operator==(const iterator &it) { return cur == it.cur; }

        std::pair<Key, Info> &operator*() { return *cur; }
    };
};

template<typename Key, typename Info>
Table<Key, Info>::Table() {
    mas = nullptr;
    n = 0;
}

template<typename Key, typename Info>
void Table<Key, Info>::insert(Key key1, Info info1) {
    std::pair<Key, Info> new_elem;
    auto *new_mas = new std::pair<Key, Info>[n + 1];
    for (int i = 0; i < n; i++) {
        new_mas[i] = mas[i];
    }
    delete[] mas;
    mas = new_mas;
    new_elem.first = key1;
    new_elem.second = info1;
    mas[n] = new_elem;
    n++;
}

template<typename Key, typename Info>
void Table<Key, Info>::insert(std::pair<Key, Info> new_elem) {
    std::pair<Key, Info> *new_mas;
    new_mas = new std::pair<Key, Info>[n + 1];
    for (int i = 0; i < n; i++) {
        new_mas[i] = mas[i];
    }
    delete[] mas;
    mas = new_mas;
    mas[n] = new_elem;
    n++;
}

template<typename Key, typename Info>
Info Table<Key, Info>::find(Key key1) {
    Info x;
    int i;
    for (i = 0; i < n; i++) {
        if (mas[i].first == key1) {
            x = mas[i].second;
            break;
        }
    }
    if (i == n) {
        throw (std::runtime_error("Not Found"));
    }
    return x;
}

template<typename Key, typename Info>
Table<Key, Info>::~Table()=default;



#endif //BIG_PROJECT_TABLE_HPP
