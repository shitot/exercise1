/*
Guy Golpur
Bar Azouri
Hadar Ivan
Shachar Levkovich
*/

#include <Windows.h>
#include <sstream>
#include <iostream>
#include <string>
#include "Checkbox.h"
#include <vector>

using namespace std;

class Checklist {
	private:
		COORD listPosition;
		Checkbox *list;
		int listSize;
		HANDLE HandleOutPut;
	public:
		Checklist(vector<string> elementsList, int X, int Y);
        ~Checklist();
		void HandleInput(INPUT_RECORD inputRecord);
		void draw();
        void MouseEventHandleing(MOUSE_EVENT_RECORD mouseEvent);
		void KeyEventHandleing(KEY_EVENT_RECORD keyEvent);
};