#
# make: all, clean, tar, run
#
#=========================================================================
DIR = `basename $(CURDIR)`
#------------------------
NAME1 = zad4
NAME2 = konsument
#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
#----------------------
EXEC2 = $(NAME2)
OBJS2 = $(NAME2).o
#############################
COFLAGS = -Wall -O
LDFLAGS = -Wall -O
CO = g++
LD = $(CO)
#############################
%.o: %.cpp
	$(CO) $(COFLAGS) -c $<
#############################
.PHONY: all
all: $(EXEC1) $(EXEC2)
#############################
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC2): $(OBJS2)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
.PHONY: clean tar
# Porzadki
EXECS = $(EXEC1) $(EXEC2)
clean:                                                     
	rm -f *.o  *~ $(EXECS)
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================
# Uruchamianie i porownanie pliku wejscia i wyjscia
run:
	(./zad4 in.txt out.txt; diff -s in.txt out.txt; rm out.txt)
#=========================================================================
