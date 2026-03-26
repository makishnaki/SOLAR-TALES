#include "Planet.h"
#include "Utilities.h"
#include <iostream>

using namespace std;

// Конструктор по умолчанию
Planet::Planet() : SpaceObject() {}

// Конструктор с параметрами
Planet::Planet(const string& name, int age, int temperature,
    const string& color, const string& description)
    : SpaceObject(name, age, temperature, color, description) {
}

// Отображение информации о планете
void Planet::display(int index) const {
    cout << index << ". " << name << "\n";
    cout << "\033[38;2;220;89;39m   Age: \033[0m\033[38;2;220;107;40m" << age << "\033[0m\033[38;2;220;89;39m mill. of years\033[0m\n";
    cout << "\033[38;2;220;89;39m   Temperature: \033[0m\033[38;2;220;107;40m" << temperature << "\033[0m\033[38;2;220;89;39m °C\033[0m\n";
    cout << "\033[38;2;220;89;39m   Colour: \033[0m\033[38;2;220;107;40m" << color << "\033[0m\n";
    cout << "\033[38;2;220;89;39m   Describtion: \033[0m\033[38;2;220;107;40m" << description << "\033[0m\n";
    cout << "\033[38;2;220;69;40m----------------------------------------\033[0m\n";
}

// Сохранение планеты в бинарный файл
void Planet::saveToFile(ofstream& file) const {
    saveString(file, name);
    file.write((char*)&age, sizeof(age));
    file.write((char*)&temperature, sizeof(temperature));
    saveString(file, color);
    saveString(file, description);
}

// Загрузка планеты из бинарного файла
void Planet::loadFromFile(ifstream& file) {
    name = loadString(file);
    file.read((char*)&age, sizeof(age));
    file.read((char*)&temperature, sizeof(temperature));
    color = loadString(file);
    description = loadString(file);
}

// Получение типа объекта
string Planet::getType() const {
    return "\033[38;2;220;89;39mPlanet\033[0m";
}