OBJS	= vaccineMonitor.o fileHandling.o hashFunctions.o bitArrayFunctions.o bloomFilterFunctions.o skipList.o userCommands.o recordListFunctions.o records.o bloomFilterListFunctions.o skipListListFunctions.o mytok.o dateVaccinatedList.o countryList.o
SOURCE	= vaccineMonitor.c fileHandling.c hashFunctions.c bitArrayFunctions.c bloomFilterFunctions.c skipList.c userCommands.c recordListFunctions.c records.c bloomFilterListFunctions.c skipListListFunctions.c mytok.c dateVaccinatedList.c countryList.c
HEADER	= fileHandling.h hashFunctions.h bitArrayFunctions.h bloomFilterFunctions.h skipList.h userCommands.h recordListFunctions.h records.h bloomFilterListFunctions.h skipListListFunctions.h mytok.h dateVaccinatedList.h countryList.h
OUT	= vaccineMonitor
CC	= gcc
FLAGS	= -g -c -Wall

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

art.o: vaccineMonitor.c
	$(CC) $(FLAGS) vaccineMonitor.c

fileHandling.o: fileHandling.c
	$(CC) $(FLAGS) fileHandling.c

hashFunctions.o: hashFunctions.c
	$(CC) $(FLAGS) hashFunctions.c

bitArrayFunctions.o: bitArrayFunctions.c
	$(CC) $(FLAGS) bitArrayFunctions.c

bloomFilterFunctions.o: bloomFilterFunctions.c
	$(CC) $(FLAGS) bloomFilterFunctions.c

skipList.o: skipList.c
	$(CC) $(FLAGS) skipList.c

userCommands.o: userCommands.c
	$(CC) $(FLAGS) userCommands.c

recordListFunctions.o: recordListFunctions.c
	$(CC) $(FLAGS) recordListFunctions.c

records.o: records.c
	$(CC) $(FLAGS) records.c

bloomFilterListFunctions.o: bloomFilterListFunctions.c
	$(CC) $(FLAGS) bloomFilterListFunctions.c

skipListListFunctions.o: skipListListFunctions.c
	$(CC) $(FLAGS) skipListListFunctions.c

mytok.o: mytok.c
	$(CC) $(FLAGS) mytok.c

dateVaccinatedList.o: dateVaccinatedList.c
	$(CC) $(FLAGS) dateVaccinatedList.c

countryList.o: countryList.c
	$(CC) $(FLAGS) countryList.c

clean:
	rm -f $(OBJS) $(OUT)