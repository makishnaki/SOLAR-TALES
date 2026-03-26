#include "MenuFunctions.h"
#include "Utilities.h"
#include <iostream>
#include <memory>

using namespace std;

// Меню добавления планеты
void addPlanetMenu(SpaceDatabase& db) {
    clearScreen();
    cout << "\n\033[38;2;220;69;40m===\033[0m \033[38;2;220;89;39mAdding planet\033[0m \033[38;2;220;69;40m===\033[0m\n";

    string name;
    cout << "\033[38;2;220;69;40mEnter the name of the planet: \033[0m\033[38;2;201;218;190m";
    cin.ignore();
    getline(cin, name);

    if (db.planetExists(name)) {
        cout << "\033[0m\033[38;2;220;40;40mError: planet with this name already exists!\033[0m\n";
        pressEnterToContinue();
        return;
    }

    int age, temperature;
    string color, description;

    cout << "\033[0m\033[38;2;220;69;40mEnter the age of the planet (in millions of years): \033[0m\033[38;2;201;218;190m";
    cin >> age;
    cout << "\033[0m\033[38;2;220;69;40mEnter average temperature (in °C): \033[0m\033[38;2;201;218;190m";
    cin >> temperature;
    cout << "\033[0m\033[38;2;220;69;40mEnter the main colour of the planet: \033[0m\033[38;2;201;218;190m";
    cin.ignore();
    getline(cin, color);
    cout << "\033[0m\033[38;2;220;69;40mEnter general description: \033[0m\033[38;2;201;218;190m";
    getline(cin, description);

    auto planet = make_unique<Planet>(name, age, temperature, color, description);
    db.addPlanet(move(planet));

    cout << "\n\033[0m\033[38;2;220;89;39mPlanet \033[0m\033[38;2;220;107;40m\"" << name
        << "\"\033[0m \033[38;2;220;89;39msuccessfully added!\033[0m\n";
    pressEnterToContinue();
}

// Меню добавления спутника
void addSatelliteMenu(SpaceDatabase& db) {
    if (db.getPlanets().empty()) {
        cout << "\n\033[0m\033[38;2;220;40;40mError: you need to have at least one planet!\033[0m\n";
        db.showPlanetsList();
        pressEnterToContinue();
        return;
    }

    clearScreen();
    cout << "\n\033[38;2;220;69;40m===\033[0m \033[38;2;220;89;39mAdding Satellite\033[0m \033[38;2;220;69;40m===\033[0m\n";

    string name;
    cout << "\033[0m\033[38;2;220;69;40mEnter the name of the satellite: \033[0m\033[38;2;201;218;190m";
    cin.ignore();
    getline(cin, name);

    if (db.satelliteExists(name)) {
        cout << "\033[0m\033[38;2;220;40;40mError: satellite with this name already exists!\033[0m\n";
        pressEnterToContinue();
        return;
    }

    int age, temperature;
    string color, description, planetName;

    cout << "\033[0m\033[38;2;220;69;40mEnter the age of the satellite (in millions of years): \033[0m\033[38;2;201;218;190m";
    cin >> age;
    cout << "\033[0m\033[38;2;220;69;40mEnter average temperature (in °C): \033[0m\033[38;2;201;218;190m";
    cin >> temperature;
    cout << "\033[0m\033[38;2;220;69;40mEnter the main colour of the satellite: \033[0m\033[38;2;201;218;190m";
    cin.ignore();
    getline(cin, color);
    cout << "\033[0m\033[38;2;220;69;40mEnter general description: \033[0m\033[38;2;201;218;190m";
    getline(cin, description);

    bool validPlanet = false;
    do {
        cout << "\n\033[0m\033[38;2;220;89;39mTo which planet does this satellite belong?\033[0m\n";
        db.showPlanetsList();
        cout << "\n\033[0m\033[38;2;220;69;40mEnter the name of the planet: \033[0m\033[38;2;201;218;190m";
        getline(cin, planetName);

        if (db.planetExists(planetName)) {
            validPlanet = true;
        }
        else {
            cout << "\n\033[38;2;220;40;40mError: planet \033[0m\033[38;2;220;107;40m\"" << planetName << "\" \033[0m\033[38;2;220;40;40mdoes not exist!\033[0m\n";
            cout << "\033[38;2;220;89;39mPlease enter a name from the list above.\033[0m\n";
        }
    } while (!validPlanet);

    auto satellite = make_unique<Satellite>(name, age, temperature, color, description, planetName);
    db.addSatellite(move(satellite));

    cout << "\n\033[38;2;220;89;39mSatellite \033[0m\033[38;2;220;107;40m\"" << name
        << "\"\033[0m\033[38;2;220;89;39m successfully added!\033[0m\n";
    pressEnterToContinue();
}

// Меню удаления данных
void deleteDataMenu(SpaceDatabase& db) {
    clearScreen();
    cout << "\"\033[38;2;220;89;39m SOLAR TALES \033[0m\"\n\n";
    cout << "\033[38;2;220;69;40m===\033[0m \033[38;2;220;89;39mData Destruction\033[0m \033[38;2;220;69;40m===\033[0m\n\n";

    if (db.isEmpty()) {
        cout << "\033[38;2;220;89;39mNo data to destroy.\033[0m\n";
        pressEnterToContinue();
        return;
    }

    int choice;
    cout << "\033[38;2;220;89;39mWhat do you wish to destroy?\033[0m\n";
    cout << "\033[38;2;220;69;40m1 - \033[0m\033[38;2;220;89;39mPlanet\033[0m\n";
    cout << "\033[38;2;220;69;40m2 - \033[0m\033[38;2;220;89;39mSatellite\033[0m\n";
    cout << "\033[38;2;220;69;40m3 - \033[0m\033[38;2;220;89;39mBack\033[0m\n";
    cout << "\033[38;2;220;69;40mYour choice: \033[0m\033[38;2;201;218;190";
    cin >> choice;

    if (choice == 1) {
        if (db.getPlanets().empty()) {
            cout << "\033[0m\033[38;2;220;40;40mNo planets to destroy.\033[0m\n";
        }
        else {
            cout << "\n\033[0m\033[38;2;220;89;39mAvailable planets:\033[0m\n";
            const auto& planets = db.getPlanets();
            for (size_t i = 0; i < planets.size(); i++) {
                cout << i + 1 << ". " << planets[i]->getName() << "\n";
            }

            int planetChoice;
            cout << "\n\033[0m\033[38;2;220;69;40mEnter planet number to destroy (0 to cancel): \033[0m\033[38;2;201;218;190";
            cin >> planetChoice;

            if (planetChoice > 0 && planetChoice <= planets.size()) {
                db.deletePlanet(planetChoice - 1);
            }
        }
    }
    else if (choice == 2) {
        if (db.getSatellites().empty()) {
            cout << "\033[0m\033[38;2;220;40;40mNo satellites to destroy.\033[0m\n";
        }
        else {
            cout << "\n\033[0m\033[38;2;220;89;39mAvailable satellites:\033[0m\n";
            const auto& satellites = db.getSatellites();
            for (size_t i = 0; i < satellites.size(); i++) {
                const Satellite* sat = dynamic_cast<const Satellite*>(satellites[i].get());
                cout << i + 1 << ". " << satellites[i]->getName()
                    << "\033[38;2;220;40;40m (planet: " << (sat ? sat->getPlanetName() : "unknown") << ")\033[0m\n";
            }

            int satChoice;
            cout << "\n\033[0m\033[38;2;220;69;40mEnter satellite number to destroy (0 to cancel): \033[0m\033[38;2;201;218;190";
            cin >> satChoice;

            if (satChoice > 0 && satChoice <= satellites.size()) {
                db.deleteSatellite(satChoice - 1);
            }
        }
    }

    pressEnterToContinue();
}