#include <stdbool.h>

#include "Date.h"

struct Dependent {
	bool is_initialized;
	char name[35+1];
	struct Date dob;
	bool ctc_qualify;
	bool odc_qualify;
	bool eic_qualify;
};

void initialize_dependent(struct Dependent *dep);
