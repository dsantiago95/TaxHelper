#include <stdio.h>
#include "Schedule8863.h"

void initialize_schedule8863(struct Schedule8863 *sch) {
	sch->refundable_credit = 0;
	sch->nonrefundable_credit = 0;
}

void credit_limit_wk(struct f1040 *tax_return, struct Schedule2 *sch2)
{
	int total_tax = tax_return->tax + sch2->other_taxes;
	if (schedule.nonrefundable_credit > total_tax)
	{
		schedule.nonrefundable_credit = total_tax;
		printf("Calculated nonrefundable portion of AOTC: %d\n", schedule.nonrefundable_credit);
	}
}

//currently does not calculate Lifetime Learners Credit, assumed to qualify for AOTC
void calculate_aotc_llc(struct f1040 *tax_return, struct Schedule2 *sch2, int total_expenses)
{
	//Part III
	//
	//2024TY: line 27
	if (total_expenses > 4000)
	{
		total_expenses = 4000;
	}
	//2024TY: line 28
	double credit = total_expenses - 2000;
	if (credit < 0)
	{
		credit = 0;
	}
	
	//2024TY: line 29
	double interim_calc = credit * 0.25;

	int max_credit;
	if (credit == 0)
	{
		max_credit = total_expenses;
	} else {
		max_credit = 2000 + interim_calc;
	}

	//Part I
	//
	int threshold;
	if (tax_return->status == 2)	
	{
		threshold = MFJ_THRESHOLD;
	} else {
		threshold = SINGLE_THRESHOLD;
	}

	int diff = threshold - tax_return->agi;
	if (diff <= 0)
	{
		printf("Do not qualify for AOTC. Over income limit.\n");
	}
	
	int smaller_threshold;

	if (tax_return->status == 2)
	{
		smaller_threshold = 20000;
	} else {
		smaller_threshold = 10000;
	}

	double factor;
	if (diff >= smaller_threshold)
	{
		factor = 1.0;
	} else {
		factor = smaller_threshold/diff;
	}

	//Must add age check here. Likely have to add taxpayer back to f1040 struct.
	//2024TY: line 7
	double total_credit = max_credit * factor;

	//2024TY: line 8
	schedule.refundable_credit = total_credit * 0.4;
	printf("Calculated refundable portion of AOTC: %d\n", schedule.refundable_credit);

	schedule.nonrefundable_credit =  total_credit - schedule.refundable_credit;

	credit_limit_wk(tax_return, sch2);
}
