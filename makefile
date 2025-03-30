main: Form1040/main.o Form1040/f1040.o Form1040/TaxPayer.o Form1040/Address.o Form1040/Brackets.o Form1040/Dependent.o Form1040/Schedule1.o Form1040/Schedule2.o Form1040/Schedule8812.o Form1040/Schedule3.o Form1040/Schedule8895.o
	gcc -g -o main Form1040/main.o Form1040/f1040.o Form1040/TaxPayer.o Form1040/Address.o Form1040/Brackets.o Form1040/Dependent.o Form1040/Schedule1.o Form1040/Schedule2.o Form1040/Schedule8812.o Form1040/Schedule3.o Form1040/Schedule8895.o

main.o: Form1040/main.c Form1040/f1040.c Form1040/TaxPayer.h Form1040/Address.h Form1040/Brackets.h Form1040/Dependent.h Form1040/Schedule1.h Form1040/Schedule2.h Form1040/Schedule3.h Form1040/Schedule8812.h
	gcc -g -c Form1040/main.c

f1040.o: Form1040/f1040.c Form1040/TaxPayer.h Form1040/Address.h Form1040/Brackets.h Form1040/Dependent.h Form1040/Schedule1.h Form1040/Schedule2.h Form1040/Schedule3.h Form1040/Schedule8812.h
	gcc -g -c Form1040/f1040.c

TaxPayer.o: Form1040/TaxPayer.c Form1040/TaxPayer.h Form1040/Date.h
	gcc -g -c Form1040/TaxPayer.c

Address.o: Form1040/Address.c Form1040/Address.h
	gcc -g -c Form1040/Address.c

Brackets.o: Form1040/Brackets.c Form1040/Brackets.h
	gcc -g -c Form1040/Brackets.c

Dependent.o: Form1040/Dependent.c Form1040/Dependent.h Form1040/Date.h
	gcc -g -c Form1040/Dependent.c

Schedule3.o: Form1040/Schedule3.c Form1040/Schedule3.h
	gcc -g -c Form1040/Schedule3.c

Schedule8812.o: Form1040/Schedule8812.c  Form1040/Schedule8812.h Form1040/Schedule3.h
	gcc -g -c Form1040/Schedule8812.c

Schedule8895.o: Form1040/Schedule8895.c Form1040/Schedule8895.h Form1040/f1040.h Form1040/Schedule1.h
	gcc -g -c Form1040/Schedule8895.c

Schedule1.o: Form1040/Schedule1.c Form1040/Schedule.h 
	gcc -g -c Form1040/Schedule1.c

Schedule2.o: Form1040/Schedule2.c Form1040/Schedule2.h Form1040/TaxPayer.h
	gcc -g -c Form1040/Schedule2.c

clean:
	rm Form1040/*.o
