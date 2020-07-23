#include<iostream>
#include<Windows.h>
#include<thread>
#include<chrono>
using namespace std;

enum class COLOURS { BROWN = 4, GREY = 8, YELLOW = 6, CYAN = 3, GREEN = 2, WHITE = 15, BLUE = 1, LIGHTGREEN = 10 };

struct COUNT {
    unsigned long long Skin;
    unsigned long long Iron;
    unsigned long long Gold;
    unsigned long long Diamond;
    unsigned long long Ruby;
};

struct UPGRADES {
    int price;
    int colour;
    int count;
    char* str;
    bool buying;
};

struct UPGRADES_II {
    bool buying;
    bool temp;
    int price;
    int sleep;
};

void Text();
void Frame();
void Instruction();
void PrintProgress(COUNT& count);
void KlickII(COUNT& count, UPGRADES_II& up_ii);
void Klick(COUNT& count, UPGRADES& up, UPGRADES_II& up_ii);
void Streams(COUNT& count, UPGRADES& up, UPGRADES_II& up_ii);
void PrintKlick(UPGRADES& up, COORD mouse, int colour);
void PrintUpgrades(UPGRADES*& up, int count);
void PrintUpgradesII(UPGRADES_II*& up_ii, int count);
UPGRADES* Upgrades(UPGRADES& up);
UPGRADES_II* UpgradesII(UPGRADES_II& up_ii);
void PrintBuy(int x, int y, int colour);
void CheckToBuy(COUNT& count, UPGRADES*& up_ar, UPGRADES_II*& up_ii_ar,
    int count_buying, int count_buying_i);
void CheckToPlus(COUNT& count);