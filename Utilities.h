#pragma once

#include <fstream>
#include <string>
#include <vector>

using namespace std;
// Глобальные функции для работы с файлами (сериализация)
void saveString(ofstream& file, const string& str);
string loadString(ifstream& file);

// Функции для задержки и анимации
void sleep_ms(int ms);
void loaderSequence(const vector<string>& messages, int totalSteps = 40, int delayMs = 60);

// Функции для работы с консолью
void clearScreen();
void pressEnterToContinue();

