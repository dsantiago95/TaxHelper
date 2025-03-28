#include <stdio.h>

//Consider making a struct to hold line items for when generating pdfs

#include "Date.h"
#include "f1040.h"
#include "Dependent.h"
#include "Schedule3.h"
#include "Schedule8812.h"

int ceiling_1000(int x)
{
	if (x % 1000 == 0)
	{
		return x;
	}

	return (x + (1000 - (x % 1000)));
}

int credit_limit_wk_a(const struct f1040 *tax_return, const struct Schedule3 *sch3)
{
	int total_precredit_taxes = tax_return->tax + tax_return->sch2_add_taxes_precredits;
	int limit = total_precredit_taxes - sch3->nonrefundable_credits;
	if (limit < 0)
	{
		return 0;
	} else {
		return limit;
	}
}

void calculate_ctc_odc(struct f1040 *tax_return, struct Schedule3 *sch3)
{
	int num_ctc = 0;
	int num_odc = 0;
	for (int i = 0; i < MAX_DEP; i++)
	{
		if (tax_return->dependents[i] != NULL)
		{
			if (tax_return->dependents[i]->ctc_qualify)
			{
				num_ctc++;
			}
			if (tax_return->dependents[i]->odc_qualify)
			{
				num_odc++;
			}
		}
	}	

	//2024TY: line 8
	int total_ctc_odc = (num_ctc * CTC_AMOUNT) + (num_odc * ODC_AMOUNT);

	int filing_status_limit = 0;
	if (tax_return->status == 2)
	{
		filing_status_limit = 400000;
	} else {
		filing_status_limit = 200000;
	}

	int agi_limit_diff = tax_return->agi - filing_status_limit;
	if (agi_limit_diff < 0)
	{
		agi_limit_diff = 0;
	}
	if (agi_limit_diff % 1000 != 0)
	{
		agi_limit_diff = ceiling_1000(agi_limit_diff);
	}

	//2024TY: line 11
	int phase_out = agi_limit_diff * 0.05;
	
	if (total_ctc_odc > phase_out)
	{
		total_ctc_odc = total_ctc_odc - phase_out;
		if (total_ctc_odc > credit_limit_wk_a(tax_return, sch3))
		{
			tax_return->ctc_odc_credit = credit_limit_wk_a(tax_return, sch3);
			printf("Calculating CTC and ODC amount: %d\n", tax_return->ctc_odc_credit);
			return;
		} else {
			tax_return->ctc_odc_credit = total_ctc_odc;
			printf("Calculating CTC and ODC amount: %d\n", tax_return->ctc_odc_credit);
			return;
		}
	} else {
		printf("Do not qualify for refundable CTC or ODC.\n");
		return;
	}
}


void calculate_actc(struct f1040 *tax_return)
{

}
