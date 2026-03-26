#pragma once
#include <vector>
#include <memory>
#include <string>
#include "SpaceObject.h"
#include "Planet.h"
#include "Satellite.h"

using namespace std;
// Класс для управления базой данных космических объектов
class SpaceDatabase {
private:
    vector<unique_ptr<SpaceObject>> planets;     // Хранилище планет
    vector<unique_ptr<SpaceObject>> satellites;  // Хранилище спутников
    const string PLANETS_FILE;      // Имя файла для планет
    const string SATELLITES_FILE;   // Имя файла для спутников

public:
    // Конструктор (инициализирует имена файлов)
    SpaceDatabase();

    // Добавление объектов
    void addPlanet(unique_ptr<Planet> planet);
    void addSatellite(unique_ptr<Satellite> satellite);

    // Проверка существования объектов
    bool planetExists(const string& name) const;
    bool satelliteExists(const string& name) const;

    // Геттеры для доступа к данным (только для чтения)
    const vector<unique_ptr<SpaceObject>>& getPlanets() const;
    const vector<unique_ptr<SpaceObject>>& getSatellites() const;

    // Работа с файлами (сохранение/загрузка)
    void savePlanets() const;
    void loadPlanets();
    void saveSatellites() const;
    void loadSatellites();
    void saveAllData();
    void loadAllData();

    // Отображение данных
    void displayPlanets() const;
    void displaySatellites() const;
    void displayAllData() const;

    // Удаление объектов
    void deletePlanet(int index);
    void deleteSatellite(int index);

    // Сортировка
    void sortPlanetsByName();
    void sortPlanetsByAge();
    void sortPlanetsByTemperature();
    void sortSatellitesByName();
    void sortSatellitesByPlanet();

    // Статистика и поиск
    void showStatistics() const;
    void searchByName(const string& searchName) const;

    // Вспомогательные методы
    bool isEmpty() const;
    void showPlanetsList() const;
};

