#ifndef SCHEDULE8812_H
#define SCHEDULE8812_H

#include "f1040.h"
#include "Schedule3.h"

#define ACTC_AMOUNT 1700
#define CTC_AMOUNT 2000
#define ODC_AMOUNT 500

//Form 8812
int credit_limit_wk_a(const struct f1040 *, const struct Schedule3 *);

void calculate_ctc_odc(struct f1040 *, struct Schedule3 *);

void calculate_actc(struct f1040 *);

#endif //SCHEDULE8812_H
