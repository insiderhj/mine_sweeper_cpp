#include "mine_sweeper.h"

using namespace std;

int countEnter(const string& str) {
	int count = 0;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '\n') count++;
	}
	return count;
}

int pickMenu(int menu_size, const string& menu_title, string* menu) {
	int now = 0;
	int input;
	int enter;
	system("CLS");
	gotoxy(0, 0);

	cout << menu_title << endl << endl << endl;
	enter = countEnter(menu_title);

	for (int i = 0; i < menu_size; i++) {
		cout << menu[i] << endl << endl;
	}

	gotoxy(0, 3 + enter);
	cout << " > " << menu[0];

	while (true) {
		input = _getch();

		if (input == 72 || input == 80) {
			gotoxy(0, now * 2 + 3 + enter);
			cout << menu[now] << "   ";

			if (input == 72) --now;
			else ++now;

			if (now < 0) now = menu_size - 1;
			if (now == menu_size) now = 0;

			gotoxy(0, now * 2 + 3 + enter);
			cout << " > " << menu[now];
		}
		if (input == 13) break;
	}

	return now;
}

int* setDifficulty() {
	int* result = new int[3];
	int now = 0;
	int input;
	system("CLS");
	gotoxy(0, 0);

	int menu_size = 5;
	string menu_title = "set difficulty";
	string* menu = new string[menu_size];
	menu[0] = "easy(9 * 9)";
	menu[1] = "normal(16 * 16)";
	menu[2] = "hard(30 * 16)";
	menu[3] = "joo moon jae jak";
	menu[4] = "how to play";

	switch (pickMenu(menu_size, menu_title, menu)) {
	case 0:
		result[0] = 9, result[1] = 9, result[2] = 10;
		break;
	case 1:
		result[0] = 16, result[1] = 16, result[2] = 40;
		break;
	case 2:
		result[0] = 30, result[1] = 16, result[2] = 99;
		break;
	case 3:
		system("CLS");
		gotoxy(0, 0);
		while (true) {
			string map_option[3];
			bool is_all_int = true;
			cout << "width(1 ~ 50): ";
			cin >> map_option[0];
			cout << "height(1 ~ 30): ";
			cin >> map_option[1];
			cout << "mine: ";
			cin >> map_option[2];

			for (int i = 0; i < 3; i++) {
				result[i] = atoi(map_option[i].c_str());
				if (to_string(result[i]) != map_option[i]) is_all_int = false;
			}

			if (result[0] * result[1] < result[2] || result[0] < 1 || result[0] > 50 || result[1] < 1 || result[1] > 30 || !is_all_int) {
				system("CLS");
				gotoxy(0, 0);
				cout << "jang nan ha ni?" << endl;
			}
			else break;
		}
		break;
	case 4:
		howToPlay();
		int* tmp = setDifficulty();
		result[0] = tmp[0];
		result[1] = tmp[1];
		result[2] = tmp[2];
		delete[] tmp;
		break;
	}
	delete[] menu;

	return result;
}

bool win() {
	int menu_size = 2;
	string menu_title = ":) you win!";
	string* menu = new string[menu_size];
	menu[0] = "go to main menu";
	menu[1] = "fuck you";

	if (pickMenu(menu_size, menu_title, menu) == 0) {
		delete[] menu;
		return true;
	}
	delete[] menu;
	return false;
}

bool lose() {
	int menu_size = 2;
	string menu_title = ":( you lose";
	string* menu = new string[menu_size];
	menu[0] = "go to main menu";
	menu[1] = "fuck you";

	if (pickMenu(menu_size, menu_title, menu) == 0) {
		delete[] menu;
		return true;
	}
	delete[] menu;
	return false;
}

void howToPlay() {
	int menu_size = 1;
	string menu_title = "How to play";
	menu_title += "\n\n\nZ: number";
	menu_title += "\n\nX: mine";
	menu_title += "\n\nif you press Z with the cursor on a number,";
	menu_title += "\nit works same as a double click.";
	menu_title += "\n\nif you press X with the cursor on a mine,";
	menu_title += "\nthe mine turns into a question mark.";
	menu_title += "\nif you press X one more time,";
	menu_title += "\nthe question mark turns into a dot again.";
	string* menu = new string[menu_size];
	menu[0] = "back to main menu";

	pickMenu(menu_size, menu_title, menu);
	delete[] menu;
}