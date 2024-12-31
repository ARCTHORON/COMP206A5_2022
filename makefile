all: mini5main.o mini5phone.o
	gcc -o mini5main mini5main.o mini5phone.o

mini5main.o: mini5main.c mini5phone.h
	gcc -c mini5main.c

mini5phone.o: mini5phone.c
	gcc -c mini5phone.c


