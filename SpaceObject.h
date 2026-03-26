#pragma once
#include <string>
#include <fstream>

using namespace std;
// Абстрактный базовый класс для всех космических объектов
class SpaceObject {
protected:
    string name;          // Название объекта
    int age;                   // Возраст в миллионах лет
    int temperature;           // Средняя температура в °C
    string color;         // Основной цвет
    string description;   // Описание

public:
    // Конструктор с параметрами по умолчанию
    SpaceObject(const string& name = "", int age = 0, int temperature = 0,
        const string& color = "", const string& description = "");

    // Виртуальный деструктор (необходим для полиморфизма)
    virtual ~SpaceObject();

    // Геттеры (методы доступа к protected полям)
    string getName() const;
    int getAge() const;
    int getTemperature() const;
    string getColor() const;
    string getDescription() const;

    // Сеттеры (методы изменения protected полей)
    void setName(const string& newName);
    void setAge(int newAge);
    void setTemperature(int newTemp);
    void setColor(const string& newColor);
    void setDescription(const string& newDesc);

    // Чисто виртуальные методы (делают класс абстрактным)
    virtual void display(int index) const = 0;           // Отображение информации
    virtual void saveToFile(ofstream& file) const = 0;  // Сохранение в файл
    virtual void loadFromFile(ifstream& file) = 0;      // Загрузка из файла
    virtual string getType() const = 0;                 // Получение типа объекта

    // Виртуальный метод для сравнения (может быть переопределен)
    virtual bool compareByName(const SpaceObject& other) const;
};

