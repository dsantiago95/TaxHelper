#ifndef ADDRESS_H
#define ADDRESS_H

#include <stdbool.h>

struct Address {
	char street_address[35+1];
	char city[35+1];
	char state[2+1]; //state abbreviation, i.e. "NJ"
	char zip_code[5+1];
};

bool addresses_are_equal(struct Address, struct Address);

struct Address create_address(char street[35+1], char city[35+1], char state[2+1], char zip[5+1]);
#endif //ADDRESS_H
