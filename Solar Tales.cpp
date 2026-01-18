#include <iostream> // Input/Output
#include <string> // Для создания переменных поддерживающих слова
#include <vector> // Динамический массив, растет по мере добавления данных
#include <limits> // Для очистки входного буфера
#include <algorithm> // Для функций сортировки, поиска, изменения, копирования, удаления, минимума/максимума
#include <fstream>  // Для работы с файлами

using namespace std;

// ↓ ----------- Структуры для хранения данных ----------- ↓

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
    // Сохранение длины строки
    size_t length = str.size();
    file.write((char*)&length, sizeof(length));

    // Сохранение самой строки
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
        cout << "Error: failed to open planets save file!\n";
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
    cout << "Planets data saved in file: " << PLANETS_FILE << "\n";
}

// Загрузка планет из бинарного файла
void loadPlanets() {
    ifstream file(PLANETS_FILE, ios::binary);

    if (!file) {
        cout << "Planet file not found. We will create a new one for you.\n";
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
    cout << "Planets loaded: " << planets.size() << " \n";
}

// Сохранение спутников в бинарный файл
void saveSatellites() {
    ofstream file(SATELLITES_FILE, ios::binary);

    if (!file) {
        cout << "Error: failed to open satellites save file!\n";
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
    cout << "Satellites data saved in file: " << SATELLITES_FILE << "\n";
}

// Загрузка спутников из бинарного файла
void loadSatellites() {
    ifstream file(SATELLITES_FILE, ios::binary);

    if (!file) {
        cout << "Satellite file not found. We will create a new one for you.\n";
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
    cout << "Satellites loaded: " << satellites.size() << " \n";
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
    cout << "\nPress Enter to continue...";
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
        cout << "  (list od planets is empty)\n";
    }
    else {
        cout << "  Existing planets:\n";
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

    cout << "\n=== Adding planet ===\n";

    cout << "Enter the name of the planet: ";
    cin.ignore();
    getline(cin, planet.name);

    // Проверка на уникальность имени
    if (planetExists(planet.name)) {
        cout << "Error: planets with one name are not welcome in ANY system!\n";
        return;
    }

    cout << "Enter the age of the planet (in millions of years): ";
    cin >> planet.age;

    cout << "Enter average temperature (in °C): ";
    cin >> planet.temperature;

    cout << "Enter the main colour of the planet: ";
    cin.ignore();
    getline(cin, planet.color);

    cout << "Enter general describtion: ";
    getline(cin, planet.description);

    planets.push_back(planet);

    // Автосохранение после добавления
    savePlanets();

    cout << "\nPlanet \"" << planet.name << "\" successfully added to the database! \n";
}

// Функция для добавления спутника 
void addSatellite() {
    if (planets.empty()) {
        cout << "\nError: you need to have at least one planet to record data of your satellite!\n";
        showPlanetsList();
        return;
    }

    Satellite satellite;

    cout << "\n=== Adding Satellite ===\n";

    cout << "Enter the name of the satellite: ";
    cin.ignore();
    getline(cin, satellite.name);

    // Проверка на уникальность имени спутника
    for (const auto& sat : satellites) {
        if (sat.name == satellite.name) {
            cout << "Error: sattelites with one name are not welcome in ANY system!\n";
            return;
        }
    }

    cout << "Enter the age of the satellite (in millions of years): ";
    cin >> satellite.age;

    cout << "Enter average temperature (in °C): ";
    cin >> satellite.temperature;

    cout << "Enter the main colour of the satellite: ";
    cin.ignore();
    getline(cin, satellite.color);

    cout << "Enter general describtion: ";
    getline(cin, satellite.description);

    // Ввод и проверка планеты-хозяина
    bool validPlanet = false;
    do {
        cout << "\nTo which planet this satellite belongs to?\n";
        showPlanetsList();
        cout << "\nEnter the name of the planet: ";
        getline(cin, satellite.planetName);

        if (planetExists(satellite.planetName)) {
            validPlanet = true;
        }
        else {
            cout << "\nError: planet \"" << satellite.planetName << "\" never existed yet!\n";
            cout << "Please, enter the name from the list above.\n";
        }
    } while (!validPlanet);

    satellites.push_back(satellite);

    // Автосохранение после добавления
    saveSatellites();

    cout << "\nSatellite \"" << satellite.name << "\" successfully added to the database! \""
        << satellite.planetName << "\" and saved!\n";
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
            cout << "Wrong choice. Try again.\n";
            pressEnterToContinue();
        }
    } while (choice != 3);
}

// Функция для форматированного вывода планет
void displayPlanet(const Planet& planet, int index) {
    cout << index << ". " << planet.name << "\n";
    cout << "   Age: " << planet.age << " mill. of years\n";
    cout << "   Temperature: " << planet.temperature << " °C\n";
    cout << "   Colour: " << planet.color << "\n";
    cout << "   Describtion: " << planet.description << "\n";
    cout << "----------------------------------------\n";
}

// Функция для форматированного вывода спутников
void displaySatellite(const Satellite& satellite, int index) {
    cout << index << ". " << satellite.name << "\n";
    cout << "   Planet: " << satellite.planetName << "\n";
    cout << "   Age: " << satellite.age << " mill. of years\n";
    cout << "   Temperature: " << satellite.temperature << " °C\n";
    cout << "   Colour: " << satellite.color << "\n";
    cout << "   Describtion: " << satellite.description << "\n";
    cout << "----------------------------------------\n";
}

// Функция для просмотра данных
void viewData() {
    clearScreen();
    cout << "\" SOLAR TALES \"\n\n";
    cout << "=== Viewing Data ===\n\n";

    cout << "PLANETS:\n";
    cout << "========================================\n";
    if (planets.empty()) {
        cout << "No data found.\n";
    }
    else {
        for (size_t i = 0; i < planets.size(); i++) {
            displayPlanet(planets[i], i + 1);
        }
    }

    cout << "\nSATELLITES:\n";
    cout << "========================================\n";
    if (satellites.empty()) {
        cout << "No data found.\n";
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
    cout << "=== Data Destruction ===\n\n";

    if (planets.empty() && satellites.empty()) {
        cout << "No data to destroy.\n";
        pressEnterToContinue();
        return;
    }

    int choice;
    cout << "What do you wish to destroy?\n";
    cout << "1 - Planet\n";
    cout << "2 - Satellite\n";
    cout << "3 - Back\n";
    cout << "Your choice: ";
    cin >> choice;

    if (choice == 1) {
        if (planets.empty()) {
            cout << "No planets to destroy. :(\n";
        }
        else {
            cout << "\nAvailable planets:\n";
            for (size_t i = 0; i < planets.size(); i++) {
                cout << i + 1 << ". " << planets[i].name << "\n";
            }

            int planetChoice;
            cout << "\nEnter planet number for destruction (0 to show mercy): ";
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

                cout << "Planet \"" << planetName << "\" and her satellites were destroyed by you. Data saved tho!.\n";
            }
        }
    }
    else if (choice == 2) {
        if (satellites.empty()) {
            cout << "No satellites to destroy.\n";
        }
        else {
            cout << "\nAvailable sattelites:\n";
            for (size_t i = 0; i < satellites.size(); i++) {
                cout << i + 1 << ". " << satellites[i].name
                    << " (planet: " << satellites[i].planetName << ")\n";
            }

            int satelliteChoice;
            cout << "\nEnter satellite number for destruction (0 to show mercy): ";
            cin >> satelliteChoice;

            if (satelliteChoice > 0 && satelliteChoice <= satellites.size()) {
                string satelliteName = satellites[satelliteChoice - 1].name;
                satellites.erase(satellites.begin() + satelliteChoice - 1);

                // Сохраняем изменения
                saveSatellites();

                cout << "Satellite \"" << satelliteName << "\" destroyed by you. Why? Data saved.\n";
            }
        }
    }

    pressEnterToContinue();
}

// Меню ручного сохранения
void saveMenu() {
    clearScreen();
    cout << "\" SOLAR TALES \"\n\n";
    cout << "=== Data saving ===\n\n";

    cout << "1 - Save all data\n";
    cout << "2 - Save only planets\n";
    cout << "3 - Save only satelliets\n";
    cout << "4 - Back\n";
    cout << "Your choice: ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        saveAllData();
        cout << "All data saved!\n";
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
        cout << "Wrong choice!\n";
    }

    pressEnterToContinue();
}

// Остальные функции
void searchFilter() {
    clearScreen();
    cout << "\" SOLAR TALES \"\n\n";
    cout << "=== Search/Filters ===\n\n";

    cout << "1 - Search by name\n";
    cout << "2 - Search by planet (for satellites)\n";
    cout << "3 - Save data (by hand)\n";
    cout << "4 - Back\n";
    cout << "Your choice: ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1: {
        // Поиск по имени
        if (planets.empty() && satellites.empty()) {
            cout << "Data base is empty. :(\n";
            pressEnterToContinue();
            return;
        }

        string searchName;
        cout << "Enter name for the search: ";
        cin.ignore();
        getline(cin, searchName);

        bool found = false;

        // Поиск среди планет
        for (const auto& planet : planets) {
            if (planet.name.find(searchName) != string::npos) {
                if (!found) {
                    cout << "\nResults:\n";
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
                    cout << "\nResults:\n";
                    cout << "========================================\n";
                    found = true;
                }
                displaySatellite(satellite, 1);
            }
        }

        if (!found) {
            cout << "\nObjects named \"" << searchName << "\" never existed yet.\n";
        }
        pressEnterToContinue();
        break;
    }
    case 2:
        cout << "\nWork in progress. :P\n";
        pressEnterToContinue();
        break;
    case 3:
        saveMenu();
        break;
    case 4:
        break;
    default:
        cout << "Wrong choice!\n";
        pressEnterToContinue();
    }
}

void showSummary() {
    clearScreen();
    cout << "\" SOLAR TALES \"\n\n";
    cout << "=== Statistics ===\n\n";

    cout << "General statistics:\n";
    cout << "-----------------\n";
    cout << "Amount of planets: " << planets.size() << "\n";
    cout << "Amount of satellites: " << satellites.size() << "\n";
    cout << "Amount of objects: " << planets.size() + satellites.size() << "\n";

    cout << "\nData files:\n";
    cout << "-------------\n";
    cout << "Planets file: " << PLANETS_FILE << "\n";
    cout << "Sitellites file: " << SATELLITES_FILE << "\n";

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

        cout << "\nStatistics on planets:\n";
        cout << "----------------------\n";
        cout << "Average age: " << totalAge / planets.size() << " mill. of years\n";
        cout << "Average temperature: " << totalTemp / planets.size() << " °C\n";
        cout << "Oldest planet: " << oldestPlanet << " (" << oldestAge << " mill. of years)\n";
        cout << "Hottest planet: " << hottestPlanet << " (" << hottestTemp << " °C)\n";
    }

    pressEnterToContinue();
}

void sortData() {
    clearScreen();
    cout << "\" SOLAR TALES \"\n\n";
    cout << "=== Data Sorting ===\n\n";

    cout << "1 - Sort planets by name\n";
    cout << "2 - Sort planets by age\n";
    cout << "3 - Sort planets by temperature\n";
    cout << "4 - Sort satellites by name\n";
    cout << "5 - Sort satellites by planets\n";
    cout << "6 - Back\n";
    cout << "Your choice: ";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        sort(planets.begin(), planets.end(),
            [](const Planet& a, const Planet& b) { return a.name < b.name; });
        cout << "Planets sorted by name.\n";
        break;
    case 2:
        sort(planets.begin(), planets.end(),
            [](const Planet& a, const Planet& b) { return a.age < b.age; });
        cout << "Planets sorted by age.\n";
        break;
    case 3:
        sort(planets.begin(), planets.end(),
            [](const Planet& a, const Planet& b) { return a.temperature < b.temperature; });
        cout << "Planets sorted by temperature.\n";
        break;
    case 4:
        sort(satellites.begin(), satellites.end(),
            [](const Satellite& a, const Satellite& b) { return a.name < b.name; });
        cout << "Satellites sorted by name.\n";
        break;
    case 5:
        sort(satellites.begin(), satellites.end(),
            [](const Satellite& a, const Satellite& b) { return a.planetName < b.planetName; });
        cout << "Satellites sorted by planet.\n";
        break;
    case 6:
        return;
    default:
        cout << "Wrong choice. Try again.\n";
    }

    pressEnterToContinue();
}

int main() {
    setlocale(LC_ALL, "RU");

    int choice;

    // Загружаем данные при запуске
    cout << "Loading resources!\n";
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
            cout << "Data saved in files:\n";
            cout << "1. " << PLANETS_FILE << " (planets)\n";
            cout << "2. " << SATELLITES_FILE << " (satellites)\n";
            cout << "\nMay the great cosmos guide you. See you tommorow!\n";
            break;
        default:
            cout << "Seems like you'va made a mistake. Try again.\n";
            pressEnterToContinue();
        }
    } while (choice != 7);

    return 0;
}