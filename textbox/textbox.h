#include <string>
#include <windows.h>
#include <iostream>
using namespace std;

class TextBox
{
    public:
        short width;
        short top;
        short left;
        bool hasBorder;
        WORD color;
        WORD background;

        string value;
        TextBox(short width, short top, short left, string value);
        void draw();

        void handleKeyboardEvent(KEY_EVENT_RECORD&);
        void handleMouseEvent(MOUSE_EVENT_RECORD&);

};