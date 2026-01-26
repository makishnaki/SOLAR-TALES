#include <iostream> // Input/Output
#include <string> // Для создания переменных поддерживающих слова
#include <vector> // Динамический массив, растет по мере добавления данных
#include <limits> // Для очистки входного буфера
#include <algorithm> // Для функций сортировки, поиска, изменения, копирования, удаления, минимума/максимума
#include <fstream>  // Для работы с файлами
#include <chrono>  // библиотека для работы со временем
#include <thread>  // для потоков и выполнения нескольких задач одновременно

using namespace std;

// ↓ ----------- Структуры для хранения данных ----------- ↓

struct Planet { // структура планет
    string name;
    int age;
    int temperature;
    string color;
    string description;
};

struct Satellite { // структура спутников
    string name;
    int age;
    int temperature;
    string color;
    string description;
    string planetName;
};

// Векторы для хранения данных
vector<Planet> planets;
vector<Satellite> satellites; // для списков планет и спутников

// Имена файлов для сохранения
const string PLANETS_FILE = "planets.dat";
const string SATELLITES_FILE = "satellites.dat";

// функция лодера
void sleep_ms(int ms) { // задержка выполнения на заданное количество миллисекунд
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void loaderSequence(const std::vector<std::string>& messages, int totalSteps = 40, int delayMs = 60) {
    //каждое сообщение показываем на своей стадии лоадера
    for (size_t i = 0; i < messages.size(); ++i) { // принимает набор сообщений, эмитирует их на разных стадиях лоадера и эмулирует процесс загрузки с прогрессбаром
        for (int step = 0; step <= totalSteps; ++step) {
            int progress = static_cast<int>((step * 100) / totalSteps); // progress вычисляется как % от текущего шага
            //выводим статус загрузки и текущее сообщение
            std::cout << "\033[38;2;83;1;1mLoading in progress: " << progress << "%\n";
            std::cout << messages[i] << "\n"; // каждый элемент сообщения будет выводиться на своей стадии лоадера
            //имитация прогресса
            std::cout << "[";
            int filled = (step * 20) / totalSteps;
            for (int j = 0; j < 20; ++j) {
                std::cout << (j < filled ? '=' : ' '); // рисуется простая консольная полоска
            }
            std::cout << "]\033[0m\n";
            sleep_ms(delayMs); // после этого вызывается sleep ms для задержки между шагами
        }
    }
}


// Функция для сохранения строки в бинарный файл
void saveString(ofstream& file, const string& str) { // сначала записывается размер строки, затем пишутся сами символы
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
        cout << "\033[38;2;83;1;1mError: failed to open planets save file!\033[0m\n";
        return;
    }

    // Сохраняем количество планет
    size_t count = planets.size(); //
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
    cout << "\033[38;2;187;219;220mPlanets data saved in file:\033[0m \033[38;2;73;149;142m" << PLANETS_FILE << "\033[0m\n";
}

// Загрузка планет из бинарного файла
void loadPlanets() {
    ifstream file(PLANETS_FILE, ios::binary);

    if (!file) {
        cout << "\033[38;2;73;149;142mPlanet file not found. We will create a new one for you.\033[0m\n";
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
    cout << "\033[38;2;187;219;220mPlanets loaded:\033[0m \033[38;2;73;149;142m" << planets.size() << " \033[0m\n";
}

// Сохранение спутников в бинарный файл
void saveSatellites() {
    ofstream file(SATELLITES_FILE, ios::binary);

    if (!file) {
        cout << "\033[38;2;83;1;1mError: failed to open satellites save file!\033[0m\n";
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
    cout << "\033[38;2;187;219;220mSatellites data saved in file:\033[0m \033[38;2;73;149;142m" << SATELLITES_FILE << "\033[0m\n";
}

// Загрузка спутников из бинарного файла
void loadSatellites() {
    ifstream file(SATELLITES_FILE, ios::binary);

    if (!file) {
        cout << "\033[38;2;73;149;142mSatellite file not found. We will create a new one for you.\033[0m\n";
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
    cout << "\033[38;2;187;219;220mSatellites loaded:\033[0m \033[38;2;73;149;142m" << satellites.size() << " \033[0m\n";
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
    system("clear"); // обращается к компьютеру вызывает system clear
#endif
}

// Функция для ожидания нажатия Enter
void pressEnterToContinue() {
    cout << "\n\033[38;2;188;101;119mPress Enter to continue...\033[0m";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Затем ждёт нажатия Enter через cin.ignore и cin.get()
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
        cout << "\033[38;2;73;149;142m  (list od planets is empty)\033[0m\n";
    }
    else {
        cout << "\033[38;2;187;219;220m  Existing planets:\033[0m\n";
        for (const auto& planet : planets) {
            cout << "  - " << planet.name << "\n";
        }
    }
}

// Функция отображения главного меню
void showMainMenu() {
    std::vector<std::string> startupMessages = {
    "Updating data...",
    "Accessing the on-board computer..."
    };
    //запуск лоадера после старта
    loaderSequence(startupMessages);
    clearScreen();
    cout << "\"\033[38;2;187;219;220m SOLAR TALES \033[0m\"\n\n";
    cout << "\033[38;2;187;219;220mMain Menu:\033[0m\n";
    cout << "\033[38;2;73;149;142m- 1 -\033[0m \033[38;2;187;219;220mAdd data\033[0m\n";
    cout << "\033[38;2;73;149;142m- 2 -\033[0m \033[38;2;187;219;220mView data\033[0m\n";
    cout << "\033[38;2;73;149;142m- 3 -\033[0m \033[38;2;187;219;220mDelete data\033[0m\n";
    cout << "\033[38;2;73;149;142m- 4 -\033[0m \033[38;2;187;219;220mSearch/Filter\033[0m\n";
    cout << "\033[38;2;73;149;142m- 5 -\033[0m \033[38;2;187;219;220mSummary\033[0m\n";
    cout << "\033[38;2;73;149;142m- 6 -\033[0m \033[38;2;187;219;220mSort\033[0m\n";
    cout << "\033[38;2;73;149;142m- 7 -\033[0m \033[38;2;187;219;220mSave and Exit\033[0m\n";
    cout << "\n\033[38;2;188;101;119mEnter Your choice : \033[0m";
}

// Функция для добавления планеты
void addPlanet() {
    Planet planet;

    cout << "\n\033[38;2;187;219;220m=== Adding planet ===\033[0m\n";

    cout << "\033[38;2;188;101;119mEnter the name of the planet: \033[0m\033[38;2;185;43;61m";
    cin.ignore();
    getline(cin, planet.name);

    // Проверка на уникальность имени
    if (planetExists(planet.name)) {
        cout << "\033[0m\033[38;2;83;1;1mError: planets with one name are not welcome in ANY system!\033[0m\n";
        return;
    }

    cout << "\033[0m\033[38;2;188;101;119mEnter the age of the planet (in millions of years): \033[0m\033[38;2;185;43;61m";
    cin >> planet.age;

    cout << "\033[0m\033[38;2;188;101;119mEnter average temperature (in °C): \033[0m\033[38;2;185;43;61m";
    cin >> planet.temperature;

    cout << "\033[0m\033[38;2;188;101;119mEnter the main colour of the planet: \033[0m\033[38;2;185;43;61m";
    cin.ignore();
    getline(cin, planet.color);

    cout << "\033[0m\033[38;2;188;101;119mEnter general describtion: \033[0m\033[38;2;185;43;61m";
    getline(cin, planet.description);

    planets.push_back(planet);

    // Автосохранение после добавления
    savePlanets();

    cout << "\n\033[38;2;187;219;220mPlanet \033[0m\033[38;2;73;149;142m\"" << planet.name << "\"\033[0m \033[38;2;187;219;220msuccessfully added to the database! \033[0m\n";
}

// Функция для добавления спутника 
void addSatellite() {
    if (planets.empty()) {
        cout << "\n\033[38;2;83;1;1mError: you need to have at least one planet to record data of your satellite!\033[0m\n";
        showPlanetsList();
        return;
    }

    Satellite satellite;

    cout << "\n\033[38;2;187;219;220m=== Adding Satellite ===\033[0m\n";

    cout << "\033[0m\033[38;2;188;101;119mEnter the name of the satellite: \033[0m\033[38;2;185;43;61m";
    cin.ignore();
    getline(cin, satellite.name);

    // Проверка на уникальность имени спутника
    for (const auto& sat : satellites) {
        if (sat.name == satellite.name) {
            cout << "\033[0m\033[38;2;83;1;1mError: sattelites with one name are not welcome in ANY system!\033[0m\n";
            return;
        }
    }

    cout << "\033[0m\033[38;2;188;101;119mEnter the age of the satellite (in millions of years): \033[0m\033[38;2;185;43;61m";
    cin >> satellite.age;

    cout << "\033[0m\033[38;2;188;101;119mEnter average temperature (in °C): \033[0m\033[38;2;185;43;61m";
    cin >> satellite.temperature;

    cout << "\033[0m\033[38;2;188;101;119mEnter the main colour of the satellite: \033[0m\033[38;2;185;43;61m";
    cin.ignore();
    getline(cin, satellite.color);

    cout << "\033[0m\033[38;2;188;101;119mEnter general describtion: \033[0m\033[38;2;185;43;61m";
    getline(cin, satellite.description);

    // Ввод и проверка планеты-хозяина
    bool validPlanet = false;
    do {
        cout << "\n\033[0m\033[38;2;188;101;119mTo which planet this satellite belongs to?\033[0m\033[38;2;185;43;61m\n";
        showPlanetsList();
        cout << "\n\033[0m\033[38;2;188;101;119mEnter the name of the planet: \033[0m\033[38;2;185;43;61m";
        getline(cin, satellite.planetName);

        if (planetExists(satellite.planetName)) {
            validPlanet = true;
        }
        else {
            cout << "\n\033[38;2;83;1;1mError: planet \"" << satellite.planetName << "\" never existed yet!\n";
            cout << "Please, enter the name from the list above.\033[0m\n";
        }
    } while (!validPlanet);

    satellites.push_back(satellite);

    // Автосохранение после добавления
    saveSatellites();

    cout << "\n\033[38;2;187;219;220mSatellite \033[0m\033[38;2;73;149;142m\"" << satellite.name << "\"\033[0m\033[38;2;187;219;220m successfully added to the database! \033[0m\033[38;2;73;149;142m\""
        << satellite.planetName << "\"\033[0m]\033[38;2;187;219;220m and saved!\033[0m\n";
}

// Функция отображения меню добавления данных
void showAddDataMenu() {
    int choice;

    do {
        clearScreen();
        cout << "\"\033[38;2;187;219;220m SOLAR TALES \033[0m\"\n\n";
        cout << "\033[38;2;187;219;220mAdd Data Menu:\033[0m\n";
        cout << "\033[38;2;73;149;142m- 1 -\033[0m\033[38;2;187;219;220m PLANET\033[0m\n";
        cout << "\033[38;2;73;149;142m- 2 -\033[0m\033[38;2;187;219;220m SATELLITE\033[0m\n";
        cout << "\033[38;2;73;149;142m- 3 -\033[0m\033[38;2;187;219;220m Back\033[0m\n";
        cout << "\n\033[38;2;188;101;119mEnter Your choice : \033[0m";
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
            cout << "\033[38;2;83;1;1mWrong choice. Try again.\033[0m\n";
            pressEnterToContinue();
        }
    } while (choice != 3);
}

// Функция для форматированного вывода планет
void displayPlanet(const Planet& planet, int index) {
    cout << index << ". " << planet.name << "\n";
    cout << "\033[38;2;187;219;220m   Age: " << planet.age << " mill. of years\033[0m\n";
    cout << "\033[38;2;187;219;220m   Temperature: " << planet.temperature << " °C\033[0m\n";
    cout << "\033[38;2;187;219;220m   Colour: " << planet.color << "\033[0m\n";
    cout << "\033[38;2;187;219;220m   Describtion: " << planet.description << "\033[0m\n";
    cout << "\033[38;2;73;149;142m----------------------------------------\033[0m\n";
}

// Функция для форматированного вывода спутников
void displaySatellite(const Satellite& satellite, int index) {
    cout << index << ". " << satellite.name << "\n";
    cout << "\033[38;2;187;219;220m   Planet: " << satellite.planetName << "\033[0m\n";
    cout << "\033[38;2;187;219;220m   Age: " << satellite.age << " mill. of years\033[0m\n";
    cout << "\033[38;2;187;219;220m   Temperature: " << satellite.temperature << " °C\033[0m\n";
    cout << "\033[38;2;187;219;220m   Colour: " << satellite.color << "\033[0m\n";
    cout << "\033[38;2;187;219;220m   Describtion: " << satellite.description << "\033[0m\n";
    cout << "\033[38;2;73;149;142m----------------------------------------\033[0m\n";
}

// Функция для просмотра данных
void viewData() {
    clearScreen();
    cout << "\"\033[38;2;187;219;220m SOLAR TALES \033[0m\"\n\n";
    cout << "\033[38;2;187;219;220m=== Viewing Data ===\033[0m\n\n";

    cout << "\033[38;2;187;219;220mPLANETS:\033[0m\n";
    cout << "\033[38;2;73;149;142m========================================\033[0m\n";
    if (planets.empty()) {
        cout << "\033[38;2;83;1;1mNo data found.\033[0m\033[38;2;187;219;220m\n";
    }
    else {
        for (size_t i = 0; i < planets.size(); i++) {
            displayPlanet(planets[i], i + 1);
        }
    }

    cout << "\n\033[0m\033[38;2;187;219;220mSATELLITES:\033[0m\n";
    cout << "\033[38;2;73;149;142m========================================\033[0m\n";
    if (satellites.empty()) {
        cout << "\033[38;2;83;1;1mNo data found.\033[0m\033[38;2;187;219;220m\n";
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
    cout << "\"\033[38;2;187;219;220m SOLAR TALES \033[0m\"\n\n";
    cout << "\033[38;2;187;219;220m=== Data Destruction ===\033[0m\n\n";

    if (planets.empty() && satellites.empty()) {
        cout << "\033[38;2;73;149;142mNo data to destroy.\033[0m\n";
        pressEnterToContinue();
        return;
    }

    int choice;
    cout << "\033[38;2;187;219;220mWhat do you wish to destroy?\033[0m\n";
    cout << "\033[38;2;73;149;142m1 - \033[0m\033[38;2;187;219;220mPlanet\033[0m\n";
    cout << "\033[38;2;73;149;142m2 - \033[0m\033[38;2;187;219;220mSatellite\033[0m\n";
    cout << "\033[38;2;73;149;142m3 - \033[0m\033[38;2;187;219;220mBack\033[0m\n";
    cout << "\033[38;2;188;101;119mYour choice: \033[0m\033[38;2;185;43;61m";
    cin >> choice;

    if (choice == 1) {
        if (planets.empty()) {
            cout << "\033[0m\033[38;2;83;1;1mNo planets to destroy. :(\033[0m\n";
        }
        else {
            cout << "\n\033[0m\033[38;2;187;219;220mAvailable planets:\033[0m\033[38;2;73;149;142m\n";
            for (size_t i = 0; i < planets.size(); i++) {
                cout << i + 1 << ". " << planets[i].name << "\n";
            }

            int planetChoice;
            cout << "\n\033[0m\033[38;2;188;101;119mEnter planet number for destruction (0 to show mercy): \033[0m\033[38;2;185;43;61m";
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

                cout << "\033[0m\033[38;2;187;219;220mPlanet \033[0m\033[38;2;73;149;142m\"" << planetName << "\"\033[0m\033[38;2;187;219;220m and her satellites were destroyed by you. Data saved tho!.\033[0m\n";
            }
        }
    }
    else if (choice == 2) {
        if (satellites.empty()) {
            cout << "\033[38;2;83;1;1mNo satellites to destroy.\033[0m\n";
        }
        else {
            cout << "\n\033[38;2;187;219;220mAvailable sattelites:\033[0m\033[38;2;73;149;142m\n";
            for (size_t i = 0; i < satellites.size(); i++) {
                cout << i + 1 << ". " << satellites[i].name
                    << " (planet: " << satellites[i].planetName << ")\033[0m\n";
            }

            int satelliteChoice;
            cout << "\n\033[38;2;188;101;119mEnter satellite number for destruction (0 to show mercy): \033[0m\033[38;2;185;43;61m";
            cin >> satelliteChoice;

            if (satelliteChoice > 0 && satelliteChoice <= satellites.size()) {
                string satelliteName = satellites[satelliteChoice - 1].name;
                satellites.erase(satellites.begin() + satelliteChoice - 1);

                // Сохраняем изменения
                saveSatellites();

                cout << "\033[0m\033[38;2;187;219;220mSatellite \033[0m\033[38;2;73;149;142m\"" << satelliteName << "\"\033[0m\033[38;2;187;219;220m destroyed by you. \033[38;2;83;1;1mWhy?\033[0m\033[38;2;187;219;220m Data saved.\033[0m\n";
            }
        }
    }

    pressEnterToContinue();
}

// Меню ручного сохранения
void saveMenu() {
    clearScreen();
    cout << "\"\033[38;2;187;219;220m SOLAR TALES \033[0m\"\n\n";
    cout << "\033[38;2;187;219;220m=== Data saving ===\033[0m\n\n";

    cout << "\033[38;2;73;149;142m1 - \033[0m\033[38;2;187;219;220mSave all data\033[0m\n";
    cout << "\033[38;2;73;149;142m2 - \033[0m\033[38;2;187;219;220mSave only planets\033[0m\n";
    cout << "\033[38;2;73;149;142m3 - \033[0m\033[38;2;187;219;220mSave only satelliets\033[0m\n";
    cout << "\033[38;2;73;149;142m4 - \033[0m\033[38;2;187;219;220mBack\033[0m\n";
    cout << "\033[38;2;188;101;119mYour choice: \033[0m\033[38;2;185;43;61m";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        saveAllData();
        cout << "\033[0m\033[38;2;187;219;220mAll data saved!\033[0m\n";
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
        cout << "\033[38;2;83;1;1mWrong choice!\033[0m\n";
    }

    pressEnterToContinue();
}

// Остальные функции
void searchFilter() {
    clearScreen();
    cout << "\"\033[38;2;187;219;220m SOLAR TALES \033[0m\"\n\n";
    cout << "\033[38;2;187;219;220m=== Search/Filters ===\033[0m\n\n";

    cout << "\033[38;2;73;149;142m1 - \033[0m\033[38;2;187;219;220mSearch by name\033[0m\n";
    cout << "\033[38;2;73;149;142m2 - \033[0m\033[38;2;187;219;220mSearch by planet (for satellites)\033[0m\n";
    cout << "\033[38;2;73;149;142m3 - \033[0m\033[38;2;187;219;220mSave data (by hand)\033[0m\n";
    cout << "\033[38;2;73;149;142m4 - \033[0m\033[38;2;187;219;220mBack\033[0m\n";
    cout << "\033[38;2;188;101;119mYour choice: \033[0m\033[38;2;185;43;61m";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1: {
        // Поиск по имени
        if (planets.empty() && satellites.empty()) {
            cout << "\033[0m\033[38;2;73;149;142mData base is empty. :(\033[0m\n";
            pressEnterToContinue();
            return;
        }

        string searchName;
        cout << "\033[38;2;188;101;119mEnter name for the search: \033[0m\033[38;2;73;149;142m";
        cin.ignore();
        getline(cin, searchName);

        bool found = false;

        // Поиск среди планет
        for (const auto& planet : planets) {
            if (planet.name.find(searchName) != string::npos) {
                if (!found) {
                    cout << "\n\033[0m\033[38;2;187;219;220mResults:\033[0m\n";
                    cout << "\033[38;2;73;149;142m========================================\n";
                    found = true;
                }
                displayPlanet(planet, 1);
            }
        }

        // Поиск среди спутников
        for (const auto& satellite : satellites) {
            if (satellite.name.find(searchName) != string::npos) {
                if (!found) {
                    cout << "\n\033[0m\033[38;2;187;219;220mResults:\033[0m\n";
                    cout << "\033[38;2;73;149;142m========================================\n";
                    found = true;
                }
                displaySatellite(satellite, 1);
            }
        }

        if (!found) {
            cout << "\n\033[38;2;187;219;220mObjects named \033[0m\033[38;2;73;149;142m\"" << searchName << "\" \033[0m\033[38;2;187;219;220mnever existed yet.\033[0m\n";
        }
        pressEnterToContinue();
        break;
    }
    case 2:
        cout << "\n\033[38;2;73;149;142mWork in progress. :P\033[0m\n";
        pressEnterToContinue();
        break;
    case 3:
        saveMenu();
        break;
    case 4:
        break;
    default:
        cout << "\033[38;2;83;1;1mWrong choice!\033[0m\n";
        pressEnterToContinue();
    }
}

void showSummary() {
    clearScreen();
    cout << "\"\033[38;2;187;219;220m SOLAR TALES \033[0m\"\n\n";
    cout << "\033[38;2;187;219;220m=== Statistics ===\033[0m\n\n";

    cout << "\033[38;2;187;219;220mGeneral statistics:\033[0m\n";
    cout << "-----------------\n";
    cout << "\033[38;2;187;219;220mAmount of planets: " << planets.size() << "\033[0m\n";
    cout << "\033[38;2;187;219;220mAmount of satellites: " << satellites.size() << "\033[0m\n";
    cout << "\033[38;2;187;219;220mAmount of objects: " << planets.size() + satellites.size() << "\033[0m\n";

    cout << "\n\033[38;2;187;219;220mData files:\033[0m\n";
    cout << "-------------\n";
    cout << "\033[38;2;187;219;220mPlanets file: " << PLANETS_FILE << "\033[0m\n";
    cout << "\033[38;2;187;219;220mSitellites file: " << SATELLITES_FILE << "\033[0m\n";

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

        cout << "\n\033[38;2;187;219;220mStatistics on planets:\033[0m\n";
        cout << "----------------------\n";
        cout << "\033[38;2;187;219;220mAverage age: " << totalAge / planets.size() << " mill. of years\033[0m\n";
        cout << "\033[38;2;187;219;220mAverage temperature: " << totalTemp / planets.size() << " °C\033[0m\n";
        cout << "\033[38;2;187;219;220mOldest planet: " << oldestPlanet << " (" << oldestAge << " mill. of years)\033[0m\n";
        cout << "\033[38;2;187;219;220mHottest planet: " << hottestPlanet << " (" << hottestTemp << " °C)\033[0m\n";
    }

    pressEnterToContinue();
}

void sortData() {
    clearScreen();
    cout << "\"\033[0m\033[38;2;187;219;220m SOLAR TALES \033[0m\"\n\n";
    cout << "\033[38;2;187;219;220m=== Data Sorting ===\033[0m\n\n";

    cout << "\033[38;2;73;149;142m1 - \033[0m\033[38;2;187;219;220mSort planets by name\033[0m\n";
    cout << "\033[38;2;73;149;142m2 - \033[0m\033[38;2;187;219;220mSort planets by age\033[0m\n";
    cout << "\033[38;2;73;149;142m3 - \033[0m\033[38;2;187;219;220mSort planets by temperature\033[0m\n";
    cout << "\033[38;2;73;149;142m4 - \033[0m\033[38;2;187;219;220mSort satellites by name\033[0m\n";
    cout << "\033[38;2;73;149;142m5 - \033[0m\033[38;2;187;219;220mSort satellites by planets\033[0m\n";
    cout << "\033[38;2;73;149;142m6 - \033[0m\033[38;2;187;219;220mBack\033[0m\n";
    cout << "\033[38;2;188;101;119mYour choice: \033[0m\033[38;2;185;43;61m";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        sort(planets.begin(), planets.end(),
            [](const Planet& a, const Planet& b) { return a.name < b.name; });
        cout << "\033[0m\033[38;2;187;219;220mPlanets sorted by name.\033[0m\n";
        break;
    case 2:
        sort(planets.begin(), planets.end(),
            [](const Planet& a, const Planet& b) { return a.age < b.age; });
        cout << "\033[0m\033[38;2;187;219;220mPlanets sorted by age.\033[0m\n";
        break;
    case 3:
        sort(planets.begin(), planets.end(),
            [](const Planet& a, const Planet& b) { return a.temperature < b.temperature; });
        cout << "\033[0m\033[38;2;187;219;220mPlanets sorted by temperature.\033[0m\n";
        break;
    case 4:
        sort(satellites.begin(), satellites.end(),
            [](const Satellite& a, const Satellite& b) { return a.name < b.name; });
        cout << "\033[0m\033[38;2;187;219;220mSatellites sorted by name.\033[0m\n";
        break;
    case 5:
        sort(satellites.begin(), satellites.end(),
            [](const Satellite& a, const Satellite& b) { return a.planetName < b.planetName; });
        cout << "\033[0m\033[38;2;187;219;220mSatellites sorted by planet.\033[0m\n";
        break;
    case 6:
        return;
    default:
        cout << "\033[38;2;83;1;1mWrong choice. Try again.\033[0m\n";
    }

    pressEnterToContinue();
}

int main() {
    setlocale(LC_ALL, "RU");

    int choice;

    // Загружаем данные при запуске
    cout << "\033[38;2;73;149;142mLoading resources!\033[0m\n";
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
            cout << "\033[38;2;187;219;220mData saved in files:\033[0m\n";
            cout << "\033[38;2;187;219;220m1. \033[0m\033[38;2;73;149;142m" << PLANETS_FILE << "\033[38;2;187;219;220m (planets)\033[0m\n";
            cout << "\033[38;2;187;219;220m2. \033[0m\033[38;2;73;149;142m" << SATELLITES_FILE << "\033[38;2;187;219;220m (satellites)\033[0m\n";
            cout << "\n\033[38;2;187;219;220mMay the great cosmos guide you. See you tommorow!\033[0m\n";
            break;
        default:
            cout << "\033[38;2;73;149;142mSeems like you'va made a \033[38;2;83;1;1mmistake.\033[0m Try again.\033[0m\n";
            pressEnterToContinue();
        }
    } while (choice != 7);

    return 0;
}

