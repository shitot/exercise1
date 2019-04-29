#include <iostream>
#include <string>
#include <Windows.h>
#include <stdio.h>
#include "checkList.h"

using namespace std;

void sendCheckBox() {
	vector<string> elementsList = {"Guy Golpur", "Bar Azouri", "Hadar Ivan", "Shachar Levkovich"};
	Checklist checkList(elementsList, 50, 10);
	checkList.draw();
	HANDLE handleInput = GetStdHandle(STD_INPUT_HANDLE);
	while (true) {
		INPUT_RECORD inputList;
		DWORD countDword;
		ReadConsoleInput(handleInput, &inputList, 1, &countDword);
		checkList.HandleInput(inputList);
	}
}

int main(int argc, char** argv) {
	sendCheckBox();
}

