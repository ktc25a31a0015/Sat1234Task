#pragma once

enum ResultType { Clear, Less, More };

ResultType compare(int random, int input);

void dispResult(ResultType result);