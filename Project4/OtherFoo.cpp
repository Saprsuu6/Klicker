#include"Header.h"

HANDLE h = GetStdHandle(-11);
HWND hwnd = GetConsoleWindow();

void Instruction() {
    system("mode con cols=40 lines=20");
    int desktop_width = GetSystemMetrics(SM_CXSCREEN);
    int desktop_height = GetSystemMetrics(SM_CYSCREEN);
    int left_shift = desktop_width - 850;
    int top_shift = desktop_height - 750;
    MoveWindow(hwnd, left_shift, top_shift, 800, 400, true);
    CONSOLE_CURSOR_INFO info;
    info.bVisible = false;
    info.dwSize = 1;
    SetConsoleCursorInfo(h, &info);
    SetConsoleTextAttribute(h, (int)COLOURS::LIGHTGREEN);
}

void Frame() {
    int width = 39;
    int hight = 19;
    for (int i = 0; i < hight; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || j == 0 || i == hight - 1 || j == width - 1 ||
                i == hight - 7)
                cout << char(219);
            else if (i == hight - 2 && j == 1)
                cout << char(200);
            else if (i == hight - 6 && j == 1)
                cout << char(201);
            else if (i == hight - 6 && j == width - 2)
                cout << char(187);
            else if (i == hight - 2 && j == width - 2)
                cout << char(188);
            else if (i == hight - 6 || i == hight - 2)
                cout << char(205);
            else if ((j == width - 2 || j == 1) && i > hight - 6 && i < hight - 1)
                cout << char(186);
            else
                cout << " ";
        }
        cout << endl;
    }
}

void Text() {
    COORD c{ 30, 2 };
    SetConsoleTextAttribute(h, (int)COLOURS::WHITE);
    SetConsoleCursorPosition(h, c);
    cout << "< >";
    c.X = 30, c.Y += 2;
    SetConsoleCursorPosition(h, c);
    cout << "< >";
    c.X = 2, c.Y += 2;
    SetConsoleTextAttribute(h, (int)COLOURS::BROWN);
    SetConsoleCursorPosition(h, c);
    cout << "Skin - 0";
    c.X = 2, c.Y++;
    SetConsoleTextAttribute(h, (int)COLOURS::GREY);
    SetConsoleCursorPosition(h, c);
    cout << "Iron - 0";
    c.X = 2, c.Y++;
    SetConsoleTextAttribute(h, (int)COLOURS::YELLOW);
    SetConsoleCursorPosition(h, c);
    cout << "Gold - 0";
    c.X = 2, c.Y++;
    SetConsoleTextAttribute(h, (int)COLOURS::CYAN);
    SetConsoleCursorPosition(h, c);
    cout << "Diamond - 0";
    c.X = 2, c.Y++;
    SetConsoleTextAttribute(h, (int)COLOURS::GREEN);
    SetConsoleCursorPosition(h, c);
    cout << "Ruby - 0";
}

void PrintProgress(COUNT& count) {
    COORD c{ 9, 6 };
    SetConsoleTextAttribute(h, (int)COLOURS::BROWN);
    SetConsoleCursorPosition(h, c);
    cout << count.Skin;
    c.X = 9, c.Y++;
    SetConsoleTextAttribute(h, (int)COLOURS::GREY);
    SetConsoleCursorPosition(h, c);
    cout << count.Iron;
    c.X = 9, c.Y++;
    SetConsoleTextAttribute(h, (int)COLOURS::YELLOW);
    SetConsoleCursorPosition(h, c);
    cout << count.Gold;
    c.X = 12, c.Y++;
    SetConsoleTextAttribute(h, (int)COLOURS::CYAN);
    SetConsoleCursorPosition(h, c);
    cout << count.Diamond;
    c.X = 9, c.Y++;
    SetConsoleTextAttribute(h, (int)COLOURS::GREEN);
    SetConsoleCursorPosition(h, c);
    cout << count.Ruby;
}

void KlickII(COUNT& count, UPGRADES_II& up_ii) {
    while (true) {
        if (up_ii.temp) {
            count.Skin++;
            CheckToPlus(count);
            PrintProgress(count);
            Sleep(up_ii.sleep);
        }
    }
}

void Klick(COUNT& count, UPGRADES& up, UPGRADES_II& up_ii) {
    int press_colour = (int)COLOURS::WHITE;
    int count_buying = 0;
    int count_buying_ii = 0;
    bool temp = false;
    int upgrades = 5;
    up.str = new char[upgrades];
    strcpy_s(up.str, upgrades, "+1");
    UPGRADES* up_ar = new UPGRADES[upgrades];
    up_ar = Upgrades(up);
    UPGRADES_II* up_ii_ar = new UPGRADES_II[upgrades];
    up_ii_ar = UpgradesII(up_ii);
    PrintUpgrades(up_ar, 0);
    PrintUpgradesII(up_ii_ar, 0);
    COORD mouse;
    HANDLE h_m = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleMode(h_m, ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
    const int events = 256;
    INPUT_RECORD all_events[events];
    DWORD read_events;
    while (true) {
        if (!up_ar[count_buying].buying && !up_ii_ar[count_buying_ii].buying)
            CheckToBuy(count, up_ar, up_ii_ar, count_buying, count_buying_ii);
        else if (up_ar[count_buying].buying)
            PrintBuy(34, 2, (int)COLOURS::CYAN);
        else if (up_ii_ar[count_buying_ii].buying)
            PrintBuy(34, 4, (int)COLOURS::CYAN);
        ReadConsoleInput(h_m, all_events, events, &read_events);
        for (int i = 0; i < read_events; i++) {
            mouse.X = all_events[i].Event.MouseEvent.dwMousePosition.X;
            mouse.Y = all_events[i].Event.MouseEvent.dwMousePosition.Y;
            if (all_events[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED
                || all_events[i].Event.MouseEvent.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
                if (mouse.X > 1 && mouse.X < 36 && mouse.Y > 13 && mouse.Y < 17) {
                    count.Skin += up.count;
                    PrintKlick(up, mouse, press_colour);
                    SetConsoleTextAttribute(h, press_colour);
                    CheckToPlus(count);
                }
                if (mouse.Y == 2) {
                    if (mouse.X == 32 && count_buying < 4) {
                        count_buying++;
                        PrintUpgrades(up_ar, count_buying);
                    }
                    else if (mouse.X == 30 && count_buying > 0) {
                        count_buying--;
                        PrintUpgrades(up_ar, count_buying);
                    }
                }
                else if (mouse.Y == 4) {
                    if (mouse.X == 32 && count_buying_ii < 4) {
                        count_buying_ii++;
                        PrintUpgradesII(up_ii_ar, count_buying_ii);
                    }
                    else if (mouse.X == 30 && count_buying_ii > 0) {
                        count_buying_ii--;
                        PrintUpgradesII(up_ii_ar, count_buying_ii);
                    }
                }
                if (mouse.X > 33 && mouse.X < 37 && mouse.Y == 2 && count.Skin >= up_ar[count_buying].price
                    && !up_ar[count_buying].buying) {
                    press_colour = up_ar[count_buying].colour;
                    up.count = up_ar[count_buying].count;
                    up.str = up_ar[count_buying].str;
                    up_ar[count_buying].buying = true;
                }
                else if (mouse.X > 33 && mouse.X < 37 && mouse.Y == 4 && count.Skin >= up_ii_ar[count_buying_ii].price
                    && !up_ii_ar[count_buying_ii].buying) {
                    up_ii.temp = up_ii_ar[count_buying_ii].temp;
                    up_ii.sleep = up_ii_ar[count_buying_ii].sleep;
                    up_ii_ar[count_buying_ii].buying = true;
                }
                PrintProgress(count);
            }
        }
    }
}

void CheckToPlus(COUNT& count) {
    if (count.Skin > 1000)
        count.Iron++;
    else if (count.Iron > 30000)
        count.Gold;
    else if (count.Gold > 50000)
        count.Diamond++;
    else if (count.Diamond > 100000)
        count.Ruby++;
}

void CheckToBuy(COUNT& count, UPGRADES*& up_ar, UPGRADES_II*& up_ii_ar, 
    int count_buying, int count_buying_ii) {
    if (count.Skin >= up_ar[count_buying].price)
        PrintBuy(34, 2, (int)COLOURS::GREEN);
    else
        PrintBuy(34, 2, (int)COLOURS::BROWN);
    if (count.Skin >= up_ii_ar[count_buying_ii].price)
        PrintBuy(34, 4, (int)COLOURS::GREEN);
    else
        PrintBuy(34, 4, (int)COLOURS::BROWN);
}

void PrintBuy(int x, int y, int colour) {
    COORD c{ x,y };
    SetConsoleTextAttribute(h, colour);
    SetConsoleCursorPosition(h, c);
    cout << "Buy";
}

void PrintKlick(UPGRADES& up, COORD mouse, int colour) {
    SetConsoleCursorPosition(h, mouse);
    SetConsoleTextAttribute(h, colour);
    cout << up.str;
    //Sleep(50);
    SetConsoleCursorPosition(h, mouse);
    cout << "  ";
}

void Streams(COUNT& count, UPGRADES& up, UPGRADES_II& up_ii) {
    thread th(KlickII, ref(count), ref(up_ii));
    Klick(count, up, up_ii);
    th.join();
}

UPGRADES* Upgrades(UPGRADES& up) {
    int upgrades = 5;
    UPGRADES* up_ar = new UPGRADES[upgrades];
    for (int i = 0; i < upgrades; i++) {
        up_ar[i].buying = false;
        up_ar[i].price = 1000 + (i * (1000 + i * 5000));
        up_ar[i].colour = rand() % 15 + 1;
        up_ar[i].count = 2 + i;
        up_ar[i].str = new char[5];
        char* temp_str = new char[5];
        _itoa_s(2 + i, temp_str, 5, 10);
        strcpy_s(up_ar[i].str, 4, "+");
        strcat_s(up_ar[i].str, 4, temp_str);
        delete[] temp_str;
    }
    return up_ar;
}

UPGRADES_II* UpgradesII(UPGRADES_II& up_ii) {
    int upgrades = 5;
    UPGRADES_II* up_ii_ar = new UPGRADES_II[upgrades];
    for (int i = 0; i < upgrades; i++) {
        up_ii_ar[i].buying = false;
        up_ii_ar[i].price = 1000 + (i * (1000 + i * 5000));
        up_ii_ar[i].sleep = 1000 - (i * 200);
        up_ii_ar[i].temp = true;
    }
    return up_ii_ar;
}

void PrintUpgrades(UPGRADES*& up, int count) {
    COORD c{ 2,2 };
    SetConsoleCursorPosition(h, c);
    SetConsoleTextAttribute(h, (int)COLOURS::WHITE);
    switch (count) {
    case(0):
        cout << "+2 for skin    " << up[0].price << "sk. ";
        break;
    case(1):
        cout << "+3 for skin    " << up[1].price << "sk. ";
        break;
    case(2):
        cout << "+4 for skin    " << up[2].price << "sk. ";
        break;
    case(3):
        cout << "+5 for skin    " << up[3].price << "sk. ";
        break;
    case(4):
        cout << "+6 for skin    " << up[4].price << "sk. ";
    }
}

void PrintUpgradesII(UPGRADES_II*& up_ii, int count) {
    COORD c{ 2,4 };
    SetConsoleCursorPosition(h, c);
    SetConsoleTextAttribute(h, (int)COLOURS::WHITE);
    switch (count) {
    case(0):
        cout << "Each 1 sec.   " << up_ii[0].price << "sk.  ";
        break;
    case(1):
        cout << "Each 0,8 sec.   " << up_ii[1].price << "sk.  ";
        break;
    case(2):
        cout << "Each 0,6 sec.   " << up_ii[2].price << "sk.  ";
        break;
    case(3):
        cout << "Each 0,4 sec.   " << up_ii[3].price << "sk.  ";
        break;
    case(4):
        cout << "Each 0,2 sec.   " << up_ii[4].price << "sk.  ";
    }
}