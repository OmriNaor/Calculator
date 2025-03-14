CC = gcc
CFLAGS = -ansi -pedantic-errors -Wall -Wextra -fPIC -g
CPPFLAGS = -I include/
SHARED = -shared

SRC = src
TEST = test
HEADER = include
NAME = calculator

BUILD = .
DEBUG_BUILD = bin/debug
RELEASE_BUILD = bin/release

# Manually define the libraries you want to compile
LIBS = stack # Add or remove libraries here

OBJ_LIBS = $(patsubst %, $(BUILD)/%.o, $(LIBS))

.PHONY: all
all:
	make debug
	make release
	make test

####################################### TEST #########################################
.PHONY: test
test: $(BUILD)/$(NAME).out

$(BUILD)/$(NAME).out: $(BUILD)/$(NAME)_test.o $(DEBUG_BUILD)/$(NAME).so
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ $^ -lm
	
$(BUILD)/$(NAME)_test.o: $(TEST)/$(NAME)_test.c $(HEADER)/$(NAME).h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $(TEST)/$(NAME)_test.c -o $@

$(BUILD)/%.o: $(SRC)/%.c $(HEADER)/%.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	
		
####################################### DEBUG #########################################

.PHONY: debug
debug: CFLAGS += -g
debug: $(DEBUG_BUILD)/$(NAME).so

$(DEBUG_BUILD)/$(NAME).so: $(NAME).o $(OBJ_LIBS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SHARED) -o $@ $< $(OBJ_LIBS) -lm

$(NAME).o: $(SRC)/$(NAME).c $(HEADER)/$(NAME).h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	

####################################### RELEASE #########################################

.PHONY: release
release: CFLAGS += -O3 -DNDEBUG
release: $(RELEASE_BUILD)/$(NAME).so

$(RELEASE_BUILD)/$(NAME).so: $(NAME).o $(OBJ_LIBS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(SHARED) -o $@ $< $(OBJ_LIBS) -lm
	
	
####################################### CLEAN #########################################
	
.PHONY: clean
clean:
	rm -f $(BUILD)/*.o $(DEBUG_BUILD)/*.o $(RELEASE_BUILD)/*.o $(BUILD)/*.out $(DEBUG_BUILD)/*.out $(RELEASE_BUILD)/*.out $(NAME).so $(RELEASE_BUILD)/*.so $(DEBUG_BUILD)/*.so
