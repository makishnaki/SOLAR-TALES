#include "Satellite.h"
#include "Utilities.h"
#include <iostream>

using namespace std;

// Конструктор по умолчанию
Satellite::Satellite() : SpaceObject(), planetName("") {}

// Конструктор с параметрами
Satellite::Satellite(const string& name, int age, int temperature,
    const string& color, const string& description,
    const string& planetName)
    : SpaceObject(name, age, temperature, color, description),
    planetName(planetName) {
}

// Геттер для planetName
string Satellite::getPlanetName() const {
    return planetName;
}

// Сеттер для planetName
void Satellite::setPlanetName(const string& newPlanetName) {
    planetName = newPlanetName;
}

// Отображение информации о спутнике
void Satellite::display(int index) const {
    cout << index << ". " << name << "\n";
    cout << "\033[38;2;220;89;39m   Planet: \033[0m\033[38;2;220;107;40m" << planetName << "\033[0m\n";
    cout << "\033[38;2;220;89;39m   Age: \033[0m\033[38;2;220;107;40m" << age << "\033[0m\033[38;2;220;89;39m mill. of years\033[0m\n";
    cout << "\033[38;2;220;89;39m   Temperature: \033[0m\033[38;2;220;107;40m" << temperature << "\033[0m\033[38;2;220;89;39m °C\033[0m\n";
    cout << "\033[38;2;220;89;39m   Colour: \033[0m\033[38;2;220;107;40m" << color << "\033[0m\n";
    cout << "\033[38;2;220;89;39m   Describtion: \033[0m\033[38;2;220;107;40m" << description << "\033[0m\n";
    cout << "\033[38;2;220;69;40m----------------------------------------\033[0m\n";
}

// Сохранение спутника в бинарный файл
void Satellite::saveToFile(ofstream& file) const {
    saveString(file, name);
    file.write((char*)&age, sizeof(age));
    file.write((char*)&temperature, sizeof(temperature));
    saveString(file, color);
    saveString(file, description);
    saveString(file, planetName);
}

// Загрузка спутника из бинарного файла
void Satellite::loadFromFile(ifstream& file) {
    name = loadString(file);
    file.read((char*)&age, sizeof(age));
    file.read((char*)&temperature, sizeof(temperature));
    color = loadString(file);
    description = loadString(file);
    planetName = loadString(file);
}

// Получение типа объекта
string Satellite::getType() const {
    return "\033[38;2;220;89;39mSatellite\033[0m";
}