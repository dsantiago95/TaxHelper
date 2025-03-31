#ifndef SCHEDULE2_H
#define SCHEDULE2_H

#include "Schedule1.h"
#include "TaxPayer.h"

#define MAX_SS_INCOME 168600

struct Schedule2 {
	int excess_ptc;
	double se_tax;
	//a catch-all memeber until other taxes are implemented
	int other_taxes;
};

void initialize_schedule2(struct Schedule2 *sch2);
//Self-employment tax is calculated on a per person basis
void calculate_se_tax(const struct TaxPayer *taxpayer, struct Schedule1 *sch1, struct Schedule2 *sch2);
#endif //SCHEDULE2_H
