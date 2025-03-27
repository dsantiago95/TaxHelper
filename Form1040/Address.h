
struct Address {
	char street_address[35+1];
	char city[35+1];
	char state[2+1]; //state abbreviation, i.e. "NJ"
	char zip_code[5+1];
};

struct Address create_address(char street[35+1], char city[35+1], char state[2+1], char zip[5+1]);
