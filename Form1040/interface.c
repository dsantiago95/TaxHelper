#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "interface.h"
#include "Date.h"
#include "TaxPayer.h"
#include "Address.h"
#include "Dependent.h"
#include "f1040.h"


void get_taxpayer_info(struct TaxPayer *taxpayer)
{
	char name[35+1];
	int month, day, year;
	printf("Enter taxpayer name: ");
	scanf("%s", name);
	initialize_taxpayer(taxpayer, name);
	printf("Enter date of birth.\n");
	scanf("Month (i.e. 10 = Oct): %d\n", &month);
	scanf("Day: %d\n", &day);
	scanf("Year (YYYY): %d\n", &year);
	struct Date dob = create_date(month, day, year);
	taxpayer->dob = dob;
}

void get_tax_return_info(struct f1040 *tax_return)
{
	int tax_year;
	printf("Enter the tax year: ");
	scanf("%d", &tax_year);
	initialize_tax_return(tax_return, tax_year);

	struct Address address;
	char street[35+1];
	char city[35+1];
	char state[2+1];
	char zip[5+1];
	printf("Enter the street address: ");
	fflush(stdin); //flush the \n\0 from previous scanf()
	fgets(street, 36, stdin);
	printf("Enter the city address: ");
	scanf("%s", city);
	printf("Enter the state address: ");
	scanf("%s", state);
	printf("Enter the zip address: ");
	scanf("%s", zip);
	address = create_address(street, city, state, zip);
	tax_return->address = address;

	int status;
	printf("1 = Single\n \
			2 = Married filing jointly\n \
			3 = Married filing sperately\n \
			4 = Head of Household\n");
	printf("Enter filing status: ");
	scanf("%d", &status);
	tax_return->status = status;

}

