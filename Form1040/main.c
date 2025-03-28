#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "Date.h"
#include "TaxPayer.h"
#include "Address.h"
#include "Brackets.h"
#include "Dependent.h"
#include "f1040.h"
#include "Schedule8812.h"
#include "Schedule1.h"
#include "Schedule2.h"
#include "Schedule3.h"

struct Brackets brackets;

int main()
{
	struct f1040 tax_return;
	initialize_tax_return(&tax_return, 2024);

	read_brackets();
	
	struct Schedule1 sch1;
	initialize_schedule1(&sch1);

	struct Schedule2 sch2;
	initialize_schedule2(&sch2);

	struct Schedule3 sch3;
	initialize_schedule3(&sch3);

	struct TaxPayer primary;
	initialize_taxpayer(&primary);
	//add_taxpayer(&tax_return, primary);

	tax_return.status = 1;

	struct Dependent dependent;
	initialize_dependent(&dependent);
	dependent.ctc_qualify = true;
	dependent.eic_qualify = true;
	add_dependent(&tax_return, &dependent);

	struct Address address = create_address("831 Elizabeth Ave", "Elizabeth", "NJ", "07201");
	add_address(&tax_return, address);

	add_wage_income(&primary, 40000);
	add_se_income(&primary, 25000);
	commit_taxpayer(&tax_return, &sch1, primary);
	calculate_additional_income(&sch1);
	calculate_total_income(&tax_return, sch1);
	calculate_agi(&tax_return, sch1);
	
	set_std_deduction(&tax_return);

	calculate_taxable_income(&tax_return);

	calculate_tax(&tax_return);

	calculate_se_tax(&primary, &sch1, &sch2);

	calculate_ctc_odc(&tax_return, &sch3);

	calculate_eic(&tax_return);

	printf("compiled!\n");
}
