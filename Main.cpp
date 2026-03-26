#include <iostream>
#include <vector>
#include <string>
#include "SpaceDatabase.h"
#include "Utilities.h"
#include "MenuFunctions.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");

    SpaceDatabase db;
    int choice;

    cout << "\033[38;2;220;89;39mLoading resources!\033[0m\n";
    db.loadAllData();
    pressEnterToContinue();

    do {
        clearScreen();
        vector<string> startupMessages = { "Updating data...", "Accessing the on-board computer..." };
        loaderSequence(startupMessages);
        clearScreen();

        cout << "\"\033[0m\033[38;2;220;89;39m SOLAR TALES \033[0m\"\n\n";
        cout << "\033[38;2;220;89;39mMain Menu:\033[0m\n";
        cout << "\033[38;2;220;69;40m- 1 -\033[0m \033[38;2;220;89;39mAdd data\033[0m\n";
        cout << "\033[38;2;220;69;40m- 2 -\033[0m \033[38;2;220;89;39mView data\033[0m\n";
        cout << "\033[38;2;220;69;40m- 3 -\033[0m \033[38;2;220;89;39mDelete data\033[0m\n";
        cout << "\033[38;2;220;69;40m- 4 -\033[0m \033[38;2;220;89;39mSearch/Filter\033[0m\n";
        cout << "\033[38;2;220;69;40m- 5 -\033[0m \033[38;2;220;89;39mSummary\033[0m\n";
        cout << "\033[38;2;220;69;40m- 6 -\033[0m \033[38;2;220;89;39mSort\033[0m\n";
        cout << "\033[38;2;220;69;40m- 7 -\033[0m \033[38;2;220;89;39mSave and Exit\033[0m\n";
        cout << "\n\033[38;2;220;69;40mEnter Your choice : \033[0m\033[38;2;201;218;190m";
        cin >> choice;

        switch (choice) {
        case 1: {
            int subChoice;
            clearScreen();
            cout << "\"\033[0m\033[38;2;220;89;39m SOLAR TALES \033[0m\"\n\n";
            cout << "\033[38;2;220;89;39mAdd Data Menu:\033[0m\n";
            cout << "\033[38;2;220;69;40m- 1 -\033[0m\033[38;2;220;89;39m PLANET\033[0m\n";
            cout << "\033[38;2;220;69;40m- 2 -\033[0m\033[38;2;220;89;39m SATELLITE\033[0m\n";
            cout << "\033[38;2;220;69;40m- 3 -\033[0m\033[38;2;220;89;39m Back\033[0m\n";
            cout << "\n\033[38;2;220;69;40mEnter Your choice : \033[0m\033[38;2;201;218;190m";
            cin >> subChoice;

            if (subChoice == 1) addPlanetMenu(db);
            else if (subChoice == 2) addSatelliteMenu(db);
            break;
        }
        case 2:
            clearScreen();
            cout << "\"\033[0m\033[38;2;220;89;39m SOLAR TALES \033[0m\"\n\n";
            cout << "\033[38;2;220;69;40m=== \033[0m\033[38;2;220;89;39mViewing Data\033[0m \033[38;2;220;69;40m===\033[0m\n\n";
            db.displayAllData();
            pressEnterToContinue();
            break;
        case 3:
            deleteDataMenu(db);
            break;
        case 4: {
            clearScreen();
            cout << "\"\033[0m\033[38;2;220;89;39m SOLAR TALES \033[0m\"\n\n";
            cout << "\033[38;2;220;69;40m=== \033[0m\033[38;2;220;89;39mSearch\033[0m \033[38;2;220;69;40m===\033[0m\n\n";

            if (db.isEmpty()) {
                cout << "\033[0m\033[38;2;220;40;40mDatabase is empty.\033[0m\n";
                pressEnterToContinue();
                break;
            }

            string searchName;
            cout << "\033[0m\033[38;2;220;69;40mEnter name for search: \033[0m\033[38;2;201;218;190m";
            cin.ignore();
            getline(cin, searchName);
            db.searchByName(searchName);
            pressEnterToContinue();
            break;
        }
        case 5:
            clearScreen();
            cout << "\"\033[0m\033[38;2;220;89;39m SOLAR TALES \033[0m\"\n\n";
            cout << "\033[38;2;220;69;40m=== \033[0m\033[38;2;220;89;39mStatistics\033[0m \033[38;2;220;69;40m===\033[0m\n\n";
            db.showStatistics();
            pressEnterToContinue();
            break;
        case 6: {
            clearScreen();
            cout << "\"\033[0m\033[38;2;220;89;39m SOLAR TALES \033[0m\"\n\n";
            cout << "\033[38;2;220;69;40m=== \033[0m\033[38;2;220;89;39mData Sorting\033[0m \033[38;2;220;69;40m===\033[0m\n\n";
            cout << "\033[38;2;220;69;40m1 - \033[0m\033[38;2;220;89;39mSort planets by name\033[0m\n";
            cout << "\033[38;2;220;69;40m2 - \033[0m\033[38;2;220;89;39mSort planets by age\033[0m\n";
            cout << "\033[38;2;220;69;40m3 - \033[0m\033[38;2;220;89;39mSort planets by temperature\033[0m\n";
            cout << "\033[38;2;220;69;40m4 - \033[0m\033[38;2;220;89;39mSort satellites by name\033[0m\n";
            cout << "\033[38;2;220;69;40m5 - \033[0m\033[38;2;220;89;39mSort satellites by planet\033[0m\n";
            cout << "\033[38;2;220;69;40m6 - \033[0m\033[38;2;220;89;39mBack\033[0m\n";
            cout << "\033[38;2;220;69;40mYour choice: \033[0m\033[38;2;201;218;190m";

            int sortChoice;
            cin >> sortChoice;

            switch (sortChoice) {
            case 1: db.sortPlanetsByName(); cout << "\033[0m\033[38;2;220;89;39mPlanets sorted by name.\033[0m\n"; break;
            case 2: db.sortPlanetsByAge(); cout << "\033[0m\033[38;2;220;89;39mPlanets sorted by age.\033[0m\n"; break;
            case 3: db.sortPlanetsByTemperature(); cout << "\033[0m\033[38;2;220;89;39mPlanets sorted by temperature.\033[0m\n"; break;
            case 4: db.sortSatellitesByName(); cout << "\033[0m\033[38;2;220;89;39mSatellites sorted by name.\033[0m\n"; break;
            case 5: db.sortSatellitesByPlanet(); cout << "\033[0m\033[38;2;220;89;39mSatellites sorted by planet.\033[0m\n"; break;
            default: cout << "\033[38;2;220;40;40mInvalid choice.\033[0m\n";
            }
            pressEnterToContinue();
            break;
        }
        case 7:
            db.saveAllData();
            clearScreen();
            cout << "\033[0m\033[38;2;220;89;39mData saved. May the great cosmos guide you. See you tomorrow!\033[0m\n";
            break;
        default:
            cout << "\033[38;2;220;40;40mSeems like you've made a mistake. Try again.\033[0m\n";
            pressEnterToContinue();
        }
    } while (choice != 7);

    return 0;
}