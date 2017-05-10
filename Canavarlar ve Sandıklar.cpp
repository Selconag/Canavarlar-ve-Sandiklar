// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <ctime>
#include <windows.h>
#include <cwchar>
using namespace std;
#define UP 80 //Keyboad_DOWN
#define DOWN 72 //Keyboard_UP
#define RIGHT 77
#define LEFT 75
int blackhole = 0;
bool showUnknownObj = 0;
bool alwaysShowMap = 1;
bool isBot = 1;
bool isBotAlive = 1;
bool isPlayerinRoomO = 1;
int x = 0, y = 0, moves = 0, kills = 0, foundcase = 0, x_bot = 5, y_bot = 6;
int size = 17;
int Map_1[17][17] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,0,0,0,0,0,0,0,0,0,0,0,0,0,5,1,20,0,1,1,1,0,1,1,1,1,1,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,1,
3,1,15,1,1,0,1,0,1,0,1,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,5,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,12,1,0,1,1,0,5,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,1,1,
1,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,3,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,0,1,1,1,1,0,1,1,0,1,1,12,1,0,1,0,0,0,0,1,5,1,15,1,
1,0,0,1,1,1,0,1,1,1,1,0,1,0,1,1,1,1,1,0,0,5,1,1,0,0,0,1,0,0,0,5,1,1,1,1,0,1,1,1,5,1,1,0,1,1,0,1,1,1,1,1,5,0,0,0,0,0,0,0,0,0,0,0,0,0,5,1,
1,1,1,1,1,1,1,1,1,21,1,1,1,1,1,1,1 };
void findAndSetStartPoint() {
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (Map_1[i][j] == 20) {
				x = i;
				y = j;
				break;
			}
		}
	}
}
void drawMap(int a, int o, int bot_a, int bot_o) {
	system("cls"); // Windows (OD)
	int bot_backup = 0;
	if (isBotAlive) {
		bot_backup = Map_1[bot_a][bot_o];
		Map_1[bot_a][bot_o] = 7;
	}
	int backup = Map_1[a][o];
	Map_1[a][o] = 8;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			switch (Map_1[i][j]) {
			case 0:
				printf(" ");
				break;
			case 1:
				printf(u8"█");
				break;
			case 3:
				printf(u8"⌂");
				break;
				//2
			case 5:
				if (showUnknownObj) {
					printf(u8"₢");
				}
				else {
					printf(u8"�");
				}
				break;
			case 7:
				printf(u8"☻");
				break;
			case 8:
				printf(u8"☺");
				break;
			case 9:
				printf(u8"▓");
				break;
			case 12:
				if (showUnknownObj) {
					printf(u8"₪");
				}
				else {
					printf(u8"�");
				}
				break;
			case 15:
				printf(u8"☼");
				break;
			case 20:
				printf(u8"S");
				break;
			case 21:
				printf(u8"E");
				break;
			default:
				printf(" %d ", Map_1[i][j]);
				break;
			}
		}
		printf("\n");
	}
	Map_1[bot_a][bot_o] = bot_backup;
	Map_1[a][o] = backup;
}
int calcPoint(char* isim, bool isOuterCall) {
	int point = 2 + foundcase + kills;
	if (blackhole > 0 && isOuterCall) {
		if (blackhole == 2) {
			printf(u8"\nCanavar seni yedi.");
		}
		if (blackhole == 1) {
			printf(u8"\nKara deliğe yakalandın!");
		}
		if (blackhole == 3) {
			printf(u8"\nBaşarıyla çıkışa ulaştın.");
		}
		else {
			if (moves <= 50) {
				point = point + 5;
			}
			else if (moves <= 70) {
				point = point + 3;
			}
			else if (moves <= 100) {
				point = point + 1;
			}
		}
		printf(u8"\nOyun bitti\n%s, işte skorun: %d", isim, point);
	}
	return point;
	system("pause");
}
bool confirm() {
	while (1) {
		char cevap = _getch();
		if (cevap == '.') {
			return 1;
		}
		else if (cevap == ',') {
			return 0;
		}
		else {
			printf(u8"\nAnlamadım. Bir daha gir. (.(E)/,(H)): ");
		}
	}
}
void readsimulatearrowkeys(char direction) {
	isBot = 1;
	char source;
	if (direction == (int)1) {
		_getch();
		source = _getch();
	}
	else {
		source = direction;
	}
	switch (source) {
	case UP:
		x++;
		break;
	case DOWN:
		x--;
		break;
	case RIGHT:
		y++;
		break;
	case LEFT:
		y--;
		break;
	default:
		break;
	}
}
int isOKToGo(int a, int o) {
	int curr_location = Map_1[a][o];
	int curr_up = Map_1[a + 1][o];
	int curr_down = Map_1[a - 1][o];
	int curr_right = Map_1[a][o + 1];
	int curr_left = Map_1[a][o - 1];
	showUnknownObj = 0;
	bool spec_up = (curr_location != 1 && (curr_up == 12 || curr_up == 5));
	bool spec_down = (curr_location != 1 && (curr_down == 12 || curr_down == 5));
	bool spec_right = (curr_location != 1 && (curr_right == 12 || curr_right == 5));
	bool spec_left = (curr_location != 1 && (curr_left == 12 || curr_left == 5));
	if (curr_location == 7) isBotAlive = 0;
	if (((spec_left || spec_right || spec_up || spec_down) & isPlayerinRoomO) & isBot) {
		printf(u8"\nBir anda ");
		if (spec_up)printf(u8"aşağıda");
		if (spec_down)printf(u8"yukarıda");
		if (spec_right)printf(u8"sağında");
		if (spec_left)printf(u8"solunda");
		printf(u8" güzel gorünümlü bir oda olduğunu fark ediyorsun, girmek istiyormusun? (.(E)/,(H)): ");
		if (confirm()) {
			if (spec_up)readsimulatearrowkeys(UP);
			if (spec_down)readsimulatearrowkeys(DOWN);
			if (spec_right)readsimulatearrowkeys(RIGHT);
			if (spec_left)readsimulatearrowkeys(LEFT);
			moves++;
			isPlayerinRoomO = 0;
			isOKToGo(x, y);
		}
	}
	else {
		isPlayerinRoomO = 1;
	}
	if (curr_location == 1 || a >= size || a < 0 || o >= size || o < 0) {
		return 1;
	}
	else if (curr_location == 12) {
		blackhole = 1;
		return 0;
	}
	else if (curr_location == 21) {
		blackhole = 3;
		return 0;
	}
	else if (curr_location == 15) {
		showUnknownObj = 1;
		drawMap(a, o, x_bot, y_bot);
		return 0;
	}
	else if (curr_location == 9 & isBot) {
		printf(u8"\nBir çıkmaza girdiniz geri dönmenizi tavsiye ederim"); //Mesaj ekrandan hemen kayboluyor
		return 1;
	}
	else if (curr_location == 5 & isBot) {
		if (5 <= calcPoint("OuterCall", 0)) {
			kills++;
			Map_1[a][o] = 0;
		}
		else {
			blackhole = 2;
		}
		return 0;
	}
	else if (curr_location == 3) {
		Map_1[a][o] = 0;
		if (isBot) {
			foundcase = foundcase + 3;
			moves++;
		}
		return 0;
	}
	else if (isBot) {
		moves++;
		return 0;
	}
	else {
		return 0;
	}
}
void startGame(char* name) {
	while (blackhole == 0) {
		int x_wall = x;
		int y_wall = y;
		int y_wallb = y_bot;
		int x_wallb = x_bot;
		int moves_wall = moves;
		if (isBotAlive) {
			isBot = 0;
			int x_m = x_bot;
			int x_p = x_bot;
			int y_m = y_bot;
			int y_p = y_bot;
			int x_md = -1;
			int x_pd = -1;
			int y_md = -1;
			int y_pd = -1;
			bool one_out = 1;
			bool two_out = 1;
			bool three_out = 1;
			bool four_out = 1;
			int last_out;
			while (one_out | two_out | three_out | four_out) {
				if (!(Map_1[x_m][y_bot] == 1) & one_out) {
					x_md++;
					x_m--;
				}
				else {
					one_out = 0;
				}
				if (!(Map_1[x_p][y_bot] == 1) & two_out) {
					x_pd++;
					x_p++;
				}
				else {
					two_out = 0;
				}
				if (!(Map_1[x_bot][y_m] == 1) & three_out) {
					y_md++;
					y_m--;
				}
				else {
					three_out = 0;
				}
				if (!(Map_1[x_bot][y_p] == 1) & four_out) {
					y_pd++;
					y_p++;
				}
				else {
					four_out = 0;
				}
			}
			bool edit = 1;
			if ((x_md * 3) > (y_md + x_pd + y_pd) &edit) { x_bot--; edit = 0; }
			if ((x_pd * 3) > (y_md + x_md + y_pd) &edit) { x_bot++; edit = 0; }
			if ((y_md * 3) > (x_md + x_pd + y_pd) &edit) { y_bot--; edit = 0; }
			if ((y_pd * 3) > (y_md + x_pd + x_md) &edit) { y_bot++; edit = 0; }
			printf(u8" | Bot yaşıyor!\n");
		}
		else {
			printf(u8" | Bot öldü!");
			Map_1[x_bot][y_bot] = 0;
		}
		readsimulatearrowkeys(1);
		if (isOKToGo(x, y)) {
			x = x_wall;
			y = y_wall;
			moves = moves_wall;
		}
		if (alwaysShowMap) drawMap(x, y, x_bot, y_bot);
		printf(u8"\n Öldürme: %d | Hareket: %d | Puan: %d", kills, moves, calcPoint("OuterCall", 0));
	}
	calcPoint(name, 1);
	while (1);
}
int main() {
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
	CONSOLE_FONT_INFOEX font;
	font.cbSize = sizeof(font);
	font.nFont = 0;
	font.dwFontSize.X = 0;
	font.dwFontSize.Y = 18;
	font.FontFamily = FF_DONTCARE;
	font.FontWeight = FW_NORMAL;
	std::wcscpy(font.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &font);
	//https://msdn.microsoft.com/en-us/library/windows/desktop/ms686200%28v=vs.85%29.aspx
	//https://github.com/jimlawless/cmdmp3
	//http://www.newgrounds.com/audio/listen/274382
	system(u8"title Sandiklar ve Canavarlar & start /B assets/cmdmp3 assets/274382.mp3 >nul 2>&1"); //Windows (OD)
	char name[30], cevap;
	printf(u8"İsminizi giriniz: ");
	scanf(" %s", name);
	printf(u8"Hoş geldin %s\nBaşlamaya hazır mısın? (.(E)/,(H)):", name);
	if (confirm()) {
		printf(u8"\nEvet dedin.\nO zaman başlayalım >:[");
		findAndSetStartPoint();
		if (alwaysShowMap) drawMap(x, y, x_bot, y_bot);
		startGame(name);
	}
	else {
		printf(u8"\nHayır Dedin.\nO zaman hazır olduğunda gel! ");
	}
	while (1);
	return 0;
}