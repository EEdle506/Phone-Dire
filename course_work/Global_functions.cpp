using namespace std;
#include "Dire.h"

//////////////////////////////////////////////////////////////

void ChangeColour(int colour) {
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(handle, colour);
}

int GetKey() {
    int a = 0;
    a = _getch();
    return a - 48;
}

//////////////////////////////////////////////////////////////