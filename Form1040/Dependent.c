#include <stdio.h>

#include "Dependent.h"

void initialize_dependent(struct Dependent *dep)
{
	dep->ctc_qualify = false;
	dep->odc_qualify = false;
	dep->eic_qualify = false;
	dep->is_initialized = false;

	printf("Dependent initialized successfuly.\n");
}
