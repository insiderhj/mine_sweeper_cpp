#include "mine_sweeper.h"

using namespace std;

int main() {
	int* map_option;
	int input;
	int xpos, ypos;
	bool first_turn;

	while (true) {
		map_option = setDifficulty();

		MineSweeper mine_sweeper(map_option[0], map_option[1], map_option[2]);
		xpos = 0, ypos = 0;
		first_turn = true;

		system("CLS");
		mine_sweeper.showMap();
		gotoxy(0, map_option[1] + 1 + COL_MARGIN);
		cout << "remain mine: " << mine_sweeper.getRemainMine() << " ";

		gotoxy(xpos * 2 + ROW_MARGIN, ypos + COL_MARGIN);

		do {
			input = _getch();
			switch (input) {
			case 72:
				--ypos;
				break;
			case 75:
				--xpos;
				break;
			case 77:
				++xpos;
				break;
			case 80:
				++ypos;
				break;
			case 120:
				mine_sweeper.inputX(xpos, ypos);
				gotoxy(0, map_option[1] + 1 + COL_MARGIN);
				cout << "remain mine: " << mine_sweeper.getRemainMine() << " ";
				break;
			case 122:
				if (first_turn && mine_sweeper.getxy(xpos, ypos) == '.') {
					first_turn = false;
					if (mine_sweeper.isMine(xpos, ypos)) mine_sweeper.moveMine(xpos, ypos);
				}
				mine_sweeper.inputZ(xpos, ypos);
				break;
			}

			if (xpos < 0) xpos = map_option[0] - 1;
			if (xpos == map_option[0]) xpos = 0;
			if (ypos < 0) ypos = map_option[1] - 1;
			if (ypos == map_option[1]) ypos = 0;

			gotoxy(ROW_MARGIN + xpos * 2, COL_MARGIN + ypos);
		} while (mine_sweeper.isAlive() && !(mine_sweeper.hasWon()));
		if (mine_sweeper.isAlive()) {
			if (!win()) return 0;
		}
		else {
			if (!lose()) return 0;
		}

		delete[] map_option;
	}

	return 0;
}

void gotoxy(int x, int y) {
	COORD pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
