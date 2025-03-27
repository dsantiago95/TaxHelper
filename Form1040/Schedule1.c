#include <stdio.h>

#include "Schedule1.h"

void initialize_schedule1(struct Schedule1 *schedule)
{

	schedule->business_income = 0; //negative if loss
	schedule->rental_income = 0;
	schedule->unemployment_comp = 0;
	schedule->additional_income = 0;  // 2024TY: line 10

	schedule->se_tax_deduction = 0;
	schedule->adjustments_to_income = 0; // 2024TY: line 26
	printf("Schedule 1 initialized.\n");
}

void calculate_additional_income(struct Schedule1 *schedule)
{
	schedule->additional_income += schedule->rental_income;
	schedule->additional_income += schedule->business_income;
}
