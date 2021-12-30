#include "Person.h"
//overloaded operators just comparing the id of the two persons, since in implementation, no 2 persons can have same id
bool operator==(Person& p1, Person& p2){
    return p1.ID == p2.ID;
}
bool operator!=(Person& p1, Person& p2){
    return p1.ID != p2.ID;
}
bool operator<(Person& p1, Person& p2){
    return p1.ID < p2.ID;
}
bool operator>(Person& p1, Person& p2){
    return p1.ID > p2.ID;
}
bool operator==(Person& p1, int p2){
    return p1.ID == p2;
}
bool operator!=(Person& p1, int p2){
    return p1.ID != p2;
}
bool operator<(Person& p1, int p2){
    return p1.ID < p2;
}
bool operator>(Person& p1, int p2){
    return p1.ID > p2;
}
bool operator==(int p1, Person& p2){
    return p1 == p2.ID;
}
bool operator!=(int p1, Person& p2){
    return p1 != p2.ID;
}
bool operator<(int p1, Person& p2){
    return p1 < p2.ID;
}
bool operator>(int p1, Person& p2){
    return p1 > p2.ID;
}