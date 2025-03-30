#inlcude "Schedule8863.h"

//currently does not calculate Lifetime Learners Credit, assumed to qualify for AOTC
void calucalte_aotc_llc(struct f1040 *tax_return, int total_expenses)
{
	int max_credit 
	double = total_expenses - 2000;
	if (max_credit < 0)
	{
		max_credit = 0;
	}
	double interim_calc = max_credit * 0.25;
	max_credit += interim_calc;
}
