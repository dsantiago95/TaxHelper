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

bool addresses_are_equal(struct Address a1, struct Address a2)
{
	if (a1.street_address != a2.street_address)
	{
		return false;
	}
	if (a1.city != a2.city)
	{
		return false;
	}
	if (a1.state != a2.state)
	{
		return false;
	}
	if (a1.zip_code != a2.zip_code)
	{
		return false;
	}

	return true;
}
