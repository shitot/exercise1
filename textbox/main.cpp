#include "textbox.h"
using namespace std;

int main(int argc, char const *argv[])
{
    auto handle = GetStdHandle(STD_INPUT_HANDLE);

    TextBox tb(20, 3, 3, "");
    tb.draw();
    
    while (1) 
    {
        INPUT_RECORD ir;
        DWORD count;
        DWORD fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
        SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),fdwMode);
        ReadConsoleInput(handle, &ir, 1, &count);
        if (count)
        {
            if (ir.EventType == KEY_EVENT)
            {
                tb.handleKeyboardEvent(ir.Event.KeyEvent); //writes to text box
            }
            if (ir.EventType == MOUSE_EVENT) 
            {
                tb.handleMouseEvent(ir.Event.MouseEvent);
            }
        }
    }

    

    return 0;
}
