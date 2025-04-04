#ifndef F1040_H
#define F1040_H

#include "Address.h"
#include "Schedule1.h"
#include "Schedule2.h"
#include "Schedule3.h"
#include "TaxPayer.h"

#define EITC_TABLE "tables/eitc_table.txt"


#define MAX_DEP 3
#define STD_DED_SINGLE 14600
#define STD_DED_MFJ 29200
#define STD_DED_HOH 21900



struct f1040 {
	int tax_year;
	struct Date filing_date;
	struct TaxPayer *primary_taxpayer;
	struct TaxPayer *spouse;
	int status;
	struct Address address;
	struct Dependent *dependents[MAX_DEP];
	int w2_wages;
	int sch1_additional_income;
	int total_income;
	int earned_income;
	int sch1_adjusments_to_income;
	int agi;
	int std_deduction;
	int itemized_deduction;
	double qbi_deduction;
	int taxable_income;
	int tax;
	int sch2_add_taxes_precredits;
	double ctc_odc_credit;
	int sch3_additional_credits;
	int sch2_other_taxes;
	int total_taxes;
	int w2_payments;
	int f1099_payments;
	int estimated_payments;
	int eic_credit;
	int actc_credit;
	int aotc_credit;
	int total_payments;
};


//Checks for equality member by member
bool returns_are_equal(struct f1040, struct f1040);

//Set int values to zero for easier summation later.
void initialize_tax_return(struct f1040 *, int);

//adds a taxpayer as primary to an empty retrun, a spouse to a tax return
//that already has a primary_taxpayer, and an error to a tax return that
//already has two taxpayers. Initialize TaxPayer members with null.
void add_taxpayer(struct f1040 *, struct TaxPayer *);

void add_souse(struct f1040 *, struct TaxPayer *);

//adds a dependent to the tax return up to the MAX_DEP
void add_dependent(struct f1040 *, struct Dependent *);

void add_address(struct f1040 *, struct Address);

//1 = single
//2 = MFJ
//3 = MFS
//4 = HoH

//void set_status(struct f1040 *tax_return, int status);

//commits taxpayer's income and details to the tax return.
void commit_taxpayer(struct f1040 *, struct Schedule1 *);

//sums income from Schedule 1 and adds to f1040 struct.
void calculate_total_income(struct f1040 *, struct Schedule1);

void calculate_agi(struct f1040 *, struct Schedule1);

void set_std_deduction(struct f1040 *);


void calculate_taxable_income(struct f1040 *);

void calculate_earned_income(struct f1040 *, struct Schedule1 *);

void calculate_tax(struct f1040 *);

void calculate_additional_precredit_tax(struct f1040 *, struct Schedule2);


void calculate_other_credits(struct f1040 *, struct Schedule3);

void calculate_other_taxes(struct f1040 *, struct Schedule2);

void calculate_total_taxes(struct f1040 *);

//W-2 and 1099 withholdings, estimated payments
void calculate_payments(struct f1040 *);

int find_eitc_comumn(struct f1040 *);

void calculate_eic(struct f1040 *);



void calculate_total_payments(struct f1040 *, struct Schedule3);

void calculate_final_result(struct f1040 *);


#endif //F1040_H
