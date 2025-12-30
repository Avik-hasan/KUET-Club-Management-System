# Compiler
CC = gcc

# Compiler flags
# -c: Compile and assemble, but do not link
# -Wall: Enable all common warnings
CFLAGS = -c -Wall

# Linker flags (I removed a bad space character here)
LDFLAGS =

# Target executable name
TARGET = my_club_app

# Object files
# We list all .o files needed to build the target.
OBJ = main.o \
      admin.o \
      user.o \
      admin_members.o \
      admin_utils.o \
      admin_events.o \
      AdiminWorkspace.o \
      user_public.o \
      user_auth.o \
      user_member.o

# --- Rules ---

# Default rule (what runs when you just type 'make')
# .PHONY means 'all' is just a label, not a file.
.PHONY: all
all: $(TARGET)

# Linking rule: Combines all .o files into the final executable
# This rule depends on all the object files listed in $(OBJ).
$(TARGET): $(OBJ)
	# IMPORTANT: This line MUST be indented with a Tab, not spaces!
	$(CC) $(OBJ) $(LDFLAGS) -o $(TARGET).exe

# Compilation rule (Pattern Rule)
# This one rule replaces all your separate '.o: .c' rules.
# It says: "To make any file.o, find its file.c"
%.o: %.c
	# IMPORTANT: This line MUST be indented with a Tab, not spaces!
	# $< is an automatic variable for the prerequisite (the .c file)
	# $@ is an automatic variable for the target (the .o file)
	$(CC) $(CFLAGS) $< -o $@

# Clean rule: Removes generated files
# .PHONY means 'clean' is just a label, not a file.
.PHONY: clean
	clean:
	# This line MUST be indented with a Tab!
	rm -f *.o $(TARGET).exe