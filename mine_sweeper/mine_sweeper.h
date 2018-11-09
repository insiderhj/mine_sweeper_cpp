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
	Map(void);
	Map(int, int);
	~Map(void);

	int getWidth(void) const;
	int getHeight(void) const;
};

class MineMap : public Map<bool>
{
private:
	int mine_count;
public:
	MineMap();
	MineMap(int, int, int);
	~MineMap();

	void moveMine(int, int);
	int getMineCount(void) const;
	bool isMine(int, int) const;
};

class NumberMap : public Map<int>
{
private:
	int getMineCount(int, int, MineMap*) const;
public:
	NumberMap(void);
	NumberMap(MineMap*);
	~NumberMap(void);

	int getxy(int, int) const;
};

class StatusMap : public Map<char>
{
public:
	StatusMap(void);
	StatusMap(NumberMap*);
	~StatusMap(void);

	char getxy(int, int) const;
	void setxy(int, int, char);
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
	MineSweeper(void);
	MineSweeper(int, int, int);
	~MineSweeper(void);

	void moveMine(int, int);
	void inputZ(int, int);
	void inputX(int, int);
	char getxy(int, int) const;
	int getRemainMine(void) const;
	bool isMine(int, int) const;
	bool isAlive(void) const;
	bool hasWon(void) const;

	void showMap(void) const;
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