#include <stdio.h>
#include "Schedule8895.h"


void calculate_qbi_deduction(struct f1040 *tax_return, struct Schedule1 *sch1)
{
	int qbi = sch1->business_income - sch1->se_tax_deduction;
	double qbi_component = qbi * 0.2;
	int taxable_income_before_qbi = tax_return->agi - tax_return->std_deduction;
	double income_limit = taxable_income_before_qbi * 0.2;
	if (income_limit > qbi_component)
	{
		tax_return->qbi_deduction = qbi_component;
		printf("Calculated QBI deduction: %.2f\n", tax_return->qbi_deduction);
		return;
	} else {
		tax_return->qbi_deduction = income_limit;
		printf("Calculated QBI deduction: %.2f\n", tax_return->qbi_deduction);
		return;
	}
}
