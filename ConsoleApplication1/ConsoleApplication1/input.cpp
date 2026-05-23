#include <iostream>
#include <string>

int raffle() {
    // srand()シード変更
    // time(NULL)で時間をシードに
    // rand() % (最大値 + 最小値 + 1) + 最小値

    srand((unsigned int)time(NULL));

    return rand() % 10;
}

bool isDigit(std::string s) {
    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }

    return !s.empty();
}

void clearInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int inputNumber() {
    std::string input;
    int value;

    while (true) {
        std::cout << "0 - 9 の整数を入力 : " << std::flush;
        std::cin >> input;

        if (!isDigit(input)) {
            clearInput();

            continue;
        }

        try {
            value = std::stoi(input);
        }
        catch (...) {
            continue;
        }

        return value;
    }
}