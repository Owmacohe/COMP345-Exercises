#include "Map.h"
#include "../Player/Player.h"

#include "../Cards/Cards.cpp"
#include "Map.cpp"
#include "../Orders/Orders.cpp"
#include "../Player/Player.cpp"

int mapDriver() {
    const int len = 5;
    string *files = new string[len]{"canada.map", "europe.map", "LOTR2.map", "usa8regions.map", "solar.map"};
    MapLoader loader;

    for (int i = 0; i < len; i++) {
        cout << endl;
        Map temp = loader.load(files[i]);

        if (temp.isGoodMap) {
            cout << endl;
            cout << temp << endl;
            cout << endl;
            temp.validate();
        }

        cout << "\n==========" << endl;
    }

    delete[] files;
    files = NULL;

    return 0;
}