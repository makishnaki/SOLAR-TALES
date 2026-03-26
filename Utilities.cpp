#include "Utilities.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <limits>

using namespace std;

// Сохранение строки в бинарный файл
void saveString(ofstream& file, const string& str) {
    size_t length = str.size();
    file.write((char*)&length, sizeof(length));
    file.write(str.c_str(), length);
}

// Загрузка строки из бинарного файла
string loadString(ifstream& file) {
    size_t length;
    file.read((char*)&length, sizeof(length));
    char* buffer = new char[length + 1];
    file.read(buffer, length);
    buffer[length] = '\0';
    string result(buffer);
    delete[] buffer;
    return result;
}

// Задержка выполнения
void sleep_ms(int ms) {
    this_thread::sleep_for(chrono::milliseconds(ms));
}

// Анимация загрузки с прогресс-баром
void loaderSequence(const vector<string>& messages, int totalSteps, int delayMs) {
    for (size_t i = 0; i < messages.size(); ++i) {
        for (int step = 0; step <= totalSteps; ++step) {
            int progress = static_cast<int>((step * 100) / totalSteps);
            cout << "\033[38;2;220;40;40mLoading in progress: " << progress << "%\n";
            cout << messages[i] << "\n";
            cout << "[";
            int filled = (step * 20) / totalSteps;
            for (int j = 0; j < 20; ++j) {
                cout << (j < filled ? '=' : ' ');
            }
            cout << "]\033[0m\n";
            sleep_ms(delayMs);
        }
    }
}

// Очистка экрана (кроссплатформенная)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Ожидание нажатия Enter
void pressEnterToContinue() {
    cout << "\n\033[38;2;220;40;40mPress Enter to continue...\033[0m";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}