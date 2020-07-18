#include"Header.h"

int main() {
	COUNT count{ 0,0,0,0,0 };
	UPGRADES up{ 0,0,0 };
	UPGRADES_II up_ii{ false,0,0 };
	Instruction();
	Frame();
	Text();
	Streams(count, up, up_ii);
	system("pause > NULL");
}