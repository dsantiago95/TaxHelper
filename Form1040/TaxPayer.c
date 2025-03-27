#include <stdbool.h>
#include <stdio.h>

#include "TaxPayer.h"


void initialize_taxpayer(struct TaxPayer *taxpayer)
{
	taxpayer->w2_wages = 0;
	taxpayer->rental_income = 0;
	taxpayer->se_income = 0; //Sch C, Sch E pg2
	taxpayer->eic_qualify = false;

	printf("Taxpayer initialized successfuly.\n");
}

void add_wage_income(struct TaxPayer *taxpayer, int wages)
{
	taxpayer->w2_wages += wages;
	printf("Wages of %d added.\n", taxpayer->w2_wages);
}

void add_se_income(struct TaxPayer *taxpayer, int se_income)
{
	taxpayer->se_income += se_income;
	printf("Self-employed income %d added.\n", taxpayer->se_income);
}
