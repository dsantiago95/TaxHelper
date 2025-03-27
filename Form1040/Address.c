#include <stdio.h>
#include <string.h>

#include "Address.h"

struct Address create_address(char street[35+1], char city[35+1], char state[2+1], char zip[5+1])
{
	struct Address return_add;
	strncpy(return_add.street_address, street, 35+1);
	strncpy(return_add.city, city, 35+1);
	strncpy(return_add.state, state, 2+1);
	strncpy(return_add.zip_code, zip, 5+1);
	printf("Address created.\n");
	return return_add;
}
