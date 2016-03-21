# Header files
HEADERS = \
	../include/exceptional.hpp

# g++ options
GCC = g++ -std=c++14

# g++ compiling flags
GCC-CFLAGS = -c -Wall -Wextra -Wmissing-declarations -Werror

# g++ linking flags
GCC-LFLAGS = -Wall -Wextra -Wmissing-declarations -Werror

# Clang compilation options
CLANG = clang++-3.5 -std=c++14 -Werror -fshow-source-location -fshow-column -fcaret-diagnostics -fcolor-diagnostics -fdiagnostics-show-option

# Output filename
OUTPUT = tests

#####
###
#
# 'Make' commands
#
###
#####

# $ 'make' or 'make help'
help:
	@echo "INSTRUCTIONS:"
	@echo "  To test exceptional with g++, run: make tests"
	@echo "  To test exceptional with clang, run: make tests-clang"
	@echo "  To remove compiled output files, run: make clean"

# Executed whenever an object file is out of date
# Symbols:
#   % refers to any character(s)
#   $< refers to the first item in the dependency list
%.o: ../src/%.cpp $(HEADERS)
	$(GCC) $(GCC-CFLAGS) $<

# $ make tests
tests: exceptional.o test.cpp
	$(GCC) $(GCC-LFLAGS) exceptional.o test.cpp -o $(OUTPUT)
	@echo "To execute the program, run: ./$(OUTPUT)"

# $ make tests-clang
tests-clang: $(HEADERS) ../src/exceptional.cpp test.cpp
	$(CLANG) ../src/exceptional.cpp test.cpp -o $(OUTPUT)
	@echo "To execute the program, run: ./$(OUTPUT)"

# $ make clean
# Removes created files
clean:
	rm -f $(OUTPUT) *.o *~ captains.log example_file.log
