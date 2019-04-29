/*
Guy Golpur
Bar Azouri
Hadar Ivan
Shachar Levkovich
*/

#include "checkList.h"

Checklist::Checklist(vector<string> elementsList, int X, int Y) {
	this->listPosition.X = X;
	this->listPosition.Y = Y;
	this->listSize = elementsList.size();
	this->HandleOutPut = GetStdHandle(STD_OUTPUT_HANDLE);
	this->list = new Checkbox[this->listSize];
	if (this->list == nullptr) {
		cout << "Allocation failed";
		exit(0);
	}
	for (int i = 0; i < this->listSize; ++i) {
		this->list[i].setText(elementsList[i]);
		this->list[i].setPositionX(X);
		this->list[i].setPositionY(Y + i);
		this->list[i].setKeyboardPos(false);
	}
	this->list[0].setKeyboardPos(true);
}

Checklist::~Checklist() {
	delete[] this->list;
}

void Checklist::HandleInput(INPUT_RECORD inputRecord) {
	if (inputRecord.EventType == KEY_EVENT) {
		this->KeyEventHandleing(inputRecord.Event.KeyEvent);
	}
	else {
		MouseEventHandleing(inputRecord.Event.MouseEvent);
	}
}

void Checklist::draw() {
	SetConsoleCursorPosition(HandleOutPut, listPosition);
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	GetConsoleScreenBufferInfo(HandleOutPut, &consoleScreenBufferInfo);

	CONSOLE_CURSOR_INFO consoleCursorInfo = { 100, FALSE };
	SetConsoleCursorInfo(HandleOutPut, &consoleCursorInfo);

	for (int i = 0; i < listSize; ++i) {
		SetConsoleCursorPosition(HandleOutPut, this->list[i].getCoordinate());
		this->list[i].draw();
	}
}

void Checklist::MouseEventHandleing(MOUSE_EVENT_RECORD mouseEvent) {
	COORD mCords = mouseEvent.dwMousePosition;
	if (mouseEvent.dwEventFlags == 0) {
		if (mouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			for (int i = 0; i < this->listSize; ++i) {
				if (this->list[i].isTarget(mCords)) {
					SetConsoleCursorPosition(HandleOutPut, this->list[i].getCoordinate());
					this->list[i].changeMode();
					break;
				}
			}
		}
	}
}

void Checklist::KeyEventHandleing(KEY_EVENT_RECORD keyEvent) {
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	GetConsoleScreenBufferInfo(HandleOutPut, &consoleScreenBufferInfo);

	Checkbox *item = nullptr;
	int Currectitem;
	if (keyEvent.bKeyDown == true) {
		for (int i = 0; i < this->listSize; ++i) {
			if (this->list[i].getKeyboardPos() == true) {
				item = &this->list[i];
				Currectitem = i;
				break;
			}
		}
		if (item == nullptr) {
			return;
		}
		if (keyEvent.wVirtualKeyCode == VK_DOWN) {
			item->setKeyboardPos(false);
			if (Currectitem == this->listSize - 1) {
				item = &this->list[0];
				item->setKeyboardPos(true);
				Currectitem = 0;
			}
			else {
				++Currectitem;
				item = &this->list[Currectitem];
				item->setKeyboardPos(true);
			}
			return;
		}
		if (keyEvent.wVirtualKeyCode == VK_UP) {
			item->setKeyboardPos(false);
			if (Currectitem == 0) {
				Currectitem = this->listSize - 1;
				this->list[Currectitem].setKeyboardPos(true);
			}
			else {
				--Currectitem;
				this->list[Currectitem].setKeyboardPos(true);
			}
			return;
		}	
		if (keyEvent.wVirtualKeyCode == VK_SPACE) {
			SetConsoleCursorPosition(HandleOutPut, this->list[Currectitem].getCoordinate());
			this->list[Currectitem].changeMode();
			return;
		}
	}
}