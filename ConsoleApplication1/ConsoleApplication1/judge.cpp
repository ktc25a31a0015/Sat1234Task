#include "judge.h"
#include <iostream>

ResultType compare(int random, int input) {
    if (input == random) {
        return Clear;
    }
    else {
        if (input > random) {
            return More;
        }
        else {
            return Less;
        }
    }
}

void dispResult(ResultType result) {
    switch (result)
    {
    case Clear:
        std::cout << "ゲームクリア！\n";

        break;

    case Less:
        std::cout << "小さい\n";

        break;

    case More:
        std::cout << "大きい\n";

        break;

    default:
        break;
    }
}