/*
Guy Golpur
Bar Azouri
Hadar Ivan
Shachar Levkovich
*/

#include "Checkbox.h"

Checkbox::Checkbox(string text, int x, int y) {
	this->position.X = x;
	this->position.Y = y;
	this->text = text;
	this->length = text.length() + 1;
	this->clicked = false;
	this->HandleOutPut = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Checkbox::draw() {
	SetConsoleCursorPosition(this->HandleOutPut, this->position);
	CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
	GetConsoleScreenBufferInfo(this->HandleOutPut, &consoleScreenBufferInfo);

	CONSOLE_CURSOR_INFO consoleCursorInfo = { 100, FALSE };
	SetConsoleCursorInfo(this->HandleOutPut, &consoleCursorInfo);

	if (this->clicked == true) {
		cout << "[X]" << this->text;
	}
	else {
		cout << "[ ]" << this->text;
	}
	
}

void Checkbox::changeMode() {
	if (this->clicked == true) {
		this->clicked = false;
		this->draw();
	}
	else {
		this->clicked = true;
		this->draw();
	}
}

void Checkbox::setPositionX(int x) {
	this->position.X = x;
}

void Checkbox::setPositionY(int y) {
	this->position.Y = y;
}

void Checkbox::setText(string text) {
	this->text = text;
	this->length = text.length() +1;
}

bool Checkbox::isTarget(COORD mouseCordinate) {
	if (mouseCordinate.Y == this->position.Y && mouseCordinate.X > this->position.X && mouseCordinate.X < this->position.X + this->length) {
		return true;
	}
	return false;
}

COORD Checkbox::getCoordinate() {
	return this->position;
}

bool Checkbox::getCheckedStatus() {
	return this->clicked;
}

void Checkbox::setKeyboardPos(bool whereIn) {
	this->KeyBoardPos = whereIn;
}

bool Checkbox::getKeyboardPos() {
	return this->KeyBoardPos;
}

Checkbox::Checkbox() {}