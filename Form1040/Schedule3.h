#ifndef SCHEDULE3_H
#define SCHEDULE3_H

//bare minimum implentation of Sch3, will need to be expanded
struct Schedule3 {
	int nonrefundable_credits;
	int refundable_credits;
};

void initialize_schedule3(struct Schedule3 *);

#endif //SCHEDULE3_H
