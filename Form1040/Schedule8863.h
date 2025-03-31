#ifndef SCHEDULE8863_H
#define SCHEDULE8863_H

#include "f1040.h"

#define MFJ_THRESHOLD 180000
#define SINGLE_THRESHOLD 90000

struct Schedule8863 {
	int refundable_credit;
	int nonrefundable_credit;
} schedule;

void initialize_schedule8863(struct Schedule8863 *);

void calculate_aotc_llc(struct f1040 *, struct Schedule2 *, int);
#endif //SCHEDULE8863_H
