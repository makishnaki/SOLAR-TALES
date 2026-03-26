#pragma once

#include "SpaceObject.h"

using namespace std;
// Класс Planet, наследуется от SpaceObject
class Planet : public SpaceObject {
public:
    // Конструкторы
    Planet();
    Planet(const string& name, int age, int temperature,
        const string& color, const string& description);

    // Переопределение виртуальных методов базового класса
    void display(int index) const override;
    void saveToFile(ofstream& file) const override;
    void loadFromFile(ifstream& file) override;
    string getType() const override;
};

