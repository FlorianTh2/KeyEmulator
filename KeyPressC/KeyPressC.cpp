// KeyPressC.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>

#define WINVER 0x0500


// msdn.microsoft.com/en-us/library/dd375731
// Sleep(2500);
int main()
{
    std::cout << "Program running...\n";

    // mouseInput event
    // usage of the array form since we need several events at one
    // if only one event is needed: use INPUT keyboardInput; and remove array syntax in following code
    INPUT keyboardInput[2];

    // Set up a generic keyboard event.
    keyboardInput[0].type = INPUT_KEYBOARD;
    keyboardInput[0].ki.wScan = 0;
    keyboardInput[0].ki.time = 0;
    keyboardInput[0].ki.dwExtraInfo = 0;
    keyboardInput[0].ki.wVk = 0x0D;
    // key press
    keyboardInput[0].ki.dwFlags = 0;

    // Release
    keyboardInput[1].type = INPUT_KEYBOARD;
    keyboardInput[1].ki.wScan = 0; // hardware scan code for key
    keyboardInput[1].ki.time = 0;
    keyboardInput[1].ki.dwExtraInfo = 0;
    keyboardInput[1].ki.wVk = 0x0D; // 0x0D;
    keyboardInput[1].ki.dwFlags = KEYEVENTF_KEYUP;


    // mouseclick
    // 1 mousemovement = 1 x up oder 1 x down
    int const clicks = 1;
    INPUT mouseInput[clicks * 2];
    // zeroMemory usage recommended according to stackoverflow to prevent blackscreen
    // initialized several variables to prevent blackscreen
    ZeroMemory(&mouseInput, sizeof(mouseInput));

    for (int i = 0; i < clicks; i++)
    {
        int position = i * 2;
        mouseInput[position].type = INPUT_MOUSE;
        mouseInput[position].mi.dx = 0;
        mouseInput[position].mi.dy = 0;
        mouseInput[position].mi.dwFlags = MOUSEEVENTF_ABSOLUTE; // | MOUSEEVENTF_MOVE;
        mouseInput[position].type = INPUT_MOUSE;
        mouseInput[position].mi.dwFlags = MOUSEEVENTF_LEFTDOWN;

        mouseInput[position + 1].type = INPUT_MOUSE;
        mouseInput[position + 1].mi.dx = 0;
        mouseInput[position + 1].mi.dy = 0;
        mouseInput[position + 1].mi.dwFlags = MOUSEEVENTF_ABSOLUTE; // | MOUSEEVENTF_MOVE;
        mouseInput[position + 1].type = INPUT_MOUSE;
        mouseInput[position + 1].mi.dwFlags = MOUSEEVENTF_LEFTUP;
    }


    while (true)
    {
        if (GetKeyState('W') & 0x8000)
        {
            SendInput(2, keyboardInput, sizeof(INPUT));
        }
        if (GetKeyState('E') & 0x8000)
        {
            SendInput(clicks, mouseInput, sizeof(INPUT));
            Sleep(0.1);
        }
        if (GetKeyState('Q') & 0x8000)
        {
            break;
        }
    }

    return 0;
}