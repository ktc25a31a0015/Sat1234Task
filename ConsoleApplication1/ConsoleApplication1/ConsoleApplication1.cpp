#include <stdio.h>
#include <time.h>

int main()
{
	int t = (int)time(nullptr);
	int answer = t % 10;

	int rank = 0;

	bool play = true;

	while (play) {
		printf("数値を入力して Enter\n");
		int input;
		scanf_s("%d", &input);

		if (answer == input) {
			rank = 2;

			printf("一致！\n");
		}
		else {
			if (answer < input) {
				printf("大きい！\n");
			}
			else {
				printf("小さい！\n");
			}

			int sub = answer - input;

			if (-3 < sub && sub < 3) {
				rank = 1;

				printf("惜しい！\n");
			}
		}

		switch (rank) {
		case 2:
			play = false;

			printf("ランクS\n");

			break;

		case 1:
			printf("ランクA\n");

			break;

		default:
			printf("ランクB\n");

			break;
		}
	}

	return 0;
}