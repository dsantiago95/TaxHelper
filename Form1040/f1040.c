#include <stdio.h>
#include <stdbool.h>
#include <string.h>


#define MAX_DEP 3

struct Date {
	char month[2];
	char day[2];
	char year[4];
};

struct Address {
	char street_address[35];
	char city[35];
	char state[2]; //state abbreviation, i.e. "NJ"
	char zip_code[5];
};

struct Address create_address(char street[35], char city[35], char state[2], char zip[5]);

struct TaxPayer {
	char name[35];
	struct Date dob;
	int w2_wages;
	int rental_income;
	int se_income; //Sch C, Sch E pg2
	bool eic_qualify;
};

void initialize_taxpayer(struct TaxPayer *taxpayer);

struct Dependent {
	char name[35];
	struct Date dob;
	bool ctc_qualify;
	bool odc_qualify;
	bool eic_qualify;
};

void initialize_dependent(struct Dependent *dep);

struct f1040 {
	int tax_year;
	struct Date filing_date;
	struct TaxPayer *primary_taxpayer;
	struct TaxPayer *spouse;
	struct Address *address;
	struct Dependent *dependents[MAX_DEP];
	int w2_wages;
	int sch1_additional_income;
	int total_income;
	int sch1_adjusments_to_income;
	int agi;
	int std_deduction;
	int itemized_deduction;
	int qbi_deduction;
	int taxable_income;
	int tax;
	int sch2_add_taxes_precredits;
	int ctc_credit;
	int odc_credit;
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

struct Schedule1 {
	int business_income; //negative if loss
	int rental_income;
	int unemployment_comp;
	//a catch-all member until other tax types are implemented
	int other_additional_income; 

	int se_tax_deduction;
	//a catch-all member until other deduction types are implemented
	int other_deductions;
};

struct Schedule2 {
	int excess_ptc;
	int se_tax;
	//a catch-all memeber until other taxes are implemented
	int other_taxes;
};

//bare minimum implentation of Sch3, will need to be expanded
struct Schedule3 {
	int nonrefundable_credits;
	int refundable_credits;
};

//Set int values to zero for easier summation later.
void initialize_tax_return(struct f1040 *tax_return, int year);

//adds a taxpayer as primary to an empty retrun, a spouse to a tax return
//that already has a primary_taxpayer, and an error to a tax return that
//already has two taxpayers. Initialize TaxPayer members with null.
void add_taxpayer(struct f1040 *tax_return, struct TaxPayer taxpayer);

//adds a dependent to the tax return up to the MAX_DEP
void add_dependent(struct f1040 *tax_return, struct Dependent dependent);

void add_address(struct f1040 *tax_return, struct Address address);

//sums income from Schedule 1 and adds to f1040 struct.
void calculate_total_income(struct f1040 *tax_return, struct Schedule1 schedule);

void calculate_agi(struct f1040 *tax_return, struct Schedule1 schedule);

void set_std_deduction(struct f1040 *tax_return, int status);

//Form 8995
void calculate_qbi(struct f1040 *tax_return);

void calculate_taxable_income(struct f1040 *tax_return);

void calculate_tax(struct f1040 *tax_return);

void calculate_additional_precredit_tax(struct f1040 *tax_return, struct Schedule2 schedule);

//Form 8812
void calculate_ctc(struct f1040 *tax_return);

void calculate_other_credits(struct f1040 *tax_return, struct Schedule3 schedule);

void calculate_other_taxes(struct f1040 *tax_return, struct Schedule2 schedule);

void calculate_total_taxes(struct f1040 *tax_return);

//W-2 and 1099 withholdings, estimated payments
void calculate_payments(struct f1040 *tax_return);

void calculate_eic(struct f1040 *tax_return);

void calculate_actc(struct f1040 *tax_return);

void calculate_aotc(struct f1040 *tax_return);

void calculate_total_payments(struct f1040 *tax_return, struct Schedule3 schedule);

void calculate_final_result(struct f1040 *tax_return);


//-----------*-*-*-------------------------*-*-*--------------------\\

void initialize_tax_return(struct f1040 *tax_return, int tax_year)
{
	tax_return->tax_year = tax_year;
	tax_return->primary_taxpayer = NULL;
	tax_return->spouse = NULL;
	tax_return->w2_wages = 0;
	tax_return->sch1_additional_income = 0;
	tax_return->total_income = 0;
	tax_return->sch1_adjusments_to_income = 0;
	tax_return->agi = 0;
	tax_return->std_deduction = 0;
	tax_return->itemized_deduction = 0;
	tax_return->qbi_deduction = 0;
	tax_return->taxable_income = 0;
	tax_return->tax = 0;
	tax_return->sch2_add_taxes_precredits = 0;
	tax_return->ctc_credit = 0;
	tax_return->odc_credit = 0;
	tax_return->sch3_additional_credits = 0;
	tax_return->sch2_other_taxes = 0;
	tax_return->total_taxes = 0;
	tax_return->w2_payments = 0;
	tax_return->f1099_payments = 0;
	tax_return->estimated_payments = 0;
	tax_return->eic_credit = 0;
	tax_return->actc_credit = 0;
	tax_return->aotc_credit = 0;
}

void initialize_dependent(struct Dependent *dep)
{
	dep->ctc_qualify = false;
	dep->odc_qualify = false;
	dep->eic_qualify = false;
}

void initialize_taxpayer(struct TaxPayer *taxpayer)
{
	taxpayer->w2_wages = 0;
	taxpayer->rental_income = 0;
	taxpayer->se_income = 0; //Sch C, Sch E pg2
	taxpayer->eic_qualify = false;
}

void add_taxpayer(struct f1040 *tax_return, struct TaxPayer taxpayer)
{
	if (tax_return->primary_taxpayer == NULL)
	{
		tax_return->primary_taxpayer = &taxpayer;
		return;
	} else if (tax_return->primary_taxpayer != NULL & tax_return->spouse == NULL)
	{
		tax_return->spouse = &taxpayer;
		return;
	}
	printf("Already 2 taxpayers on the return.\n");
	return;
}


struct Address create_address(char street[35], char city[35], char state[2], char zip[5])
{
	struct Address return_add;
	strcpy(return_add.street_address, street);
	strcpy(return_add.city, city);
	strcpy(return_add.state, state);
	strcpy(return_add.zip_code, zip);
	return return_add;
}

void add_address(struct f1040 *tax_return, struct Address address)
{
	if (tax_return->address == NULL)
	{
		tax_return->address = &address;
		return;
	} 
	printf("Address already assigned. No change.");
	return;
}

void add_dependent(struct f1040 *tax_return, struct Dependent dependent)
{
	for (int i = 0; i < MAX_DEP; i++;)
	{
		if (tax_return->dependents[i] != NULL)
		{
			tax_return->dependents[i] = dependent;
			return;
		}
	}
	printf("Max number of dependents already present. No changes\n");
	return;
}
int main()
{
	struct f1040 tax_return;
	initialize_tax_return(&tax_return, 2024);

	struct TaxPayer primary;
	initialize_taxpayer(&primary);
	add_taxpayer(&tax_return, primary);

	struct Dependent dependent;
	initialize_dependent(&dependent);

	struct Address address = create_address("831 Elizabeth Ave", "Elizabeth", "NJ", "07201");
	add_address(&tax_return, address);

	printf("compiled!\n");
}
