#include "textbox.h"
#include <iostream>
#include <algorithm>

static int flag = 0;

TextBox::TextBox(short width, short top, short left, std::string value) : 
    width(width), top(top), value(value), left(left), hasBorder(true),
    color(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY),
    background(0)  { }

void TextBox::handleKeyboardEvent(KEY_EVENT_RECORD& event)
{
    int textWidth = value.length();
    CONSOLE_SCREEN_BUFFER_INFO info;
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &info);

    if (!event.bKeyDown) return;

    if (event.wVirtualKeyCode >= 0x30 && event.wVirtualKeyCode <= 0x5a || event.wVirtualKeyCode == 0x20) //adds to the end
    {
        
        if(value.length() == this->width)
        {
            return;
        }

        if(info.dwCursorPosition.X - this->left-1 == this->width)
        {
            return;
        }
        
        if(textWidth == info.dwCursorPosition.X -  this->left - 1)
        {
            value.push_back(event.uChar.AsciiChar);
            draw();
        }
        else 
        {
            flag = 1;
            value.insert(info.dwCursorPosition.X-this->left -1, string(1, event.uChar.AsciiChar));
            draw();
        }
    }
    else flag=0;

    if (event.wVirtualKeyCode == VK_LEFT || event.wVirtualKeyCode == VK_RIGHT || event.wVirtualKeyCode == VK_NUMPAD4 || event.wVirtualKeyCode == VK_NUMPAD6)
    {
         
        auto offset = info.dwCursorPosition.X - this->left - 1;

        if (offset > 0 && (event.wVirtualKeyCode == VK_LEFT || event.wVirtualKeyCode == VK_NUMPAD4))
        {
            SetConsoleCursorPosition(handle,{ info.dwCursorPosition.X - 1, info.dwCursorPosition.Y });
        }

        if (offset < textWidth && (event.wVirtualKeyCode == VK_RIGHT || event.wVirtualKeyCode == VK_NUMPAD6))
        {
            SetConsoleCursorPosition(handle,{ info.dwCursorPosition.X + 1, info.dwCursorPosition.Y });
        }
    }

    if (event.wVirtualKeyCode == VK_BACK) //delete from end
    {
        if(info.dwCursorPosition.X - this->left == 1)
        {
            return;
        }
        if(textWidth == info.dwCursorPosition.X -  this->left - 1)
        {
            value.pop_back();
            draw();
        }
        else 
        {
            flag=2;
            value.erase(info.dwCursorPosition.X-this->left-2, 1);
            draw();
        }
    }
     if (event.wVirtualKeyCode == VK_DELETE) //delete from end
    {
        if(textWidth == info.dwCursorPosition.X -  this->left - 1)
        {
            return;
        }
        else 
        {
            flag=3;
            value.erase(info.dwCursorPosition.X-this->left-1, 1);
            draw();
        }
    }
}

void TextBox::handleMouseEvent(MOUSE_EVENT_RECORD& event)
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(handle, &info);
    if(event.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
    {
        if((event.dwMousePosition.X > this->left && event.dwMousePosition.X < value.length()+this->left) && (event.dwMousePosition.Y == this->top+1))
        {
            SetConsoleCursorPosition(handle,{ event.dwMousePosition.X, event.dwMousePosition.Y });
        }
    }

}

void TextBox::draw()
{
    auto handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(handle, &info);
    COORD coord = { left, top };
    SetConsoleCursorPosition(handle, coord);
    SetConsoleTextAttribute(handle, color | (background << 4));
    
    std::cout << (char) 0xda;
    for (int i=0; i<width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xbf;

    SetConsoleCursorPosition(handle, {coord.X, coord.Y+1});
    std::cout << (char) 0xb3;
    
    for (int i =0; i < width; i++)
        std::cout << (i >= value.length() ? ' ' : value[i]);
    
    SetConsoleCursorPosition(handle, { left + width + 1, top + 1 });
    std::cout << (char) 0xb3;

    SetConsoleCursorPosition(handle, { left, top + 2 });
    std::cout << (char) 0xc0;
    for (int i = 0; i < width; i++)
        std::cout << (char) 0xc4;
    std::cout << (char) 0xd9;
    
    switch(flag)
    {
        case 0:
            SetConsoleCursorPosition(handle, { left + 1 + value.length(), top+1 });
            break;
        case 1:    
            SetConsoleCursorPosition(handle, {left + 1 + info.dwCursorPosition.X - this->left, top+1});
            break;
        case 2:   
            SetConsoleCursorPosition(handle, {left + 1 + info.dwCursorPosition.X - this->left-2, top+1});
            break;
        case 3:
            SetConsoleCursorPosition(handle, {left + 1 + info.dwCursorPosition.X - this->left-1, top+1});
            break;
    }
}

