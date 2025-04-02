#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "TaxPayer.h"

bool taxpayers_are_equal(struct TaxPayer tp1, struct TaxPayer tp2)
{
	if (strcmp(tp1.name, tp2.name))
	{
		return false;
	}
	if (dates_are_equal(tp1.dob, tp2.dob))
	{
		return false;
	}
	if (tp1.w2_wages != tp2.w2_wages)
	{
		return false;
	}
	if (tp1.rental_income != tp2.rental_income)
	{
		return false;
	}
	if (tp1.se_income != tp2.se_income)
	{
		return false;
	}
	if (tp1.eic_qualify != tp2.eic_qualify)
	{
		return false;
	}

	return true;
}

void initialize_taxpayer(struct TaxPayer *taxpayer, char name[35+1])
{
	strcpy(taxpayer->name, name);
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
