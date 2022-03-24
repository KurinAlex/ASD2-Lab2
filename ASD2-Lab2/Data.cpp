#include "Data.h"

std::string colors[] = { "yellow","red","green","blue","purple","gold","silver" };
int colors_size = size(colors);

Data::Data()
{
	color = colors[rand() % colors_size];
	number = rand() % 13 + 1;
	has_charger = rand() % 2;
}