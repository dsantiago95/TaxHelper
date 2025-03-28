#ifndef SCHEDULE8812_H
#define SCHEDULE8812_H

#include "f1040.h"
#include "Schedule3.h"

//Form 8812
int credit_limit_wk_a(const struct f1040 *, const struct Schedule3 *);

void calculate_ctc_odc(struct f1040 *, struct Schedule3 *);

void calculate_aotc(struct f1040 *);

#endif //SCHEDULE8812_H
