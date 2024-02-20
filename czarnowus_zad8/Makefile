#
# make: all, clean, tar, run
#
#=========================================================================
PROG1 = klient
PROG2 = serwer
LIB = kolejki
#==============================================================================
COflags = -Wall -pedantic -pthread
LDflags = -Wall -Werror -pedantic -pthread -fpic
LIBflags = -lrt
CO = g++
LD = g++
DIR = $(notdir $(CURDIR))
#==============================================================================
$(LIB).o: $(LIB).cpp $(LIB).hpp
	$(LD) $(LDflags) -c $^
	$(LD) -shared -o lib$(LIB).so $(LIB).o

$(PROG1): $(PROG1).cpp $(LIB).o
	$(CO) -L$(CURDIR) -Wl,-rpath=$(CURDIR) $(COflags) -o $@ $< lib$(LIB).so $(LIBflags)

$(PROG2): $(PROG2).cpp $(LIB).o
	$(CO) -L$(CURDIR) -Wl,-rpath=$(CURDIR) $(COflags) -o $@ $< lib$(LIB).so $(LIBflags)
#==============================================================================
# Kompilacja i linkowanie calosci
.PHONY: all
all: $(PROG1) $(PROG2) $(LIB).o
#==============================================================================
# Usuwanie wszystkiego niepotrzebnego
.PHONY: clean tar run
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out *.exe *.in *.out *.hpp.gch klient serwer; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )
# Odpal program
run: 
	xterm -hold -title SERWER -bg red -fg black -e ./serwer &
	xterm -hold -title KLIENT -bg green -fg black -e ./klient &
	xterm -hold -title KLIENT -bg green -fg black -e ./klient &
