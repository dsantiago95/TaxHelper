#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#include "Date.h"
#include "TaxPayer.h"
#include "Address.h"
#include "Brackets.h"
#include "Dependent.h"
#include "f1040.h"
#include "Schedule8812.h"
#include "Schedule1.h"
#include "Schedule2.h"
#include "Schedule3.h"
#include "Schedule8895.h"
#include "Schedule8863.h"

struct Brackets brackets;

void get_taxpayer_info(struct TaxPayer *taxpayer)
{
	char name[35+1];
	int month, day, year;
	scanf("Enter taxpayer name: %s", name);
	strcpy(taxpayer->name, name);
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
	scanf("Enter the tax year: %d\n", &tax_year);
	tax_return->tax_year = tax_year;

	struct Address address;
	char street[35+1];
	char city[35+1];
	char state[2+1];
	char zip[5+1];
	scanf("Enter the street address: %s", street);
	scanf("Enter the city address: %s", city);
	scanf("Enter the state address: %s", state);
	scanf("Enter the zip address: %s", zip);
	address = create_address(street, city, state, zip);
	tax_return->address = address;

	int status;
	printf("1 = Single\n \
			2 = Married filing jointly\n \
			3 = Married filing sperately\n \
			4 = Head of Household\n");
	scanf("Enter filing status: %d\n", &status);
	tax_return->status = status;

}

int main()
{
	/*
	struct f1040 tax_return;
	initialize_tax_return(&tax_return, 2024);

	read_brackets();
	
	struct Schedule1 sch1;
	initialize_schedule1(&sch1);

	struct Schedule2 sch2;
	initialize_schedule2(&sch2);

	struct Schedule3 sch3;
	initialize_schedule3(&sch3);

	struct Schedule8863 sch8863;
	initialize_schedule8863(&sch8863);

	struct TaxPayer primary;
	initialize_taxpayer(&primary);
	add_taxpayer(&tax_return, &primary);

	tax_return.status = 1;

	struct Address address = create_address("831 Elizabeth Ave", "Elizabeth", "NJ", "07201");
	add_address(&tax_return, address);

	struct Dependent dependent1;
	initialize_dependent(&dependent1);
	dependent1.odc_qualify = true;
	dependent1.eic_qualify = true;
	add_dependent(&tax_return, &dependent1);

	struct Dependent dependent2;
	initialize_dependent(&dependent2);
	dependent2.odc_qualify = true;
	dependent2.eic_qualify = true;
	add_dependent(&tax_return, &dependent2);

	struct Dependent dependent3;
	initialize_dependent(&dependent3);
	dependent3.ctc_qualify = true;
	dependent3.eic_qualify = true;
	add_dependent(&tax_return, &dependent3);

	add_wage_income(&primary, 12609);
	add_se_income(&primary, 10200);


	//All income assignments are above commit, all calculations are below commit.
	commit_taxpayer(&tax_return, &sch1);


	calculate_additional_income(&sch1);
	calculate_earned_income(&tax_return, &sch1);
	calculate_total_income(&tax_return, sch1);

	calculate_se_tax(&primary, &sch1, &sch2); //must calc before adjustments to income for se_tax_deduction
	calculate_adjustments_to_income(&sch1); //must calc before agi
	calculate_agi(&tax_return, sch1);
	
	set_std_deduction(&tax_return);

	calculate_qbi_deduction(&tax_return, &sch1);

	calculate_taxable_income(&tax_return);

	calculate_tax(&tax_return);

	calculate_ctc_odc(&tax_return, &sch3);

	calculate_aotc_llc(&tax_return, &sch2, 4000);

	calculate_eic(&tax_return);
	*/

	struct TaxPayer tp1;
	initialize_taxpayer(&tp1, "Bob");

	struct TaxPayer tp2;
	initialize_taxpayer(&tp2, "Bob");


	if (taxpayers_are_equal(tp1, tp2))
	{
		printf("compiled!\n");
	}
}
