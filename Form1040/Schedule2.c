#include <stdio.h>

#include "Schedule2.h"
#include "TaxPayer.h"

void initialize_schedule2(struct Schedule2 *schedule)
{
	schedule->excess_ptc = 0;
	schedule->se_tax = 0;
	//a catch-all memeber until other taxes are implemented
	schedule->other_taxes = 0;
}

void calculate_se_tax(const struct TaxPayer *taxpayer, struct Schedule1 *sch1, struct Schedule2 *sch2)
{
	if (taxpayer->se_income < 400)
	{
		printf("No self-employment tax due.\n");
		return;
	}

	//92.35% is a const from IRS, removes 7.65% of employee share of FICA.
	int employer_portion_se_income = taxpayer->se_income * 0.9235;

	//Have to check that combined se_income and W2 wages subject to se tax
	//doesn't go over max income subject to social security tax.
	
	int se_income_less_wages = MAX_SS_INCOME;

	if (employer_portion_se_income + taxpayer->w2_wages > MAX_SS_INCOME)
	{
		se_income_less_wages = MAX_SS_INCOME - taxpayer->w2_wages;
	}

	int income_subject_se_tax = 0;
	double se_tax;
	
	if (employer_portion_se_income <= se_income_less_wages)
	{
		income_subject_se_tax = employer_portion_se_income;
	}
	else
	{
		income_subject_se_tax = se_income_less_wages;
	}	

	se_tax = (income_subject_se_tax * 0.124) + (employer_portion_se_income * .029);
	sch2->se_tax += se_tax;
	printf("Calcualted self-employment tax: %d\n", (int)sch2->se_tax);
	sch1->se_tax_deduction += se_tax * .5;
	printf("Calcualted deductible portion of self-employment tax: %d\n", (int)sch1->se_tax_deduction);

}
