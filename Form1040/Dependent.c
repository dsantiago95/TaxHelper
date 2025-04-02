#include <stdio.h>

#include "Dependent.h"

bool dependents_are_equal(struct Dependent d1, struct Dependent d2)
{
	if (d1.ctc_qualify != d2.ctc_qualify)
	{
		return false;
	}
	if (d1.odc_qualify != d2.odc_qualify)
	{
		return false;
	}
	if (d1.eic_qualify != d2.eic_qualify)
	{
		return false;
	}

	return true;
}
void initialize_dependent(struct Dependent *dep)
{
	dep->ctc_qualify = false;
	dep->odc_qualify = false;
	dep->eic_qualify = false;
	dep->is_initialized = false;

	printf("Dependent initialized successfuly.\n");
}
