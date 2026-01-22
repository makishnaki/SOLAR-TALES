#include <iostream> // Input/Output
#include <string> // Для создания переменных поддерживающих слова
#include <vector> // Динамический массив, растет по мере добавления данных
#include <limits> // Для очистки входного буфера
#include <algorithm> // Для функций сортировки, поиска, изменения, копирования, удаления, минимума/максимума
#include <fstream>  // Для работы с файлами
#include <chrono>  //
#include <thread>  //

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

// функция лодера
void sleep_ms(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void loaderSequence(const std::vector<std::string>& messages, int totalSteps = 40, int delayMs = 60) {
    //каждое сообщение показываем на своей стадии лоадера
    for (size_t i = 0; i < messages.size(); ++i) {
        for (int step = 0; step <= totalSteps; ++step) {
            int progress = static_cast<int>((step * 100) / totalSteps);
            //выводим статус загрузки и текущее сообщение
            std::cout << "Loading in progress: " << progress << "%\n";
            std::cout << messages[i] << "\n";
            //имитация прогресса
            std::cout << "[";
            int filled = (step * 20) / totalSteps;
            for (int j = 0; j < 20; ++j) {
                std::cout << (j < filled ? '=' : ' ');
            }
            std::cout << "]\n";
            sleep_ms(delayMs);
        }
    }
}


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
        cout << "\033[38;2;160;33;37mError: failed to open planets save file!\033[0m\n";
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
    cout << "\033[38;2;210;148;94mPlanets data saved in file:\033[0m \033[38;2;191;58;51m" << PLANETS_FILE << "\033[0m\n";
}

// Загрузка планет из бинарного файла
void loadPlanets() {
    ifstream file(PLANETS_FILE, ios::binary);

    if (!file) {
        cout << "\033[38;2;191;58;51mPlanet file not found. We will create a new one for you.\033[0m\n";
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
    cout << "\033[38;2;210;148;94mPlanets loaded:\033[0m \033[38;2;191;58;51m" << planets.size() << " \033[0m\n";
}

// Сохранение спутников в бинарный файл
void saveSatellites() {
    ofstream file(SATELLITES_FILE, ios::binary);

    if (!file) {
        cout << "\033[38;2;160;33;37mError: failed to open satellites save file!\033[0m\n";
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
    cout << "\033[38;2;210;148;94mSatellites data saved in file:\033[0m \033[38;2;191;58;51m" << SATELLITES_FILE << "\033[0m\n";
}

// Загрузка спутников из бинарного файла
void loadSatellites() {
    ifstream file(SATELLITES_FILE, ios::binary);

    if (!file) {
        cout << "\033[38;2;191;58;51mSatellite file not found. We will create a new one for you.\033[0m\n";
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
    cout << "\03[38;2;210;148;94mSatellites loaded:\033[0m \033[38;2;191;58;51m" << satellites.size() << " \033[0m\n";
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
    cout << "\n\033[38;2;255;255;255mPress Enter to continue...\033[0m";
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
        cout << "\033[38;2;191;58;51m  (list od planets is empty)\033[0m\n";
    }
    else {
        cout << "\033[38;2;210;148;94  Existing planets:\033[0m\n";
        for (const auto& planet : planets) {
            cout << "  - " << planet.name << "\n";
        }
    }
}

// Функция отображения главного меню
void showMainMenu() {
    std::vector<std::string> startupMessages = {
    "Initializing modules...",
    "Loading configurations...",
    "Updating data...",
    "Setting up the radar...", 
    "Accessing the on-board computer..."
    };
    //запуск лоадера после старта
    loaderSequence(startupMessages);
    clearScreen();
    cout << "\"\033[38;2;255;255;255m SOLAR TALES \033[0m\"\n\n";
    cout << "\033[38;2;210;148;94mMain Menu:\033[0m\n";
    cout << "\033[38;2;191;58;51m- 1 -\033[0m \033[38;2;210;148;94mAdd data\033[0m\n";
    cout << "\033[38;2;191;58;51m- 2 -\033[0m \033[38;2;210;148;94mView data\033[0m\n";
    cout << "\033[38;2;191;58;51m- 3 -\033[0m \033[38;2;210;148;94mDelete data\033[0m\n";
    cout << "\033[38;2;191;58;51m- 4 -\033[0m \033[38;2;210;148;94mSearch/Filter\033[0m\n";
    cout << "\033[38;2;191;58;51m- 5 -\033[0m \033[38;2;210;148;94mSummary\033[0m\n";
    cout << "\033[38;2;191;58;51m- 6 -\033[0m \033[38;2;210;148;94mSort\033[0m\n";
    cout << "\033[38;2;191;58;51m- 7 -\033[0m \033[38;2;210;148;94mSave and Exit\033[0m\n";
    cout << "\n\033[38;2;255;255;255mEnter Your choice : \033[0m";
}

// Функция для добавления планеты
void addPlanet() {
    Planet planet;

    cout << "\n\033[38;2;210;148;94m=== Adding planet ===\033[0m\n";

    cout << "\033[38;2;210;148;94mEnter the name of the planet: \033[0m\033[38;2;191;58;51m";
    cin.ignore();
    getline(cin, planet.name);

    // Проверка на уникальность имени
    if (planetExists(planet.name)) {
        cout << "\033[0m\033[38;2;160;33;37mError: planets with one name are not welcome in ANY system!\033[0m\n";
        return;
    }

    cout << "\033[0m\033[38;2;210;148;94mEnter the age of the planet (in millions of years): \033[0m\033[38;2;191;58;51m";
    cin >> planet.age;

    cout << "\033[0m\033[38;2;210;148;94mEnter average temperature (in °C): \033[0m\033[38;2;191;58;51m";
    cin >> planet.temperature;

    cout << "\033[0m\033[38;2;210;148;94mEnter the main colour of the planet: \033[0m\033[38;2;191;58;51m";
    cin.ignore();
    getline(cin, planet.color);

    cout << "\033[0m\033[38;2;210;148;94mEnter general describtion: \033[0m\033[38;2;191;58;51m";
    getline(cin, planet.description);

    planets.push_back(planet);

    // Автосохранение после добавления
    savePlanets();

    cout << "\n\033[38;2;210;148;94mPlanet \033[0m\033[38;2;191;58;51m\"" << planet.name << "\"\033[0m \033[38;2;210;148;94msuccessfully added to the database! \033[0m\n";
}

// Функция для добавления спутника 
void addSatellite() {
    if (planets.empty()) {
        cout << "\n\033[38;2;160;33;37mError: you need to have at least one planet to record data of your satellite!\033[0m\n";
        showPlanetsList();
        return;
    }

    Satellite satellite;

    cout << "\n\033[38;2;210;148;94m=== Adding Satellite ===\033[0m\n";

    cout << "\033[38;2;210;148;94mEnter the name of the satellite: \033[0m\033[38;2;191;58;51m";
    cin.ignore();
    getline(cin, satellite.name);

    // Проверка на уникальность имени спутника
    for (const auto& sat : satellites) {
        if (sat.name == satellite.name) {
            cout << "\033[0m\033[38;2;160;33;37mError: sattelites with one name are not welcome in ANY system!\033[0m\n";
            return;
        }
    }

    cout << "\033[0m\033[38;2;211;94;142mEnter the age of the satellite (in millions of years): \033[0m\033[38;2;191;58;51m";
    cin >> satellite.age;

    cout << "\033[0m\033[38;2;211;94;142mEnter average temperature (in °C): \033[0m\033[38;2;191;58;51m";
    cin >> satellite.temperature;

    cout << "\033[0m\033[38;2;211;94;142mEnter the main colour of the satellite: \033[0m\033[38;2;191;58;51m";
    cin.ignore();
    getline(cin, satellite.color);

    cout << "\033[0m\033[38;2;211;94;142mEnter general describtion: \033[0m\033[38;2;191;58;51m";
    getline(cin, satellite.description);

    // Ввод и проверка планеты-хозяина
    bool validPlanet = false;
    do {
        cout << "\n\033[0m\033[38;2;210;148;94mTo which planet this satellite belongs to?\033[0m\033[38;2;191;58;51m\n";
        showPlanetsList();
        cout << "\n\033[0m\033[38;2;211;94;142mEnter the name of the planet: \033[0m\033[38;2;191;58;51m";
        getline(cin, satellite.planetName);

        if (planetExists(satellite.planetName)) {
            validPlanet = true;
        }
        else {
            cout << "\n\033[38;2;160;33;37mError: planet \033[0m\033[38;2;191;58;51m\"" << satellite.planetName << "\" \033[0m\033[38;2;160;33;37mnever existed yet!\033[0m\n";
            cout << "\033[38;2;160;33;37mPlease, enter the name from the list above.\033[0m\n";
        }
    } while (!validPlanet);

    satellites.push_back(satellite);

    // Автосохранение после добавления
    saveSatellites();

    cout << "\n\033[38;2;210;148;94mSatellite \033[0m\033[38;2;191;58;51m\"" << satellite.name << "\"\033[0m\033[38;2;210;148;94m successfully added to the database! \033[0m\033[38;2;191;58;51m\""
        << satellite.planetName << "\"\033[0m]033[38;2;210;148;94m and saved!\033[0m\n";
}

// Функция отображения меню добавления данных
void showAddDataMenu() {
    int choice;

    do {
        clearScreen();
        cout << "\"\033[38;2;255;255;255m SOLAR TALES \033[0m\"\n\n";
        cout << "\033[38;2;210;148;94mAdd Data Menu:\033[0m\n";
        cout << "\033[38;2;191;58;51m- 1 -\033[0m\033[38;2;210;148;94m PLANET\033[0m\n";
        cout << "\033[38;2;191;58;51m- 2 -\033[0m\033[38;2;210;148;94m SATELLITE\033[0m\n";
        cout << "\033[38;2;191;58;51m- 3 -\033[0m\033[38;2;210;148;94m Back\033[0m\n";
        cout << "\n\033[38;2;191;58;51mEnter Your choice : \033[0m";
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
            cout << "\033[38;2;160;33;37mWrong choice. Try again.\033[0m\n";
            pressEnterToContinue();
        }
    } while (choice != 3);
}

// Функция для форматированного вывода планет
void displayPlanet(const Planet& planet, int index) {
    cout << index << ". " << planet.name << "\n";
    cout << "\033[38;2;210;148;94m   Age: \033[0m\033[38;2;191;58;51m" << planet.age << "\033[0m\033[38;2;210;148;94m mill. of years\033[0m\n";
    cout << "\033[38;2;210;148;94m   Temperature: \033[0m\033[38;2;191;58;51m" << planet.temperature << "\033[38;2;210;148;94m °C\033[0m\n";
    cout << "\033[38;2;210;148;94m   Colour: \033[0m\033[38;2;191;58;51m" << planet.color << "\033[0m\n";
    cout << "\033[38;2;210;148;94m   Describtion: \033[0m\033[38;2;191;58;51m" << planet.description << "\033[0m\n";
    cout << "----------------------------------------\n";
}

// Функция для форматированного вывода спутников
void displaySatellite(const Satellite& satellite, int index) {
    cout << index << ". " << satellite.name << "\n";
    cout << "\033[38;2;210;148;94m   Planet: \033[0m\033[38;2;191;58;51m" << satellite.planetName << "\033[0m\n";
    cout << "\033[38;2;210;148;94m   Age: \033[0m\033[38;2;191;58;51m" << satellite.age << "\033[0m\033[38;2;210;148;94m mill. of years\033[0m\n";
    cout << "\033[38;2;210;148;94m   Temperature: \033[0m\033[38;2;191;58;51m" << satellite.temperature << "\033[0m\033[38;2;210;148;94m °C\033[0m\n";
    cout << "\033[38;2;210;148;94m   Colour: \033[0m\033[38;2;191;58;51m" << satellite.color << "\033[0m\n";
    cout << "\033[38;2;210;148;94m   Describtion: \033[0m\033[38;2;191;58;51m" << satellite.description << "\033[0m\n";
    cout << "----------------------------------------\n";
}

// Функция для просмотра данных
void viewData() {
    clearScreen();
    cout << "\"\033[38;2;255;255;255m SOLAR TALES \033[0m\"\n\n";
    cout << "\033[38;2;210;148;94m=== Viewing Data ===\033[0m\n\n";

    cout << "\033[38;2;210;148;94mPLANETS:\033[0m\n";
    cout << "========================================\n";
    if (planets.empty()) {
        cout << "\033[38;2;191;58;51mNo data found.\033[0m\n";
    }
    else {
        for (size_t i = 0; i < planets.size(); i++) {
            displayPlanet(planets[i], i + 1);
        }
    }

    cout << "\n\033[38;2;210;148;94mSATELLITES:\033[0m\n";
    cout << "========================================\n";
    if (satellites.empty()) {
        cout << "\033[38;2;191;58;51mNo data found.\033[0m\n";
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
    cout << "\"\033[38;2;255;255;255m SOLAR TALES \033[0m\"\n\n";
    cout << "\033[38;2;210;148;94m=== Data Destruction ===\033[0m\n\n";

    if (planets.empty() && satellites.empty()) {
        cout << "\033[38;2;191;58;51mNo data to destroy.\033[0m\n";
        pressEnterToContinue();
        return;
    }

    int choice;
    cout << "\033[38;2;210;148;94mWhat do you wish to destroy?\033[0m\n";
    cout << "\033[38;2;191;58;51m1 - \033[0m\033[38;2;210;148;94mPlanet\033[0m\n";
    cout << "\033[38;2;191;58;51m2 - \033[0m\033[38;2;210;148;94mSatellite\033[0m\n";
    cout << "\033[38;2;191;58;51m3 - \033[0m\033[38;2;210;148;94mBack\033[0m\n";
    cout << "\033[38;2;210;148;94mYour choice: \033[0m\033[38;2;191;58;51m";
    cin >> choice;

    if (choice == 1) {
        if (planets.empty()) {
            cout << "\033[0m\033[38;2;210;148;94mNo planets to destroy. :(\033[0m\n";
        }
        else {
            cout << "\n\033[0m\033[38;2;210;148;94mAvailable planets:\033[0m\n";
            for (size_t i = 0; i < planets.size(); i++) {
                cout << i + 1 << ". " << planets[i].name << "\n";
            }

            int planetChoice;
            cout << "\n\033[38;2;210;148;94mEnter planet number for destruction (0 to show mercy): \033[0m\033[38;2;191;58;51m";
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

                cout << "\033[0m\033[38;2;210;148;94mPlanet \033[0m\033[38;2;191;58;51m\"" << planetName << "\"\033[0m\033[38;2;210;148;94m and her satellites were destroyed by you. Data saved tho!.\033[0m\n";
            }
        }
    }
    else if (choice == 2) {
        if (satellites.empty()) {
            cout << "\033[38;2;191;58;51mNo satellites to destroy.\033[0m\n";
        }
        else {
            cout << "\n\033[38;2;210;148;94mAvailable sattelites:\033[0m\n";
            for (size_t i = 0; i < satellites.size(); i++) {
                cout << i + 1 << ". " << satellites[i].name
                    << " (planet: " << satellites[i].planetName << ")\n";
            }

            int satelliteChoice;
            cout << "\n\033[38;2;210;148;94mEnter satellite number for destruction (0 to show mercy): \033[0m\033[38;2;191;58;51m";
            cin >> satelliteChoice;

            if (satelliteChoice > 0 && satelliteChoice <= satellites.size()) {
                string satelliteName = satellites[satelliteChoice - 1].name;
                satellites.erase(satellites.begin() + satelliteChoice - 1);

                // Сохраняем изменения
                saveSatellites();

                cout << "\033[0m\033[38;2;210;148;94mSatellite \033[0m\033[38;2;191;58;51m\"" << satelliteName << "\"\033[0m\033[38;2;210;148;94m destroyed by you. Why? Data saved.\033[0m\n";
            }
        }
    }

    pressEnterToContinue();
}

// Меню ручного сохранения
void saveMenu() {
    clearScreen();
    cout << "\"\033[38;2;255;255;255m SOLAR TALES \033[0m\"\n\n";
    cout << "\033[38;2;210;148;94m=== Data saving ===\033[0m\n\n";

    cout << "\033[38;2;191;58;51m1 - \033[0m\033[38;2;210;148;94mSave all data\033[0m\n";
    cout << "\033[38;2;191;58;51m2 - \033[0m\033[38;2;210;148;94mSave only planets\033[0m\n";
    cout << "\033[38;2;191;58;51m3 - \033[0m\033[38;2;210;148;94mSave only satelliets\033[0m\n";
    cout << "\033[38;2;191;58;51m4 - \033[0m\033[38;2;210;148;94mBack\033[0m\n";
    cout << "\033[38;2;210;148;94mYour choice: \033[0m\033[38;2;191;58;51m";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        saveAllData();
        cout << "\033[0m\033[38;2;210;148;94mAll data saved!\033[0m\n";
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
        cout << "\033[38;2;160;33;37mWrong choice!\033[0m\n";
    }

    pressEnterToContinue();
}

// Остальные функции
void searchFilter() {
    clearScreen();
    cout << "\"\033[38;2;255;255;255m SOLAR TALES \033[0m\"\n\n";
    cout << "\033[38;2;210;148;94m=== Search/Filters ===\033[0m\n\n";

    cout << "\033[38;2;191;58;51m1 - \033[0m\033[38;2;210;148;94mSearch by name\033[0m\n";
    cout << "\033[38;2;191;58;51m2 - \033[0m\033[38;2;210;148;94mSearch by planet (for satellites)\033[0m\n";
    cout << "\033[38;2;191;58;51m3 - \033[0m\033[38;2;210;148;94mSave data (by hand)\033[0m\n";
    cout << "\033[38;2;191;58;51m4 - \033[0m\033[38;2;210;148;94mBack\033[0m\n";
    cout << "\033[38;2;210;148;94mYour choice: \033[0m\033[38;2;191;58;51m";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1: {
        // Поиск по имени
        if (planets.empty() && satellites.empty()) {
            cout << "\033[0m\033[38;2;191;58;51mData base is empty. :(\033[0m\n";
            pressEnterToContinue();
            return;
        }

        string searchName;
        cout << "\033[38;2;210;148;94mEnter name for the search: \033[0m\033[38;2;191;58;51m";
        cin.ignore();
        getline(cin, searchName);

        bool found = false;

        // Поиск среди планет
        for (const auto& planet : planets) {
            if (planet.name.find(searchName) != string::npos) {
                if (!found) {
                    cout << "\n\033[0m\033[38;2;210;148;94mResults:\033[0m\n";
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
                    cout << "\n\033[0m\033[38;2;210;148;94mResults:\033[0m\n";
                    cout << "========================================\n";
                    found = true;
                }
                displaySatellite(satellite, 1);
            }
        }

        if (!found) {
            cout << "\n\033[38;2;210;148;94mObjects named \033[0m\033[38;2;191;58;51m\"" << searchName << "\" \033[0m\033[38;2;210;148;94mnever existed yet.\033[0m\n";
        }
        pressEnterToContinue();
        break;
    }
    case 2:
        cout << "\n\033[38;2;210;148;94mWork in progress. :P\033[0m\n";
        pressEnterToContinue();
        break;
    case 3:
        saveMenu();
        break;
    case 4:
        break;
    default:
        cout << "\033[38;2;191;58;51mWrong choice!\033[0m\n";
        pressEnterToContinue();
    }
}

void showSummary() {
    clearScreen();
    cout << "\"\033[38;2;255;255;255m SOLAR TALES \033[0m\"\n\n";
    cout << "\033[38;2;210;148;94m=== Statistics ===\033[0m\n\n";

    cout << "\033[38;2;210;148;94mGeneral statistics:\033[0m\n";
    cout << "-----------------\n";
    cout << "\033[38;2;210;148;94mAmount of planets: \033[0m\033[38;2;191;58;51m" << planets.size() << "\033[0m\n";
    cout << "\033[38;2;210;148;94mAmount of satellites: \033[0m\033[38;2;191;58;51m" << satellites.size() << "\033[0m\n";
    cout << "\033[38;2;210;148;94mAmount of objects: \033[0m\033[38;2;191;58;51m" << planets.size() + satellites.size() << "\033[0m\n";

    cout << "\n\033[38;2;210;148;94mData files:\033[0m\n";
    cout << "-------------\n";
    cout << "\033[38;2;210;148;94mPlanets file: \033[0m\033[38;2;191;58;51m" << PLANETS_FILE << "\033[0m\n";
    cout << "\033[38;2;210;148;94mSitellites file: \033[0m\033[38;2;191;58;51m" << SATELLITES_FILE << "\033[0m\n";

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

        cout << "\n\033[38;2;210;148;94mStatistics on planets:\033[0m\n";
        cout << "----------------------\n";
        cout << "\033[38;2;210;148;94mAverage age: \033[0m\033[38;2;191;58;51m" << totalAge / planets.size() << " \033[0m\033[38;2;210;148;94mmill. of years\033[0m\n";
        cout << "\033[38;2;210;148;94mAverage temperature: \033[0m\033[38;2;191;58;51m" << totalTemp / planets.size() << " \033[0m\033[38;2;210;148;94m°C\033[0m\n";
        cout << "\033[38;2;210;148;94mOldest planet: \033[0m\033[38;2;191;58;51m" << oldestPlanet << " \033[0m\033[38;2;210;148;94m(\033[0m\033[38;2;191;58;51m" << oldestAge << " \033[0m\033[38;2;210;148;94mmill. of years)\033[0m\n";
        cout << "\033[38;2;210;148;94mHottest planet: \033[0m\033[38;2;191;58;51m" << hottestPlanet << " \033[0m\033[38;2;210;148;94m(\033[0m\033[38;2;191;58;51m" << hottestTemp << " \033[0m\033[38;2;210;148;94m°C)\033[0m\n";
    }

    pressEnterToContinue();
}

void sortData() {
    clearScreen();
    cout << "\"\033[0m\033[38;2;255;255;255m SOLAR TALES \033[0m\"\n\n";
    cout << "\033[38;2;210;148;94m=== Data Sorting ===\033[0m\n\n";

    cout << "\033[38;2;191;58;51m1 - \033[0m\033[38;2;210;148;94mSort planets by name\033[0m\n";
    cout << "\033[38;2;191;58;51m2 - \033[0m\033[38;2;210;148;94mSort planets by age\033[0m\n";
    cout << "\033[38;2;191;58;51m3 - \033[0m\033[38;2;210;148;94mSort planets by temperature\033[0m\n";
    cout << "\033[38;2;191;58;51m4 - \033[0m\033[38;2;210;148;94mSort satellites by name\033[0m\n";
    cout << "\033[38;2;191;58;51m5 - \033[0m\033[38;2;210;148;94mSort satellites by planets\033[0m\n";
    cout << "\033[38;2;191;58;51m6 - \033[0m\033[38;2;210;148;94mBack\033[0m\n";
    cout << "\033[38;2;210;148;94mYour choice: \033[0m\033[38;2;191;58;51m";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        sort(planets.begin(), planets.end(),
            [](const Planet& a, const Planet& b) { return a.name < b.name; });
        cout << "\033[0m\033[38;2;210;148;94mPlanets sorted by name.\033[0m\n";
        break;
    case 2:
        sort(planets.begin(), planets.end(),
            [](const Planet& a, const Planet& b) { return a.age < b.age; });
        cout << "\033[0m\033[38;2;210;148;94mPlanets sorted by age.\033[0m\n";
        break;
    case 3:
        sort(planets.begin(), planets.end(),
            [](const Planet& a, const Planet& b) { return a.temperature < b.temperature; });
        cout << "\033[0m\033[38;2;210;148;94mPlanets sorted by temperature.\033[0m\n";
        break;
    case 4:
        sort(satellites.begin(), satellites.end(),
            [](const Satellite& a, const Satellite& b) { return a.name < b.name; });
        cout << "\033[0m\033[38;2;210;148;94mSatellites sorted by name.\033[0m\n";
        break;
    case 5:
        sort(satellites.begin(), satellites.end(),
            [](const Satellite& a, const Satellite& b) { return a.planetName < b.planetName; });
        cout << "\033[0m\033[38;2;210;148;94mSatellites sorted by planet.\033[0m\n";
        break;
    case 6:
        return;
    default:
        cout << "\033[38;2;160;33;37mWrong choice. Try again.\033[0m\n";
    }

    pressEnterToContinue();
}

int main() {
    setlocale(LC_ALL, "RU");

    int choice;

    // Загружаем данные при запуске
    cout << "\033[38;2;210;148;94mLoading resources!\033[0m\n";
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
            cout << "\033[38;2;210;148;94mData saved in files:\033[0m\n";
            cout << "\033[38;2;210;148;94m1. \033[0m\033[38;2;210;148;94m" << PLANETS_FILE << "\033[38;2;210;148;94m (planets)\033[0m\n";
            cout << "\033[38;2;210;148;94m2. \033[0m\033[38;2;191;58;51m" << SATELLITES_FILE << "\033[38;2;210;148;94m (satellites)\033[0m\n";
            cout << "\n\033[38;2;210;148;94mMay the great cosmos guide you. See you tommorow!\033[0m\n";
            break;
        default:
            cout << "\033[38;2;160;33;37mSeems like you'va made a mistake. Try again.\033[0m\n";
            pressEnterToContinue();
        }
    } while (choice != 7);

    return 0;
}
