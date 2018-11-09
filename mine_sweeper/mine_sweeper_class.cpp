#include "mine_sweeper.h"

using namespace std;

template<typename T>
Map<T>::Map() {
	_map = NULL, _width = 0, _height = 0;
}

template<typename T>
Map<T>::Map(int width, int height) {
	_width = width, _height = height;

	_map = new T*[_height]; 
	for (int i = 0; i < _height; ++i) {
		_map[i] = new T[_width];
	}
}

template<typename T>
Map<T>::~Map() {
	for (int i = 0; i < _height; ++i) {
		delete[] _map[i];
	}
	delete[] _map;
}

template<typename T>
int Map<T>::getWidth() const {
	return _width;
}

template<typename T>
int Map<T>::getHeight() const {
	return _height;
}

/*
 * class MineMap : public Map<bool>
 */
MineMap::MineMap() {
	mine_count = 0;
}

MineMap::MineMap(int width, int height, int mine) : Map(width, height) {
	mine_count = mine;
	srand(time(NULL));
	int x, y;

	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			_map[i][j] = false;
		}
	}

	for (int i = 0; i < mine_count; ++i) {
		x = rand() % _width;
		y = rand() % _height;

		if (_map[y][x]) --i;
		_map[y][x] = true;
	}
}

MineMap::~MineMap() {}

void MineMap::moveMine(int x, int y) {
	_map[y][x] = false;

	int curr_x, curr_y;
	while (true)
	{
		curr_x = rand() % _width;
		curr_y = rand() % _height;

		if (curr_x == x && curr_y == y) continue;
		if (!_map[curr_y][curr_x]) {
			_map[curr_y][curr_x] = true;
			break;
		}
	}
}

int MineMap::getMineCount() const {
	return mine_count;
}

bool MineMap::isMine(int x, int y) const {
	return _map[y][x];
}

/*
 * class NumberMap : public Map<int>
 */
int NumberMap::getMineCount(int x, int y, MineMap* mine_map) const {
	int mine_count = 0;
	for (int i = y - 1; i <= y + 1; ++i) {
		if (i < 0 || i >= _height) continue;
		for (int j = x - 1; j <= x + 1; ++j) {
			if (j < 0 || j >= _width) continue;
			if (mine_map->isMine(j, i)) ++mine_count;
		}
	}
	return mine_count;
}

NumberMap::NumberMap() {}

NumberMap::NumberMap(MineMap* mine_map) : Map(mine_map->getWidth(), mine_map->getHeight()) {
	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			if (mine_map->isMine(j, i)) _map[i][j] = -1;
			else _map[i][j] = getMineCount(j, i, mine_map);
		}
	}
}

NumberMap::~NumberMap() {}

int NumberMap::getxy(int x, int y) const {
	return _map[y][x];
}

/*
 * class StatusMap : public Map<char>
 */
StatusMap::StatusMap() {}

StatusMap::StatusMap(NumberMap* number_map) : Map(number_map->getWidth(), number_map->getHeight()) {
	for (int i = 0; i < _height; ++i) {
		for (int j = 0; j < _width; ++j) {
			_map[i][j] = '.';
		}
	}
}

StatusMap::~StatusMap() {}

char StatusMap::getxy(int x, int y) const {
	return _map[y][x];
}

void StatusMap::setxy(int x, int y, char input) {
	_map[y][x] = input;
}

string StatusMap::getInfo() const {
	string result = " ";

	for (int i = 0; i <= _width; ++i) {
		result += "__";
	}
	result += '\n';

	for (int i = 0; i < _height; ++i) {
		result += " | ";
		for (int j = 0; j < _width; ++j) {
			result += _map[i][j];
			result += ' ';
		}
		result += "|\n";
	}
	
	result += ' ';
	for (int i = 0; i <= _width; ++i) {
		result += "--";
	}

	return result;
}

/*
 * class MineSweeper
 */
void MineSweeper::seek(int x, int y) {
	for (int i = y - 1; i <= y + 1; ++i) {
		if (i < 0 || i >= _height) continue;
		for (int j = x - 1; j <= x + 1; ++j) {
			if (j < 0 || j >= _width) continue;
			if (status_map->getxy(j, i) != '.') continue;
			switch (number_map->getxy(j, i)) {
			case -1:
				is_alive = false;
				return;
			case 0:
				gotoxy(ROW_MARGIN + j * 2, COL_MARGIN + i);;
				cout << ' ';
				status_map->setxy(j, i, ' ');
				++found_number;
				seek(j, i);
				break;
			default:
				gotoxy(ROW_MARGIN + j * 2, COL_MARGIN + i);;
				cout << number_map->getxy(j, i);
				status_map->setxy(j, i, number_map->getxy(j, i) + '0');
				++found_number;
			}
		}
	}
}

MineSweeper::MineSweeper() {
	mine_map = NULL, number_map = NULL, status_map = NULL, _width = 0, _height = 0, found_number = 0, found_mine = 0, is_alive = false, win = false;
}

MineSweeper::MineSweeper(int width, int height, int mine) {
	mine_map = new MineMap(width, height, mine);
	number_map = new NumberMap(mine_map);
	status_map = new StatusMap(number_map);
	_width = width, _height = height;
	is_alive = true, win = false;
	found_number = 0, found_mine = 0;
}

MineSweeper::~MineSweeper() {
	delete mine_map;
	delete number_map;
	delete status_map;
}

void MineSweeper::moveMine(int x, int y) {
	delete number_map;
	delete status_map;

	mine_map->moveMine(x, y);
	number_map = new NumberMap(mine_map);
	status_map = new StatusMap(number_map);
}

void MineSweeper::inputZ(int x, int y) {
	switch (status_map->getxy(x, y)) {
	case '*':
	case '?':
	case ' ':
		return;
	case '.':
		switch (number_map->getxy(x, y)) {
		case -1:
			is_alive = false;
			return;
		case 0:
			gotoxy(ROW_MARGIN + x * 2, COL_MARGIN + y);;
			cout << ' ';
			status_map->setxy(x, y, ' ');
			++found_number;
			seek(x, y);
			break;
		default:
			gotoxy(ROW_MARGIN + x * 2, COL_MARGIN + y);;
			cout << number_map->getxy(x, y);
			status_map->setxy(x, y, number_map->getxy(x, y) + '0');
			++found_number;
		}
		break;
	default:
		int found_around = 0;
		for (int i = y - 1; i <= y + 1; ++i) {
			if (i < 0 || i >= _height) continue;
			for (int j = x - 1; j <= x + 1; ++j) {
				if (j < 0 || j >= _width) continue;
				if (status_map->getxy(j, i) == '*') ++found_around;
			}
		}
		if (found_around == number_map->getxy(x, y)) seek(x, y);
	}
	if (_width * _height - mine_map->getMineCount() == found_number) win = true;
}

void MineSweeper::inputX(int x, int y) {
	char pos_status = status_map->getxy(x, y);
	switch (pos_status) {
	case '.':
		status_map->setxy(x, y, '*');
		++found_mine;
		break;
	case '*':
		status_map->setxy(x, y, '?');
		--found_mine;
		break;
	case '?':
		status_map->setxy(x, y, '.');
		break;
	}

	gotoxy(ROW_MARGIN + x * 2, COL_MARGIN + y);;
	cout << status_map->getxy(x, y);
}

char MineSweeper::getxy(int x, int y) const {
	return status_map->getxy(x, y);
}

int MineSweeper::getRemainMine() const {
	return mine_map->getMineCount() - found_mine;
}

bool MineSweeper::isMine(int x, int y) const {
	return mine_map->isMine(x, y);
}

bool MineSweeper::isAlive() const {
	return is_alive;
}

bool MineSweeper::hasWon() const {
	return win;
}

void MineSweeper::showMap() const {
	cout << status_map->getInfo() << endl;
}
