#include <iostream>
#include <unordered_map>
#include <fstream>
#include "expression.hpp"

int main() {
    setlocale(LC_ALL, "ru");
    string path = "test.cpp"; // файл, который нужно открыть
    string input; // здесь будет содержимое файла
    ifstream fin;
    fin.open(path);

    if (!fin.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
    }
    else {
        cout << "Файл открыт!" << endl;
        char ch;
        while (fin.get(ch)) {
            input += ch; // добавляем символ к строке
        }
        fin.close();
    }

    Expression expr(input);
    

    return 0;
}