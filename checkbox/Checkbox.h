/*
Guy Golpur
Bar Azouri
Hadar Ivan
Shachar Levkovich
*/

#include <string>
#include <Windows.h>
#include <sstream>
#include <iostream>

using namespace std;

class Checkbox {
	private:
		HANDLE HandleOutPut;
		COORD position;
		string text;
		int length;
		bool clicked;
		bool KeyBoardPos;
	public:
		Checkbox(string text, int x, int y);
		Checkbox();
		void draw();
		void changeMode();
		bool isTarget(COORD mouseCordinate);
		void setText(string text);
		void setPositionX(int x);
		void setPositionY(int y);
		COORD getCoordinate();
		bool getCheckedStatus();
		void setKeyboardPos(bool whereIn);
		bool getKeyboardPos();
};