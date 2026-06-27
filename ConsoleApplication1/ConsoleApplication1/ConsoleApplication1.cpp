#include <iostream>

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

class RandDigits {
public:
    RandDigits() {
        for (int i = 0; i < 4; i++) {
            digits[i] = rand() % 10;
        }
    }

public:
	int digits[4] = {};
};

class InputDigits {
public:
	int digits[4] = {};
};

struct Result {
	bool success;
	int hit;
	int blow;
};

class Compare {
public:
	Compare(const RandDigits& rand, const InputDigits& input) {
		int checkedList[10] = {};
		int checkedCount = 0;

		for (int r = 0; r < 4; r++) {
			for (int v = 0; v < 4; v++) {
				if (rand.digits[r] == input.digits[v]) {
					bool checked = false;

					for (int i = 0; i < checkedCount; i++) {
						if (checkedList[i] == rand.digits[r]) {
							checked = true;

							break;
						}
					}

					if (checked) continue;

					checkedList[checkedCount] = rand.digits[r];
					checkedCount++;

					if (r == v) {
						result.hit++;
					}
					else {
						result.blow++;
					}
				}
			}
		}

		result.success = result.hit == 4;
	};

public:
	Result result = { false, 0, 0 };
};

class Disp {
public:
	Disp(const RandDigits& rands, Result& result) {
		if (result.success) {
			std::cout << "成功！！\n";
		}
		else {
			std::cout << "失敗 (" << rands.digits[0] << rands.digits[1] << rands.digits[2] << rands.digits[3] << ")\n";
			std::cout << "ヒット : " << result.hit << " 個\n";
			std::cout << "ブロー : " << result.blow << " 個\n";
		}
	};
};

int main()
{
    srand((unsigned int)time(NULL));
	
	int digit = 0;
	int count = 0;

	std::string input;

	while (true) {
		count++;

		RandDigits rands;
		InputDigits inputs;

		for (int i = 0; i < 4; i++) {
			while (true) {
				std::cout << i + 1 << "桁目の入力 : ";
				std::cin >> input;

				if (!isDigit(input)) {
					clearInput();

					continue;
				}

				try {
					inputs.digits[i] = input[0] - '0';
				}
				catch (...) {
					continue;
				}

				break;
			}
		}

		Compare compare(rands, inputs);

		Disp disp(rands, compare.result);

		if (compare.result.success) break;
	}

    std::cout << count << "回で" << "ゲームクリア！\n";
}