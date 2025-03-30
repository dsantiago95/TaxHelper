#ifndef SCHEDULE1_H
#define SCHEDULE1_H

struct Schedule1 {
	int business_income; //negative if loss
	int rental_income;
	int unemployment_comp;
	int additional_income;  // 2024TY: line 10

	double se_tax_deduction;
	int adjustments_to_income; // 2024TY: line 26
};

void initialize_schedule1(struct Schedule1 *);

void calculate_additional_income(struct Schedule1 *);

void calculate_adjustments_to_income(struct Schedule1 *);
#endif //SCHEDULE1_H
