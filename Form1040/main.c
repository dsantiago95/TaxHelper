#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define SHOW_PRINTS 0

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
#include "Schedule8895.h"
#include "Schedule8863.h"

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

	struct Schedule8863 sch8863;
	initialize_schedule8863(&sch8863);

	struct TaxPayer primary;
	initialize_taxpayer(&primary);
	add_taxpayer(&tax_return, &primary);

	tax_return.status = 1;

	struct Address address = create_address("831 Elizabeth Ave", "Elizabeth", "NJ", "07201");
	add_address(&tax_return, address);

	struct Dependent dependent1;
	initialize_dependent(&dependent1);
	dependent1.odc_qualify = true;
	dependent1.eic_qualify = true;
	add_dependent(&tax_return, &dependent1);

	struct Dependent dependent2;
	initialize_dependent(&dependent2);
	dependent2.odc_qualify = true;
	dependent2.eic_qualify = true;
	add_dependent(&tax_return, &dependent2);

	struct Dependent dependent3;
	initialize_dependent(&dependent3);
	dependent3.ctc_qualify = true;
	dependent3.eic_qualify = true;
	add_dependent(&tax_return, &dependent3);

	add_wage_income(&primary, 12609);
	add_se_income(&primary, 10200);


	//All income assignments are above commit, all calculations are below commit.
	commit_taxpayer(&tax_return, &sch1);


	calculate_additional_income(&sch1);
	calculate_earned_income(&tax_return, &sch1);
	calculate_total_income(&tax_return, sch1);

	calculate_se_tax(&primary, &sch1, &sch2); //must calc before adjustments to income for se_tax_deduction
	calculate_adjustments_to_income(&sch1); //must calc before agi
	calculate_agi(&tax_return, sch1);
	
	set_std_deduction(&tax_return);

	calculate_qbi_deduction(&tax_return, &sch1);

	calculate_taxable_income(&tax_return);

	calculate_tax(&tax_return);

	calculate_ctc_odc(&tax_return, &sch3);

	calculate_aotc_llc(&tax_return, &sch2, 4000);

	calculate_eic(&tax_return);

	printf("compiled!\n");
}
