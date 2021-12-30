#include "Database.h"

int main(){
    Database *db = new Database();//make the database
    db->RunDatabase();//run the database
    delete db;//delete the database

    return 0;
}