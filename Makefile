include makeinclude

OBJ	= main.o

all: coreunreg

coreunreg: $(OBJ)
	$(LD) $(LDFLAGS) -o coreunreg $(OBJ) $(LIBS)

clean:
	rm -f *.o
	rm -f coreunreg

makeinclude:
	@echo please run ./configure
	@false

SUFFIXES: .cpp .o
.cpp.o:
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $<
