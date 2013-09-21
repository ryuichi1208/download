#
# Makefile
#
# This is a simple make file to build the download program.
#

PROGRAM_NAME=download
SHARED_LIBRARIES=-lcurl -lncurses

# by default, compile and link the program
default:
	gcc -Wall -o $(PROGRAM_NAME) $(SHARED_LIBRARIES) src/*.c

# the debug target adds the -g option, allowing debugging with gdb
debug:
	gcc -Wall -g -o $(PROGRAM_NAME) $(SHARED_LIBRARIES) src/*.c

# delete the program and debug directory if they exist
clean:
	if [ -f $(PROGRAM_NAME) ]; then rm -f $(PROGRAM_NAME); fi;
	if [ -d $(PROGRAM_NAME).dSYM ]; then rm -rf $(PROGRAM_NAME).dSYM; fi;
