#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <algorithm>
#include <fstream>  // Для работы с файлами

using namespace std;

// Структуры для хранения данных
struct Planet {
    string name;
    int age;
    int temperature;
    string color;
    string description;
};

struct Satellite {
    string name;
    int age;
    int temperature;
    string color;
    string description;
    string planetName;
};

// Векторы для хранения данных
vector<Planet> planets;
vector<Satellite> satellites;

// Имена файлов для сохранения
const string PLANETS_FILE = "planets.dat";
const string SATELLITES_FILE = "satellites.dat";

// Функция для сохранения строки в бинарный файл
void saveString(ofstream& file, const string& str) {
    // Сохраняем длину строки
    size_t length = str.size();
    file.write((char*)&length, sizeof(length));

    // Сохраняем саму строку
    file.write(str.c_str(), length);
}

// Функция для чтения строки из бинарного файла
string loadString(ifstream& file) {
    // Читаем длину строки
    size_t length;
    file.read((char*)&length, sizeof(length));

    // Создаем буфер для строки
    char* buffer = new char[length + 1];
    file.read(buffer, length);
    buffer[length] = '\0';  // Добавляем нулевой символ

    // Создаем строку из буфера
    string result(buffer);
    delete[] buffer;

    return result;
}

// Сохранение планет в бинарный файл
void savePlanets() {
    ofstream file(PLANETS_FILE, ios::binary);

    if (!file) {
        cout << "Ошибка: не удалось открыть файл для сохранения планет!\n";
        return;
    }

    // Сохраняем количество планет
    size_t count = planets.size();
    file.write((char*)&count, sizeof(count));

    // Сохраняем каждую планету
    for (const auto& planet : planets) {
        saveString(file, planet.name);
        file.write((char*)&planet.age, sizeof(planet.age));
        file.write((char*)&planet.temperature, sizeof(planet.temperature));
        saveString(file, planet.color);
        saveString(file, planet.description);
    }

    file.close();
    cout << "Данные планет сохранены в файл: " << PLANETS_FILE << "\n";
}

// Загрузка планет из бинарного файла
void loadPlanets() {
    ifstream file(PLANETS_FILE, ios::binary);

    if (!file) {
        cout << "Файл с планетами не найден. Будет создан новый.\n";
        return;
    }

    // Очищаем текущие данные
    planets.clear();

    // Читаем количество планет
    size_t count;
    file.read((char*)&count, sizeof(count));

    // Читаем каждую планету
    for (size_t i = 0; i < count; i++) {
        Planet planet;
        planet.name = loadString(file);
        file.read((char*)&planet.age, sizeof(planet.age));
        file.read((char*)&planet.temperature, sizeof(planet.temperature));
        planet.color = loadString(file);
        planet.description = loadString(file);

        planets.push_back(planet);
    }

    file.close();
    cout << "Загружено " << planets.size() << " планет\n";
}

// Сохранение спутников в бинарный файл
void saveSatellites() {
    ofstream file(SATELLITES_FILE, ios::binary);

    if (!file) {
        cout << "Ошибка: не удалось открыть файл для сохранения спутников!\n";
        return;
    }

    // Сохраняем количество спутников
    size_t count = satellites.size();
    file.write((char*)&count, sizeof(count));

    // Сохраняем каждый спутник
    for (const auto& satellite : satellites) {
        saveString(file, satellite.name);
        file.write((char*)&satellite.age, sizeof(satellite.age));
        file.write((char*)&satellite.temperature, sizeof(satellite.temperature));
        saveString(file, satellite.color);
        saveString(file, satellite.description);
        saveString(file, satellite.planetName);
    }

    file.close();
    cout << "Данные спутников сохранены в файл: " << SATELLITES_FILE << "\n";
}

// Загрузка спутников из бинарного файла
void loadSatellites() {
    ifstream file(SATELLITES_FILE, ios::binary);

    if (!file) {
        cout << "Файл со спутниками не найден. Будет создан новый.\n";
        return;
    }

    // Очищаем текущие данные
    satellites.clear();

    // Читаем количество спутников
    size_t count;
    file.read((char*)&count, sizeof(count));

    // Читаем каждый спутник
    for (size_t i = 0; i < count; i++) {
        Satellite satellite;
        satellite.name = loadString(file);
        file.read((char*)&satellite.age, sizeof(satellite.age));
        file.read((char*)&satellite.temperature, sizeof(satellite.temperature));
        satellite.color = loadString(file);
        satellite.description = loadString(file);
        satellite.planetName = loadString(file);

        satellites.push_back(satellite);
    }

    file.close();
    cout << "Загружено " << satellites.size() << " спутников\n";
}

// Сохранение всех данных
void saveAllData() {
    savePlanets();
    saveSatellites();
}

// Загрузка всех данных
void loadAllData() {
    loadPlanets();
    loadSatellites();
}

// Функции для очистки экрана
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Функция для ожидания нажатия Enter
void pressEnterToContinue() {
    cout << "\nНажмите Enter для продолжения...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// Проверка существования планеты по имени
bool planetExists(const string& planetName) {
    for (const auto& planet : planets) {
        if (planet.name == planetName) {
            return true;
        }
    }
    return false;
}

// Функция для отображения списка планет
void showPlanetsList() {
    if (planets.empty()) {
        cout << "  (список планет пуст)\n";
    }
    else {
        cout << "  Существующие планеты:\n";
        for (const auto& planet : planets) {
            cout << "  - " << planet.name << "\n";
        }
    }
}

// Функция отображения главного меню
void showMainMenu() {
    clearScreen();
    cout << "\" SOLAR TALES \"\n\n";
    cout << "Main Menu:\n";
    cout << "- 1 - Add data\n";
    cout << "- 2 - View data\n";
    cout << "- 3 - Delete data\n";
    cout << "- 4 - Search/Filter\n";
    cout << "- 5 - Summary\n";
    cout << "- 6 - Sort\n";
    cout << "- 7 - Save and Exit\n"; 
    cout << "\nEnter Your choice : ";
}

// Функция для добавления планеты
void addPlanet() {
    Planet planet;

    cout << "\n=== Добавление планеты ===\n";

    cout << "Введите название планеты: ";
    cin.ignore();
    getline(cin, planet.name);

    // Проверка на уникальность имени
    if (planetExists(planet.name)) {
        cout << "Ошибка: планета с таким именем уже существует!\n";
        return;
    }

    cout << "Введите возраст планеты (в миллионах лет): ";
    cin >> planet.age;

    cout << "Введите среднюю температуру (в °C): ";
    cin >> planet.temperature;

    cout << "Введите основной цвет планеты: ";
    cin.ignore();
    getline(cin, planet.color);

    cout << "Введите общее описание планеты: ";
    getline(cin, planet.description);

    planets.push_back(planet);

    // Автосохранение после добавления
    savePlanets();

    cout << "\nПланета \"" << planet.name << "\" успешно добавлена и сохранена!\n";
}

// Функция для добавления спутника 
void addSatellite() {
    if (planets.empty()) {
        cout << "\nОшибка: сначала добавьте хотя бы одну планету!\n";
        showPlanetsList();
        return;
    }

    Satellite satellite;

    cout << "\n=== Добавление спутника ===\n";

    cout << "Введите название спутника: ";
    cin.ignore();
    getline(cin, satellite.name);

    // Проверка на уникальность имени спутника
    for (const auto& sat : satellites) {
        if (sat.name == satellite.name) {
            cout << "Ошибка: спутник с таким именем уже существует!\n";
            return;
        }
    }

    cout << "Введите возраст спутника (в миллионах лет): ";
    cin >> satellite.age;

    cout << "Введите среднюю температуру (в °C): ";
    cin >> satellite.temperature;

    cout << "Введите основной цвет спутника: ";
    cin.ignore();
    getline(cin, satellite.color);

    cout << "Введите общее описание спутника: ";
    getline(cin, satellite.description);

    // Ввод и проверка планеты-хозяина
    bool validPlanet = false;
    do {
        cout << "\nК какой планете принадлежит спутник?\n";
        showPlanetsList();
        cout << "\nВведите название планеты: ";
        getline(cin, satellite.planetName);

        if (planetExists(satellite.planetName)) {
            validPlanet = true;
        }
        else {
            cout << "\nОшибка: планеты с именем \"" << satellite.planetName << "\" не существует!\n";
            cout << "Пожалуйста, введите название из списка выше.\n";
        }
    } while (!validPlanet);

    satellites.push_back(satellite);

    // Автосохранение после добавления
    saveSatellites();

    cout << "\nСпутник \"" << satellite.name << "\" успешно добавлен к планете \""
        << satellite.planetName << "\" и сохранен!\n";
}

// Функция отображения меню добавления данных
void showAddDataMenu() {
    int choice;

    do {
        clearScreen();
        cout << "\" SOLAR TALES \"\n\n";
        cout << "Add Data Menu:\n";
        cout << "- 1 - PLANET\n";
        cout << "- 2 - SATELLITE\n";
        cout << "- 3 - Back\n";
        cout << "\nEnter Your choice : ";
        cin >> choice;

        switch (choice) {
        case 1:
            addPlanet();
            pressEnterToContinue();
            break;
        case 2:
            addSatellite();
            pressEnterToContinue();
            break;
        case 3:
            // Возврат в главное меню
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            pressEnterToContinue();
        }
    } while (choice != 3);
}

// Функция для форматированного вывода планет
void displayPlanet(const Planet& planet, int index) {
    cout << index << ". " << planet.name << "\n";
    cout << "   Возраст: " << planet.age << " млн лет\n";
    cout << "   Температура: " << planet.temperature << " °C\n";
    cout << "   Цвет: " << planet.color << "\n";
    cout << "   Описание: " << planet.description << "\n";
    cout << "----------------------------------------\n";
}

// Функция для форматированного вывода спутников
void displaySatellite(const Satellite& satellite, int index) {
    cout << index << ". " << satellite.name << "\n";
    cout << "   Планета: " << satellite.planetName << "\n";
    cout << "   Возраст: " << satellite.age << " млн лет\n";
    cout << "   Температура: " << satellite.temperature << " °C\n";
    cout << "   Цвет: " << satellite.color << "\n";
    cout << "   Описание: " << satellite.description << "\n";
    cout << "----------------------------------------\n";
}

// Функция для просмотра данных
void viewData() {
    clearScreen();
    cout << "\" SOLAR TALES \"\n\n";
    cout << "=== Просмотр данных ===\n\n";

    cout << "ПЛАНЕТЫ:\n";
    cout << "========================================\n";
    if (planets.empty()) {
        cout << "Нет данных о планетах.\n";
    }
    else {
        for (size_t i = 0; i < planets.size(); i++) {
            displayPlanet(planets[i], i + 1);
        }
    }

    cout << "\nСПУТНИКИ:\n";
    cout << "========================================\n";
    if (satellites.empty()) {
        cout << "Нет данных о спутниках.\n";
    }
    else {
        for (size_t i = 0; i < satellites.size(); i++) {
            displaySatellite(satellites[i], i + 1);
        }
    }

    pressEnterToContinue();
}

// Функция для удаления данных
void deleteData() {
    clearScreen();
    cout << "\" SOLAR TALES \"\n\n";
    cout << "=== Удаление данных ===\n\n";

    if (planets.empty() && satellites.empty()) {
        cout << "Нет данных для удаления.\n";
        pressEnterToContinue();
        return;
    }

    int choice;
    cout << "Что вы хотите удалить?\n";
    cout << "1 - Планету\n";
    cout << "2 - Спутник\n";
    cout << "3 - Назад\n";
    cout << "Выбор: ";
    cin >> choice;

    if (choice == 1) {
        if (planets.empty()) {
            cout << "Нет планет для удаления.\n";
        }
        else {
            cout << "\nДоступные планеты:\n";
            for (size_t i = 0; i < planets.size(); i++) {
                cout << i + 1 << ". " << planets[i].name << "\n";
            }

            int planetChoice;
            cout << "\nВведите номер планеты для удаления (0 для отмены): ";
            cin >> planetChoice;

            if (planetChoice > 0 && planetChoice <= planets.size()) {
                string planetName = planets[planetChoice - 1].name;

                // Удаляем спутники этой планеты
                for (auto it = satellites.begin(); it != satellites.end(); ) {
                    if (it->planetName == planetName) {
                        it = satellites.erase(it);
                    }
                    else {
                        ++it;
                    }
                }

                // Удаляем планету
                planets.erase(planets.begin() + planetChoice - 1);

                // Сохраняем изменения
                saveAllData();

                cout << "Планета \"" << planetName << "\" и её спутники удалены и изменения сохранены.\n";
            }
        }
    }
    else if (choice == 2) {
        if (satellites.empty()) {
            cout << "Нет спутников для удаления.\n";
        }
        else {
            cout << "\nДоступные спутники:\n";
            for (size_t i = 0; i < satellites.size(); i++) {
                cout << i + 1 << ". " << satellites[i].name
                    << " (планета: " << satellites[i].planetName << ")\n";
            }

            int satelliteChoice;
            cout << "\nВведите номер спутника для удаления (0 для отмены): ";
            cin >> satelliteChoice;

            if (satelliteChoice > 0 && satelliteChoice <= satellites.size()) {
                string satelliteName = satellites[satelliteChoice - 1].name;
                satellites.erase(satellites.begin() + satelliteChoice - 1);

                // Сохраняем изменения
                saveSatellites();

                cout << "Спутник \"" << satelliteName << "\" удален и изменения сохранены.\n";
            }
        }
    }

    pressEnterToContinue();
}

// Меню ручного сохранения
void saveMenu() {
    clearScreen();
    cout << "\" SOLAR TALES \"\n\n";
    cout << "=== Сохранение данных ===\n\n";

    cout << "1 - Сохранить все данные\n";
    cout << "2 - Сохранить только планеты\n";
    cout << "3 - Сохранить только спутники\n";
    cout << "4 - Назад\n";
    cout << "Выбор: ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        saveAllData();
        cout << "Все данные сохранены!\n";
        break;
    case 2:
        savePlanets();
        break;
    case 3:
        saveSatellites();
        break;
    case 4:
        return;
    default:
        cout << "Неверный выбор.\n";
    }

    pressEnterToContinue();
}

// Остальные функции
void searchFilter() {
    clearScreen();
    cout << "\" SOLAR TALES \"\n\n";
    cout << "=== Поиск/Фильтрация ===\n\n";

    cout << "1 - Поиск по имени\n";
    cout << "2 - Фильтр по планете (для спутников)\n";
    cout << "3 - Сохранить данные (ручное сохранение)\n"; 
    cout << "4 - Назад\n";
    cout << "Выбор: ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1: {
        // Поиск по имени
        if (planets.empty() && satellites.empty()) {
            cout << "База данных пуста.\n";
            pressEnterToContinue();
            return;
        }

        string searchName;
        cout << "Введите имя для поиска: ";
        cin.ignore();
        getline(cin, searchName);

        bool found = false;

        // Поиск среди планет
        for (const auto& planet : planets) {
            if (planet.name.find(searchName) != string::npos) {
                if (!found) {
                    cout << "\nРезультаты поиска:\n";
                    cout << "========================================\n";
                    found = true;
                }
                displayPlanet(planet, 1);
            }
        }

        // Поиск среди спутников
        for (const auto& satellite : satellites) {
            if (satellite.name.find(searchName) != string::npos) {
                if (!found) {
                    cout << "\nРезультаты поиска:\n";
                    cout << "========================================\n";
                    found = true;
                }
                displaySatellite(satellite, 1);
            }
        }

        if (!found) {
            cout << "\nОбъекты с именем \"" << searchName << "\" не найдены.\n";
        }
        pressEnterToContinue();
        break;
    }
    case 2:
        cout << "\nЭта функция находится в разработке.\n";
        pressEnterToContinue();
        break;
    case 3:
        saveMenu();
        break;
    case 4:
        break;
    default:
        cout << "Неверный выбор.\n";
        pressEnterToContinue();
    }
}

void showSummary() {
    clearScreen();
    cout << "\" SOLAR TALES \"\n\n";
    cout << "=== Статистика ===\n\n";

    cout << "Общая статистика:\n";
    cout << "-----------------\n";
    cout << "Количество планет: " << planets.size() << "\n";
    cout << "Количество спутников: " << satellites.size() << "\n";
    cout << "Всего объектов: " << planets.size() + satellites.size() << "\n";

    cout << "\nФайлы данных:\n";
    cout << "-------------\n";
    cout << "Файл планет: " << PLANETS_FILE << "\n";
    cout << "Файл спутников: " << SATELLITES_FILE << "\n";

    if (!planets.empty()) {
        int totalAge = 0;
        int totalTemp = 0;
        int oldestAge = planets[0].age;
        string oldestPlanet = planets[0].name;
        int hottestTemp = planets[0].temperature;
        string hottestPlanet = planets[0].name;

        for (const auto& planet : planets) {
            totalAge += planet.age;
            totalTemp += planet.temperature;

            if (planet.age > oldestAge) {
                oldestAge = planet.age;
                oldestPlanet = planet.name;
            }

            if (planet.temperature > hottestTemp) {
                hottestTemp = planet.temperature;
                hottestPlanet = planet.name;
            }
        }

        cout << "\nСтатистика по планетам:\n";
        cout << "----------------------\n";
        cout << "Средний возраст: " << totalAge / planets.size() << " млн лет\n";
        cout << "Средняя температура: " << totalTemp / planets.size() << " °C\n";
        cout << "Самая старая планета: " << oldestPlanet << " (" << oldestAge << " млн лет)\n";
        cout << "Самая горячая планета: " << hottestPlanet << " (" << hottestTemp << " °C)\n";
    }

    pressEnterToContinue();
}

void sortData() {
    clearScreen();
    cout << "\" SOLAR TALES \"\n\n";
    cout << "=== Сортировка данных ===\n\n";

    cout << "1 - Сортировать планеты по имени\n";
    cout << "2 - Сортировать планеты по возрасту\n";
    cout << "3 - Сортировать планеты по температуре\n";
    cout << "4 - Сортировать спутники по имени\n";
    cout << "5 - Сортировать спутники по планете\n";
    cout << "6 - Назад\n";
    cout << "Выбор: ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        sort(planets.begin(), planets.end(),
            [](const Planet& a, const Planet& b) { return a.name < b.name; });
        cout << "Планеты отсортированы по имени.\n";
        break;
    case 2:
        sort(planets.begin(), planets.end(),
            [](const Planet& a, const Planet& b) { return a.age < b.age; });
        cout << "Планеты отсортированы по возрасту.\n";
        break;
    case 3:
        sort(planets.begin(), planets.end(),
            [](const Planet& a, const Planet& b) { return a.temperature < b.temperature; });
        cout << "Планеты отсортированы по температуре.\n";
        break;
    case 4:
        sort(satellites.begin(), satellites.end(),
            [](const Satellite& a, const Satellite& b) { return a.name < b.name; });
        cout << "Спутники отсортированы по имени.\n";
        break;
    case 5:
        sort(satellites.begin(), satellites.end(),
            [](const Satellite& a, const Satellite& b) { return a.planetName < b.planetName; });
        cout << "Спутники отсортированы по планете.\n";
        break;
    case 6:
        return;
    default:
        cout << "Неверный выбор.\n";
    }

    pressEnterToContinue();
}

int main() {
    int choice;
    setlocale(LC_ALL, "RU");
    // Загружаем данные при запуске
    cout << "Загрузка данных...\n";
    loadAllData();
    pressEnterToContinue();

    do {
        showMainMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            showAddDataMenu();
            break;
        case 2:
            viewData();
            break;
        case 3:
            deleteData();
            break;
        case 4:
            searchFilter();
            break;
        case 5:
            showSummary();
            break;
        case 6:
            sortData();
            break;
        case 7:
            // Сохраняем данные перед выходом
            saveAllData();
            clearScreen();
            cout << "Данные сохранены в файлы:\n";
            cout << "1. " << PLANETS_FILE << " (планеты)\n";
            cout << "2. " << SATELLITES_FILE << " (спутники)\n";
            cout << "\nСпасибо за использование SOLAR TALES! До свидания!\n";
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
            pressEnterToContinue();
        }
    } while (choice != 7);

    return 0;
}