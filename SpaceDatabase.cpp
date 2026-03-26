#include "SpaceDatabase.h"
#include "Utilities.h"
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

// Конструктор
SpaceDatabase::SpaceDatabase()
    : PLANETS_FILE("planets.dat"), SATELLITES_FILE("satellites.dat") {
}

// Добавление планеты
void SpaceDatabase::addPlanet(unique_ptr<Planet> planet) {
    planets.push_back(move(planet));
    savePlanets();
}

// Добавление спутника
void SpaceDatabase::addSatellite(unique_ptr<Satellite> satellite) {
    satellites.push_back(move(satellite));
    saveSatellites();
}

// Проверка существования планеты по имени
bool SpaceDatabase::planetExists(const string& name) const {
    for (const auto& planet : planets) {
        if (planet->getName() == name) return true;
    }
    return false;
}

// Проверка существования спутника по имени
bool SpaceDatabase::satelliteExists(const string& name) const {
    for (const auto& sat : satellites) {
        if (sat->getName() == name) return true;
    }
    return false;
}

// Геттеры
const vector<unique_ptr<SpaceObject>>& SpaceDatabase::getPlanets() const {
    return planets;
}

const vector<unique_ptr<SpaceObject>>& SpaceDatabase::getSatellites() const {
    return satellites;
}

// Сохранение планет
void SpaceDatabase::savePlanets() const {
    ofstream file(PLANETS_FILE, ios::binary);
    if (!file) {
        cout << "\033[38;2;220;40;40mError: failed to open planets save file!\033[0m\n";
        return;
    }

    size_t count = planets.size();
    file.write((char*)&count, sizeof(count));

    for (const auto& planet : planets) {
        planet->saveToFile(file);
    }

    file.close();
    cout << "\033[38;2;220;89;39mPlanets data saved in file:\033[0m \033[38;2;220;107;40m"
        << PLANETS_FILE << "\033[0m\n";
}

// Загрузка планет
void SpaceDatabase::loadPlanets() {
    ifstream file(PLANETS_FILE, ios::binary);
    if (!file) {
        cout << "\033[38;2;220;89;39mPlanet file not found.\033[0m \033[38;2;220;89;39mWe will create a new one for you.\033[0m\n";
        return;
    }

    planets.clear();
    size_t count;
    file.read((char*)&count, sizeof(count));

    for (size_t i = 0; i < count; i++) {
        auto planet = make_unique<Planet>();
        planet->loadFromFile(file);
        planets.push_back(move(planet));
    }

    file.close();
    cout << "\033[38;2;220;89;39mPlanets loaded:\033[0m \033[38;2;220;107;40m"
        << planets.size() << " \033[0m\n";
}

// Сохранение спутников
void SpaceDatabase::saveSatellites() const {
    ofstream file(SATELLITES_FILE, ios::binary);
    if (!file) {
        cout << "\033[38;2;220;40;40mError: failed to open satellites save file!\033[0m\n";
        return;
    }

    size_t count = satellites.size();
    file.write((char*)&count, sizeof(count));

    for (const auto& satellite : satellites) {
        satellite->saveToFile(file);
    }

    file.close();
    cout << "\033[38;2;220;89;39mSatellites data saved in file:\033[0m \033[38;2;220;107;40m"
        << SATELLITES_FILE << "\033[0m\n";
}

// Загрузка спутников
void SpaceDatabase::loadSatellites() {
    ifstream file(SATELLITES_FILE, ios::binary);
    if (!file) {
        cout << "\033[38;2;220;89;39mSatellite file not found.\033[0m \033[38;2;220;89;39m We will create a new one for you.\033[0m\n";
        return;
    }

    satellites.clear();
    size_t count;
    file.read((char*)&count, sizeof(count));

    for (size_t i = 0; i < count; i++) {
        auto satellite = make_unique<Satellite>();
        satellite->loadFromFile(file);
        satellites.push_back(move(satellite));
    }

    file.close();
    cout << "\033[38;2;220;89;39mSatellites loaded:\033[0m \033[38;2;220;107;40m"
        << satellites.size() << " \033[0m\n";
}

// Сохранение всех данных
void SpaceDatabase::saveAllData() {
    savePlanets();
    saveSatellites();
}

// Загрузка всех данных
void SpaceDatabase::loadAllData() {
    loadPlanets();
    loadSatellites();
}

// Отображение планет
void SpaceDatabase::displayPlanets() const {
    cout << "\033[38;2;220;89;39mPLANETS:\033[0m\n";
    cout << "\033[38;2;220;69;40m========================================\033[0m\n";
    if (planets.empty()) {
        cout << "\033[38;2;220;40;40mNo data found.\033[0m\n";
    }
    else {
        for (size_t i = 0; i < planets.size(); i++) {
            planets[i]->display(i + 1);
        }
    }
}

// Отображение спутников
void SpaceDatabase::displaySatellites() const {
    cout << "\n\033[0m\033[38;2;220;89;39mSATELLITES:\033[0m\n";
    cout << "\033[38;2;220;69;40m========================================\033[0m\n";
    if (satellites.empty()) {
        cout << "\033[38;2;220;40;40mNo data found.\033[0m\n";
    }
    else {
        for (size_t i = 0; i < satellites.size(); i++) {
            satellites[i]->display(i + 1);
        }
    }
}

// Отображение всех данных
void SpaceDatabase::displayAllData() const {
    displayPlanets();
    displaySatellites();
}

// Удаление планеты (и всех её спутников)
void SpaceDatabase::deletePlanet(int index) {
    if (index >= 0 && index < planets.size()) {
        string planetName = planets[index]->getName();

        // Удаляем все спутники этой планеты
        for (auto it = satellites.begin(); it != satellites.end();) {
            Satellite* sat = dynamic_cast<Satellite*>(it->get());
            if (sat && sat->getPlanetName() == planetName) {
                it = satellites.erase(it);
            }
            else {
                ++it;
            }
        }

        planets.erase(planets.begin() + index);
        saveAllData();
        cout << "\033[0m\033[38;2;220;89;39mPlanet \033[0m\033[38;2;220;107;40m\"" << planetName
            << "\"\033[0m\033[38;2;220;89;39m and her satellites were destroyed.\033[0m\n";
    }
}

// Удаление спутника
void SpaceDatabase::deleteSatellite(int index) {
    if (index >= 0 && index < satellites.size()) {
        string satelliteName = satellites[index]->getName();
        satellites.erase(satellites.begin() + index);
        saveSatellites();
        cout << "\033[0m\033[38;2;220;89;39mSatellite \033[0m\033[38;2;220;107;40m\"" << satelliteName
            << "\"\033[0m\033[38;2;220;89;39m destroyed.\033[0m\n";
    }
}

// Сортировка планет по имени
void SpaceDatabase::sortPlanetsByName() {
    sort(planets.begin(), planets.end(),
        [](const unique_ptr<SpaceObject>& a, const unique_ptr<SpaceObject>& b) {
            return a->compareByName(*b);
        });
}

// Сортировка планет по возрасту
void SpaceDatabase::sortPlanetsByAge() {
    sort(planets.begin(), planets.end(),
        [](const unique_ptr<SpaceObject>& a, const unique_ptr<SpaceObject>& b) {
            return a->getAge() < b->getAge();
        });
}

// Сортировка планет по температуре
void SpaceDatabase::sortPlanetsByTemperature() {
    sort(planets.begin(), planets.end(),
        [](const unique_ptr<SpaceObject>& a, const unique_ptr<SpaceObject>& b) {
            return a->getTemperature() < b->getTemperature();
        });
}

// Сортировка спутников по имени
void SpaceDatabase::sortSatellitesByName() {
    sort(satellites.begin(), satellites.end(),
        [](const unique_ptr<SpaceObject>& a, const unique_ptr<SpaceObject>& b) {
            return a->compareByName(*b);
        });
}

// Сортировка спутников по планете
void SpaceDatabase::sortSatellitesByPlanet() {
    sort(satellites.begin(), satellites.end(),
        [](const unique_ptr<SpaceObject>& a, const unique_ptr<SpaceObject>& b) {
            const Satellite* satA = dynamic_cast<const Satellite*>(a.get());
            const Satellite* satB = dynamic_cast<const Satellite*>(b.get());
            return satA && satB ? satA->getPlanetName() < satB->getPlanetName() : false;
        });
}

// Статистика
void SpaceDatabase::showStatistics() const {
    cout << "\033[38;2;220;89;39mGeneral statistics:\033[0m\n";
    cout << "\033[38;2;220;69;40m-----------------\033[0m\n";
    cout << "\033[38;2;220;89;39mAmount of planets: \033[38;2;220;107;40m" << planets.size() << "\033[0m\n";
    cout << "\033[38;2;220;89;39mAmount of satellites: \033[38;2;220;107;40m" << satellites.size() << "\033[0m\n";
    cout << "\033[38;2;220;89;39mAmount of objects: \033[38;2;220;107;40m" << planets.size() + satellites.size() << "\033[0m\n";

    if (!planets.empty()) {
        int totalAge = 0, totalTemp = 0;
        int oldestAge = planets[0]->getAge();
        string oldestPlanet = planets[0]->getName();
        int hottestTemp = planets[0]->getTemperature();
        string hottestPlanet = planets[0]->getName();

        for (const auto& planet : planets) {
            totalAge += planet->getAge();
            totalTemp += planet->getTemperature();

            if (planet->getAge() > oldestAge) {
                oldestAge = planet->getAge();
                oldestPlanet = planet->getName();
            }

            if (planet->getTemperature() > hottestTemp) {
                hottestTemp = planet->getTemperature();
                hottestPlanet = planet->getName();
            }
        }

        cout << "\n\033[38;2;220;89;39mStatistics on planets:\033[0m\n";
        cout << "\033[38;2;220;69;40m----------------------\033[0m\n";
        cout << "\033[38;2;220;89;39mAverage age: \033[38;2;220;107;40m" << totalAge / planets.size() << "\033[0m\033[38;2;220;89;39m mill. of years\033[0m\n";
        cout << "\033[38;2;220;89;39mAverage temperature: \033[38;2;220;107;40m" << totalTemp / planets.size() << "\033[0m\033[38;2;220;89;39m °C\033[0m\n";
        cout << "\033[38;2;220;89;39mOldest planet: \033[38;2;220;107;40m" << oldestPlanet << "\033[0m\033[38;2;220;89;39m (\033[0m\033[38;2;220;107;40m" << oldestAge << "\033[0m\033[38;2;220;89;39m mill. of years)\033[0m\n";
        cout << "\033[38;2;220;89;39mHottest planet: \033[38;2;220;107;40m" << hottestPlanet << "\033[0m\033[38;2;220;89;39m (\033[0m\033[38;2;220;107;40m" << hottestTemp << "\033[0m\033[38;2;220;89;39m °C)\033[0m\n";
    }
}

// Поиск по имени
void SpaceDatabase::searchByName(const string& searchName) const {
    bool found = false;

    for (const auto& planet : planets) {
        if (planet->getName().find(searchName) != string::npos) {
            if (!found) {
                cout << "\n\033[0m\033[38;2;220;89;39mResults:\033[0m\n";
                cout << "\033[38;2;220;69;40m========================================\033[0m\n";
                found = true;
            }
            planet->display(1);
        }
    }

    for (const auto& satellite : satellites) {
        if (satellite->getName().find(searchName) != string::npos) {
            if (!found) {
                cout << "\n\033[0m\033[38;2;220;89;39mResults:\033[0m\n";
                cout << "\033[38;2;220;69;40m========================================\033[0m\n";
                found = true;
            }
            satellite->display(1);
        }
    }

    if (!found) {
        cout << "\n\033[38;2;220;89;39mObjects named \033[0m\033[38;2;220;107;40m\"" << searchName
            << "\" \033[0m\033[38;2;220;89;39mmnever existed yet.\033[0m\n";
    }
}

// Проверка на пустоту
bool SpaceDatabase::isEmpty() const {
    return planets.empty() && satellites.empty();
}

// Отображение списка планет
void SpaceDatabase::showPlanetsList() const {
    if (planets.empty()) {
        cout << "\033[38;2;220;40;40m  (list of planets is empty)\033[0m\n";
    }
    else {
        cout << "\033[38;2;220;89;39m  Existing planets:\033[0m\n";
        for (const auto& planet : planets) {
            cout << "  - " << planet->getName() << "\n";
        }
    }
}