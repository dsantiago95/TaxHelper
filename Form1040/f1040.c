#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "Date.h"
#include "TaxPayer.h"
#include "Address.h"
#include "Brackets.h"
#include "Dependent.h"
#include "Schedule8812.h"
#include "Schedule1.h"
#include "Schedule2.h"
#include "Schedule3.h"
#include "f1040.h"


//-----------*-*-*-------------------------*-*-*--------------------\\

void initialize_tax_return(struct f1040 *tax_return, int tax_year)
{
	tax_return->tax_year = tax_year;
	tax_return->address = NULL;
	tax_return->status = 0;
	for (int i = 0; i < MAX_DEP; i++)
	{
		tax_return->dependents[i] = NULL;
	}
	tax_return->w2_wages = 0;
	tax_return->sch1_additional_income = 0;
	tax_return->total_income = 0;
	tax_return->sch1_adjusments_to_income = 0;
	tax_return->agi = 0;
	tax_return->std_deduction = 0;
	tax_return->itemized_deduction = 0;
	tax_return->qbi_deduction = 0;
	tax_return->taxable_income = 0;
	tax_return->tax = 0;
	tax_return->sch2_add_taxes_precredits = 0;
	tax_return->ctc_odc_credit = 0;
	tax_return->sch3_additional_credits = 0;
	tax_return->sch2_other_taxes = 0;
	tax_return->total_taxes = 0;
	tax_return->w2_payments = 0;
	tax_return->f1099_payments = 0;
	tax_return->estimated_payments = 0;
	tax_return->eic_credit = 0;
	tax_return->actc_credit = 0;
	tax_return->aotc_credit = 0;

	printf("Tax Return initialized successfuly.\n");
}








/*
void add_taxpayer(struct f1040 *tax_return, struct TaxPayer taxpayer)
{
	if (tax_return->primary_taxpayer == NULL)
	{
		tax_return->primary_taxpayer = &taxpayer;
		printf("Taxpayer added successfuly.\n");
		return;
	} else if (tax_return->primary_taxpayer != NULL & tax_return->spouse == NULL)
	{
		tax_return->spouse = &taxpayer;
		printf("Spouse added successfuly.\n");
		return;
	}
	printf("Already 2 taxpayers on the return.\n");
	return;
}
*/

/* // For now, just let the programmer write to tax_return.status freely.
void set_status(struct f1040 *tax_return, int status)
{
	if (status == 1 | status == 4)
	{
		if (tax_return->spouse == NULL)
		{
			tax_return->status = status;
			printf("Status set successfuly.\n");
			return;
		}
		printf("Cannot set status to single or head of household if spouse is present. No changes made.\n");
		return;
	}
	tax_return->status = status;
	printf("Status set successfuly.\n");
	return;
}
*/


void add_address(struct f1040 *tax_return, struct Address address)
{
	if (tax_return->address == NULL)
	{
		tax_return->address = &address;
		printf("Address added to return.\n");
		return;
	} 
	printf("Address already assigned. No change.\n");
	return;
}

void set_std_deduction(struct f1040 *tax_return)
{
	if (tax_return->status == 1 | tax_return->status == 3)
	{
		tax_return->std_deduction = STD_DED_SINGLE;
		printf("Setting standard deduction: %d\n", tax_return->std_deduction);
		return;
	}
	else if (tax_return->status == 2)
	{
		tax_return->std_deduction = STD_DED_MFJ;
		printf("Setting standard deduction: %d\n", tax_return->std_deduction);
		return;
	}
	else if (tax_return->status == 4)
	{
		tax_return->std_deduction = STD_DED_HOH;
		printf("Setting standard deduction: %d\n", tax_return->std_deduction);
		return;
	}
}

void add_dependent(struct f1040 *tax_return, struct Dependent *dependent)
{
	for (int i = 0; i < MAX_DEP; i++)
	{
		if (tax_return->dependents[i] == NULL)
		{
			tax_return->dependents[i] = dependent;
			printf("New dependent added.\n");
			return;
		}
	}
	printf("Max number of dependents already present. No changes\n");
	return;
}

void commit_taxpayer(struct f1040 *tax_return, struct Schedule1 *schedule, struct TaxPayer taxpayer)
{
	tax_return->w2_wages += taxpayer.w2_wages;
	schedule->rental_income += taxpayer.rental_income;
	schedule->business_income += taxpayer.se_income;
	printf("Taxpayer income commited to f1040 and Schedule 1.\n");
}

void calculate_total_income(struct f1040 *tax_return, struct Schedule1 schedule)
{
	tax_return->total_income += tax_return->w2_wages;
	tax_return->total_income += schedule.additional_income;
	printf("Total income calculated: %d.\n", tax_return->total_income);
}

void calculate_agi(struct f1040 *tax_return, struct Schedule1 schedule)
{
	tax_return->agi = tax_return->total_income - schedule.adjustments_to_income;
	printf("AGI calculated: %d\n", tax_return->agi);
}

void calculate_taxable_income(struct f1040 *tax_return)
{
	tax_return->taxable_income += tax_return->agi;
	tax_return->taxable_income -= tax_return->std_deduction;
	tax_return->taxable_income -= tax_return->qbi_deduction;
	printf("Taxable income calculated: %d\n", tax_return->taxable_income);
}


void calculate_tax(struct f1040 *tax_return)
{
	int taxes = 0;
	int running_income = tax_return->taxable_income;

	if (running_income >= brackets.income_limit[0])
	{
		int income_diff = running_income - brackets.income_limit[0];
		taxes += (income_diff * brackets.tax_rate[0]);
		running_income -= income_diff;
	}
	if (running_income >= brackets.income_limit[1])
	{
		int income_diff = running_income - brackets.income_limit[1];
		taxes += (income_diff * brackets.tax_rate[1]);
		running_income -= income_diff;
	}
	if (running_income >= brackets.income_limit[2])
	{
		int income_diff = running_income - brackets.income_limit[2];
		taxes += (income_diff * brackets.tax_rate[2]);
		running_income -= income_diff;
	}
	if (running_income >= brackets.income_limit[3])
	{
		int income_diff = running_income - brackets.income_limit[3];
		taxes += (income_diff * brackets.tax_rate[3]);
		running_income -= income_diff;
	}
	if (running_income >= brackets.income_limit[4])
	{
		int income_diff = running_income - brackets.income_limit[4];
		taxes += (income_diff * brackets.tax_rate[4]);
		running_income -= income_diff;
	}
	if (running_income >= brackets.income_limit[5])
	{
		int income_diff = running_income - brackets.income_limit[5];
		taxes += (income_diff * brackets.tax_rate[5]);
		running_income -= income_diff;
	}
	if (running_income >= brackets.income_limit[6])
	{
		int income_diff = running_income - brackets.income_limit[6];
		taxes += (income_diff * brackets.tax_rate[6]);
		running_income -= income_diff;
	}
	if (running_income < 0)
	{
		printf("Error, running_income below 0.\n");
	}

	tax_return->tax = taxes;
	printf("Taxes calculated: %d\n", tax_return->tax);
}


int find_eitc_column(const struct f1040 *tax_return) {
	int col = 3;
	if (tax_return->status == 2)
	{
		col += 4; //offset to get to MFJ section of table
	}	
	for (int  i = 0; i < MAX_DEP; i++)
	{
		if (tax_return->dependents[i] != NULL)
		{
			if (tax_return->dependents[i]->eic_qualify)
			{
				col++;
			}
		}
	}

	return col;
}	

void calculate_earned_income(struct f1040 *tax_return, struct Schedule1 *sch1)
{
	tax_return->earned_income += tax_return->w2_wages;
	tax_return->earned_income += sch1->business_income;
}

void calculate_eic(struct f1040 *tax_return)
{
	int eic_return = 0;
	
	FILE *f = fopen(EITC_TABLE, "r");


	int col1, col2, col3, col4, col5, col6, col7, col8, col9, col10;
	int eitc_row[10];

	if (f == NULL) { return; }

	char buf[256];
	while (fgets(buf, sizeof(buf), f))
	{
		sscanf(
			buf,
			"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
			&col1, &col2, &col3, &col4, &col5, 
			&col6, &col7, &col8, &col9, &col10
		);

		if (tax_return->earned_income >= col1 & tax_return->earned_income < col2)
		{
			eitc_row[0] = col1;
			eitc_row[1] = col2;
			eitc_row[2] = col3;
			eitc_row[3] = col4;
			eitc_row[4] = col5;
			eitc_row[5] = col6;
			eitc_row[6] = col7;
			eitc_row[7] = col8;
			eitc_row[8] = col9;
			eitc_row[9] = col10;
			tax_return->eic_credit = eitc_row[find_eitc_column(tax_return) - 1];
			printf("EIC calculated: %d\n", tax_return->eic_credit);
		}	
	}

	fclose(f);
}

