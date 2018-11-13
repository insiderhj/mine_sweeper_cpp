#pragma once

#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

#define ROW_MARGIN 3
#define COL_MARGIN 1

/*
 * mine_sweeper_class.cpp
 */
template<typename T>
class Map
{
protected:
	T * * _map;
	int _width;
	int _height;

public:
	Map(void) : _map(NULL), _width(0), _height(0) {}
	Map(int, int);
	~Map(void);

	int getWidth(void) const { return _width; }
	int getHeight(void) const { return _height; }
};

class MineMap : public Map<bool>
{
private:
	int mine_count;
public:
	MineMap(void) : mine_count(0) {}
	MineMap(int, int, int);
	~MineMap(void) {}

	void moveMine(int, int);
	int getMineCount(void) const { return mine_count; }
	bool isMine(int x, int y) const { return _map[y][x]; }
};

class NumberMap : public Map<int>
{
private:
	int getMineCount(int, int, MineMap*) const;
public:
	NumberMap(void) {}
	NumberMap(MineMap*);
	~NumberMap(void) {}

	int getxy(int x, int y) const { return _map[y][x]; }
};

class StatusMap : public Map<char>
{
public:
	StatusMap(void) {}
	StatusMap(NumberMap*);
	~StatusMap(void) {}

	char getxy(int x, int y) const { return _map[y][x]; }
	void setxy(int x, int y, char input) { _map[y][x] = input; }
	std::string getInfo(void) const;
};

class MineSweeper
{
private:
	MineMap * mine_map;
	NumberMap* number_map;
	StatusMap* status_map;
	int _width, _height;
	bool is_alive, win;
	int found_number, found_mine;

	void seek(int, int);
public:
	MineSweeper(void) : mine_map(NULL), number_map(NULL), status_map(NULL), _width(0), _height(0), is_alive(false), win(false), found_number(0), found_mine(0) {}
	MineSweeper(int, int, int);
	~MineSweeper(void);

	void moveMine(int, int);
	void inputZ(int, int);
	void inputX(int, int);
	
	char getxy(int x, int y) const { return status_map->getxy(x, y); }
	int getRemainMine(void) const { return mine_map->getMineCount() - found_mine; }
	bool isMine(int x, int y) const { return mine_map->isMine(x, y); }
	bool isAlive(void) const { return is_alive; }
	bool hasWon(void) const { return win; }

	void showMap(void) const { std::cout << status_map->getInfo(); }
};


/*
 * mine_sweeper_screen.cpp
 */
int pickMenu(int, const std::string&, std::string*);

int* setDifficulty(void);
bool win(void);
bool lose(void);
void howToPlay(void);

/*
 * mine_sweeper_main.cpp
 */

void gotoxy(int, int);