#
# make: all, clean, tar
#
#=========================================================================
DIR = `basename $(CURDIR)`
#------------------------
NAME1 = zad5
NAME2 = prod
NAME3 = kons
#----------------------
EXEC1 = $(NAME1)
OBJS1 = $(NAME1).o
#----------------------
EXEC2 = $(NAME2)
OBJS2 = $(NAME2).o
#----------------------
EXEC3 = $(NAME3)
OBJS3 = $(NAME3).o
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
all: $(EXEC1) $(EXEC2) $(EXEC3)
#############################
$(EXEC1): $(OBJS1)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC2): $(OBJS2)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
$(EXEC3): $(OBJS3)
	 $(LD) -o $@ $(LDFLAGS) $^
#############################
.PHONY: clean tar
# Porzadki
EXECS = $(EXEC1) $(EXEC2) $(EXEC3)
clean:                                                     
	rm -f *.o  *~ $(EXECS) out.txt potok
#=========================================================================
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
#=========================================================================
