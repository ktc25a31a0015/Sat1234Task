#include <iostream>

#include "input.h"
#include "judge.h"

int main()
{
    int randInt = raffle();

    while (true) {
        int input = inputNumber();

        ResultType result = compare(randInt, input);
        dispResult(result);

        if (result == Clear) break;
    }

    return 0;
}