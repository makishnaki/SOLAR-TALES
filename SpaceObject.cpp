#include "SpaceObject.h"

using namespace std;

// Реализация конструктора
SpaceObject::SpaceObject(const string& name, int age, int temperature,
    const string& color, const string& description)
    : name(name), age(age), temperature(temperature),
    color(color), description(description) {
}

// Реализация деструктора
SpaceObject::~SpaceObject() {}

// Геттеры
string SpaceObject::getName() const { return name; }
int SpaceObject::getAge() const { return age; }
int SpaceObject::getTemperature() const { return temperature; }
string SpaceObject::getColor() const { return color; }
string SpaceObject::getDescription() const { return description; }

// Сеттеры
void SpaceObject::setName(const string& newName) { name = newName; }
void SpaceObject::setAge(int newAge) { age = newAge; }
void SpaceObject::setTemperature(int newTemp) { temperature = newTemp; }
void SpaceObject::setColor(const string& newColor) { color = newColor; }
void SpaceObject::setDescription(const string& newDesc) { description = newDesc; }

// Сравнение по имени (может быть переопределено в дочерних классах)
bool SpaceObject::compareByName(const SpaceObject& other) const {
    return name < other.name;
}