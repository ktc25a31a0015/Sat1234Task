#include <iostream>

#include "input.h"
#include "judge.h"

int main()
{
    int randInt;
    raffle(&randInt);

    while (true) {
        int input;
        inputNumber(input);

        ResultType result = compare(randInt, input);
        dispResult(result);

        if (result == Clear) break;
    }

    return 0;
}