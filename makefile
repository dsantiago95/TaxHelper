main: Form1040/f1040.o Form1040/TaxPayer.o Form1040/Address.o Form1040/Brackets.o Form1040/Dependent.o Form1040/Schedule1.o Form1040/Schedule2.o
	gcc -o main Form1040/f1040.o Form1040/TaxPayer.o Form1040/Address.o Form1040/Brackets.o Form1040/Dependent.o Form1040/Schedule1.o Form1040/Schedule2.o

f1040.o: Form1040/f1040.c Form1040/TaxPayer.h Form1040/Address.h Form1040/Brackets.h Form1040/Dependent.h Form1040/Schedule1.h Form1040/Schedule2.h Form1040/Schedule3.h
	gcc -c Form1040/f1040.c

TaxPayer.o: Form1040/TaxPayer.c Form1040/TaxPayer.h Form1040/Date.h
	gcc -c Form1040/TaxPayer.c

Address.o: Form1040/Address.c Form1040/Address.h
	gcc -c Form1040/Address.c

Brackets.o: Form1040/Brackets.c Form1040/Brackets.h
	gcc -c Form1040/Brackets.c

Dependent.o: Form1040/Dependent.c Form1040/Dependent.h Form1040/Date.h
	gcc -c Form1040/Dependent.c

Schedule1.o: Form1040/Schedule1.c Form1040/Schedule.h 
	gcc -c Form1040/Schedule1.c

Schedule2.o: Form1040/Schedule2.c Form1040/Schedule2.h Form1040/TaxPayer.h
	gcc -c Form1040/Schedule2.c

clean:
	rm Form1040/*.o
