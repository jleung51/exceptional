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
	# INSTRUCTIONS:
	#   To test exceptional, run: make tests
	#   To remove compiled output files, run: make clean

# Executed whenever an object file is out of date
# Symbols:
#   % refers to any character(s)
#   $< refers to the first item in the dependency list
%.o: ../src/%.cpp $(HEADERS)
	$(GCC) $(GCC-CFLAGS) $<

# $ make tests
tests: exceptional.o test.cpp
	$(GCC) $(GCC-LFLAGS) exceptional.o test.cpp -o $(OUTPUT)
	# To execute the program, run: ./$(OUTPUT)

# $ make <custom>
<custom>: <source_files>
	<command>

# $ make clean
# Removes created files
clean:
	rm -f $(OUTPUT) *.o *~ log.txt
