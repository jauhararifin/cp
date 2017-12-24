#include <bits/stdc++.h>

using namespace std;

char field[9][10];
int a,b;

int main() {
	for (int i = 0; i < 9; i++)
		scanf("%s", field[i]), scanf("%s", field[i] + 3), scanf("%s", field[i] + 6);
	scanf("%d%d", &a, &b); a = (a-1)%3; b = (b-1)%3;

	bool isful = 1;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (field[a*3+i][b*3+j] == '.')
				isful = 0, field[a*3+i][b*3+j] = '!';

	if (isful)
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				if (field[i][j] == '.')
					field[i][j] = '!';

	for (int i = 0; i < 9; i++) {
		printf("%c%c%c %c%c%c %c%c%c\n", field[i][0], field[i][1], field[i][2], field[i][3], field[i][4], field[i][5], field[i][6], field[i][7], field[i][8]);
		if (i == 2 || i == 5) printf("\n");
	}

	return 0;
}