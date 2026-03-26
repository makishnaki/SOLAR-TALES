#pragma once

#include "SpaceObject.h"

using namespace std;
// Класс Satellite, наследуется от SpaceObject
class Satellite : public SpaceObject {
private:
    string planetName;    // Имя планеты, вокруг которой вращается спутник

public:
    // Конструкторы
    Satellite();
    Satellite(const string& name, int age, int temperature,
        const string& color, const string& description,
        const string& planetName);

    // Геттер и сеттер для planetName
    string getPlanetName() const;
    void setPlanetName(const string& newPlanetName);

    // Переопределение виртуальных методов базового класса
    void display(int index) const override;
    void saveToFile(ofstream& file) const override;
    void loadFromFile(ifstream& file) override;
    string getType() const override;
};

