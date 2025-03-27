#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "Date.h"
#include "TaxPayer.h"
#include "Address.h"
#include "Brackets.h"
#include "Dependent.h"
#include "Schedule1.h"
#include "Schedule2.h"
#include "Schedule3.h"

#define EITC_TABLE "tables/eitc_table.txt"

#define CTC_AMOUNT 2000
#define ODC_AMOUNT 500

#define MAX_DEP 3
#define STD_DED_SINGLE 14600
#define STD_DED_MFJ 29200
#define STD_DED_HOH 21900


struct Brackets brackets;

struct f1040 {
	int tax_year;
	struct Date filing_date;
	//struct TaxPayer *primary_taxpayer;
	//struct TaxPayer *spouse;
	int status;
	struct Address *address;
	struct Dependent *dependents[MAX_DEP];
	int w2_wages;
	int sch1_additional_income;
	int total_income;
	int sch1_adjusments_to_income;
	int agi;
	int std_deduction;
	int itemized_deduction;
	int qbi_deduction;
	int taxable_income;
	int tax;
	int sch2_add_taxes_precredits;
	int ctc_credit;
	int odc_credit;
	int sch3_additional_credits;
	int sch2_other_taxes;
	int total_taxes;
	int w2_payments;
	int f1099_payments;
	int estimated_payments;
	int eic_credit;
	int actc_credit;
	int aotc_credit;
	int total_payments;
};




//Set int values to zero for easier summation later.
void initialize_tax_return(struct f1040 *tax_return, int year);

//adds a taxpayer as primary to an empty retrun, a spouse to a tax return
//that already has a primary_taxpayer, and an error to a tax return that
//already has two taxpayers. Initialize TaxPayer members with null.
//void add_taxpayer(struct f1040 *tax_return, struct TaxPayer taxpayer);

//adds a dependent to the tax return up to the MAX_DEP
void add_dependent(struct f1040 *tax_return, struct Dependent *dependent);

void add_address(struct f1040 *tax_return, struct Address address);

/*******\
1 = single
2 = MFJ
3 = MFS
4 = HoH
/*******/
//void set_status(struct f1040 *tax_return, int status);

//commits taxpayer's income and details to the tax return.
void commit_taxpayer(struct f1040 *tax_return, struct Schedule1 *schedule, struct TaxPayer taxpayer);

//sums income from Schedule 1 and adds to f1040 struct.
void calculate_total_income(struct f1040 *tax_return, struct Schedule1 schedule);

void calculate_agi(struct f1040 *tax_return, struct Schedule1 schedule);

void set_std_deduction(struct f1040 *tax_return);

//Form 8995
void calculate_qbi(struct f1040 *tax_return);

void calculate_taxable_income(struct f1040 *tax_return);

void calculate_tax(struct f1040 *tax_return);

void calculate_additional_precredit_tax(struct f1040 *tax_return, struct Schedule2 schedule);

//Form 8812
void calculate_ctc(struct f1040 *tax_return);

void calculate_odc(struct f1040 *tax_return);

void calculate_other_credits(struct f1040 *tax_return, struct Schedule3 schedule);

void calculate_other_taxes(struct f1040 *tax_return, struct Schedule2 schedule);

void calculate_total_taxes(struct f1040 *tax_return);

//W-2 and 1099 withholdings, estimated payments
void calculate_payments(struct f1040 *tax_return);

int find_eitc_comumn(struct f1040 *tax_return);

void calculate_eic(struct f1040 *tax_return);

void calculate_actc(struct f1040 *tax_return);

void calculate_aotc(struct f1040 *tax_return);

void calculate_total_payments(struct f1040 *tax_return, struct Schedule3 schedule);

void calculate_final_result(struct f1040 *tax_return);


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
	tax_return->ctc_credit = 0;
	tax_return->odc_credit = 0;
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

void calculate_ctc(struct f1040 *tax_return)
{
	if (tax_return->status == 2 && tax_return->total_income >= 400000)
	{
		printf("Does not qualify for CTC.\n");
		return;
	}
	else if (tax_return->total_income >= 200000)
	{
		printf("Does not qualify for CTC.\n");
		return;
	}

	int num_ctc = 0;
	for (int i = 0; i < MAX_DEP; i++)
	{
		if (tax_return->dependents[i] != NULL)
		{
			if (tax_return->dependents[i]->ctc_qualify)
			{
				num_ctc++;
			}
		}
	}	
	printf("Calculating CTC amount: %d\n", num_ctc * CTC_AMOUNT);
	tax_return->ctc_credit =  num_ctc * CTC_AMOUNT;
}

void calculate_odc(struct f1040 *tax_return)
{
	int num_odc = 0;
	for (int i = 0; i < MAX_DEP; i++)
	{
		if (tax_return->dependents[i]->odc_qualify)
		{
			num_odc++;
		}
	}	
	printf("Calculating ODC amount: %d\n", num_odc * ODC_AMOUNT);
	tax_return->odc_credit = num_odc * ODC_AMOUNT;
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

		if (tax_return->total_income >= col1 & tax_return->total_income < col2)
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

int main()
{
	struct f1040 tax_return;
	initialize_tax_return(&tax_return, 2024);

	read_brackets();
	
	struct Schedule1 sch1;
	initialize_schedule1(&sch1);

	struct Schedule2 sch2;
	initialize_schedule2(&sch2);

	struct TaxPayer primary;
	initialize_taxpayer(&primary);
	//add_taxpayer(&tax_return, primary);

	tax_return.status = 1;

	struct Dependent dependent;
	initialize_dependent(&dependent);
	dependent.ctc_qualify = true;
	dependent.eic_qualify = true;
	add_dependent(&tax_return, &dependent);

	struct Address address = create_address("831 Elizabeth Ave", "Elizabeth", "NJ", "07201");
	add_address(&tax_return, address);

	add_wage_income(&primary, 40000);
	add_se_income(&primary, 25000);
	commit_taxpayer(&tax_return, &sch1, primary);
	calculate_additional_income(&sch1);
	calculate_total_income(&tax_return, sch1);
	calculate_agi(&tax_return, sch1);
	
	set_std_deduction(&tax_return);

	calculate_taxable_income(&tax_return);

	calculate_tax(&tax_return);

	calculate_se_tax(&primary, &sch1, &sch2);

	calculate_ctc(&tax_return);

	calculate_eic(&tax_return);

	printf("compiled!\n");
}
