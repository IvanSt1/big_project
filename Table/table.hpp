//
// Created by ivan on 27.11.2021.
//
/*!
 * @file Table
 * @brief The header file that represents the imlementation of the templzte class Table
 */
#ifndef BIG_PROJECT_TABLE_HPP
#define BIG_PROJECT_TABLE_HPP

#include <utility>
#include <stdexcept>
/*!
 *@brief The namespace in which the file is implemented
 * contain all information about
 * table, methods, iterators and etc.
 */
namespace My_table {
    /*!
     *@brief Class Table
     * @tparam Key Any type of data that is a key
     * @tparam Info Any type of data that is an info
     * @param mas An Array consisting of n number of elements pair <Key, Info>
     * @param n Number of elements
     */
    template<typename Key, typename Info>
    class Table {
    private:
        std::pair<Key, Info> *mas;
        int n;
    public:
        /*!
         * @brief Class Iterator
         * @param cur points to the element
         */
        class iterator {
        private:
            std::pair<Key, Info> *cur;
        public:
            /*!
             * Default constructor
             */
            iterator() : cur(0) {};

            /*!
             * Construcotor from pair
             * @param pair which is pointed by cur
             */
            iterator(std::pair<Key, Info> pair) { *cur = pair; };

            /*!
             * Construcotor from iterator
             * @param other iterator
             */
            iterator(const iterator &other) : cur(other.cur) {};

            /*!
             * = operator overload
             * @param other iterator
             * @return
             */
            iterator &operator=(iterator other) {
                cur = other.cur;
                return *this;
            }

            /*!
             * prefix ++ operator overload
             * @return new iterator
             */
            iterator &operator++() {
                ++cur;
                return *this;
            }

            /*!
             * postfix ++ operator overload
             * @return new iterator
             */
            iterator &operator++(int) {
                iterator res(*this);
                ++(*this);
                return res;
            }

            /*!
             * + operator overload
             * @param k
             * @return new iterator
             */
            iterator &operator+(int k) {
                iterator res(cur + k);
                return res;
            }

            /*!
             * += operator overload
             * @param k
             * @return new iterator
             */
            iterator &operator+=(int k) {
                cur += k;
                return *this;
            }

            /*!
             * prefix -- operator overload
             * @return new iterator
             */
            iterator &operator--() {
                --cur;
                return *this;
            }

            /*!
             * postfix ++ operator overload
             * @return new iterator
             */
            iterator &operator--(int) {
                iterator res(*this);
                --(*this);
                return res;
            }

            /*!
             * - operator overload
             * @param k
             * @return new iterrator
             */
            iterator &operator-(int k) {
                iterator res(cur + k);
                return *res;
            }

            /*!
             * -= operator overload
             * @param k
             * @return new iterator
             */
            iterator &operator-=(int k) {
                cur -= k;
                return this;
            }

            /*!
             *  != operator overload
             * @param other itertator which one compare
             * @return bool
             */
            bool operator!=(const iterator &other) const { return cur != other.cur; }

            /*!
             *  == operator overload
             * @param other itertator which one compare
             * @return bool
             */
            bool operator==(const iterator &other) const { return cur == other.cur; }

            /*!
             * * operator overload
             * @return pointer to a pair
             */
            std::pair<Key, Info> &operator*() { return (*cur); }

            /*!
             * -> operator overload
             * @return pair
             */
            std::pair<Key, Info> &operator->() { return cur; }

            /*!
             *  > operator overload
             * @param other itertator which one compare
             * @return bool
             */
            bool operator>(const iterator &other) const { return cur > other.cur; }

            /*!
             *  < operator overload
             * @param other itertator which one compare
             * @return bool
             */
            bool operator<(const iterator &other) const { return cur < other.cur; }

            /*!
             *  >= operator overload
             * @param other itertator which one compare
             * @return bool
             */
            bool operator>=(const iterator &other) const { return cur >= other.cur; }

            /*!
             *  <= operator overload
             * @param other itertator which one compare
             * @return bool
             */
            bool operator<=(const iterator &other) const { return cur <= other.cur; }
        };

        /*!
         * Default constructor
         */
        Table() {
            mas = nullptr;
            n = 0;
        }

        /*!
         * find first element
         * @return iterator pointing to the first element
         */
        iterator begin() { return iterator(*mas); }

        /*!
         * end of mas
         * @return iterator pointing to the end of mas
         */
        iterator end() { return iterator(*(mas + n)); }

        /*!
         * Add new element to the end
         * @param key1 Key
         * @param info1 Info
         */
        void insert(Key key1, Info info1);

        /*!
         * Add new element to the end
         * @param pair Pair consists of Key and Info
         */

        void insert(std::pair<Key, Info> pair);

        /*!
         * find element by key
         * @param key1 key that you want to find
         * @return iterator pointing to the desired element if there is no such key returns end
         */
        iterator find(Key key1) {
            iterator x;
            for (x = this->begin(); x != this->end(); ++x) {
                if ((*x).first == key1) {
                    break;
                }
            }
            return x;
        }

        /*!
         * Default destructor
         */
        ~Table();
    };


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
    Table<Key, Info>::~Table() = default;
}

#endif //BIG_PROJECT_TABLE_HPP
