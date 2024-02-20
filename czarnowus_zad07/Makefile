#
# make: all, clean, tar
#
#=========================================================================
PROG1 = zad7
PROG2 = producent
PROG3 = konsument
LIB = biblioteka_pd
LIB1 = semafory
LIB2 = pamiecdzielona_lib
#==============================================================================
COflags = -Wall -pedantic -pthread
LDflags = -Wall -Werror -pedantic -pthread -fpic
LIBflags = -lrt
CO = g++
LD = g++
DIR = $(notdir $(CURDIR))
#==============================================================================
$(LIB).o: $(LIB1).cpp $(LIB1).hpp $(LIB2).cpp $(LIB2).hpp
	$(LD) $(LDflags) -c $^
	$(LD) -shared -o lib$(LIB).so $(LIB1).o $(LIB2).o

$(PROG1): $(PROG1).cpp $(LIB).o
	$(CO) -L$(CURDIR) -Wl,-rpath=$(CURDIR) $(COflags) -o $@ $< lib$(LIB).so $(LIBflags)

$(PROG2): $(PROG2).cpp $(LIB).o
	$(CO) -L$(CURDIR) -Wl,-rpath=$(CURDIR) $(COflags) -o $@ $< lib$(LIB).so $(LIBflags)
	
$(PROG3): $(PROG3).cpp $(LIB).o
	$(CO) -L$(CURDIR) -Wl,-rpath=$(CURDIR) $(COflags) -o $@ $< lib$(LIB).so $(LIBflags)
#==============================================================================
# Kompilacja i linkowanie calosci
.PHONY: all
all: $(PROG1) $(PROG2) $(PROG3) $(LIB).o
#==============================================================================
# Usuwanie wszystkiego niepotrzebnego
.PHONY: clean tar run
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out *.exe *.in *.out *.hpp.gch zad7 konsument producent; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
# Uruchamianie i porownanie pliku wejscia i wyjscia
run:
	(./zad7 in.txt out.txt; diff -s in.txt out.txt; rm out.txt)
