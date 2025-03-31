#include <stdio.h>
#include <string.h>

#include "Address.h"

struct Address create_address(char street[35+1], char city[35+1], char state[2+1], char zip[5+1])
{
	struct Address return_add;
	strcpy(return_add.street_address, street);
	strcpy(return_add.city, city);
	strcpy(return_add.state, state);
	strcpy(return_add.zip_code, zip);
	printf("Address created.\n");
	return return_add;
}
