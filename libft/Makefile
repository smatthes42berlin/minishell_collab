# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 14:58:39 by smatthes          #+#    #+#              #
#    Updated: 2023/11/12 17:08:05 by smatthes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# log variables: $(info $$var is [$(PATHTESTEXE)test_%.$(TARGET_EXTENSION)])
# $^ -> all prerequisites with spaces in between
# $@ -> filename of the target of the rule
# $< ->  name of the first prerequisite

include Makefile_src
include Makefile_test

# -I Flag adds path where header files are searched during preprocessing
SHELL:=/bin/bash
CFLAGS = -Wall -Wextra -Werror -I$(INCLUDESRCPATH) -I$(INCLUDETESTPATH) -I$(PATHUNITY)
NAME = libft.a
TARGET_EXTENSION=  out
LINK = cc
CC = cc

PATHPROJABS = /home/smatthes/42cursus/projects42/push_swap/
INCLUDESRCPATH = ./include/
INCLUDETESTPATH = ./includetest/
SUBFOLDERSRC = . ascii/ convert/ io/ s_lst/ dc_lst/ mem/ split/ str/ int_arr/ get_next_line/ printf/ str_arr/ math/ files/
BASEPATHSRC = ./src/
PATHSRC = $(patsubst %,$(BASEPATHSRC)%,$(SUBFOLDERSRC))
PATHBUILD = build/
PATHOBJ = build/obj/
PATHTESTEXE = build/exe/
PATHRES = build/results/
PATHUNITY = unity/src/
BASEPATHTEST = ./srctest/
SUBFOLDERTEST = . split/ str_arr/ io/ str/ convert/ get_next_line/ printf/
PATHTEST = $(patsubst %,$(BASEPATHTEST)%,$(SUBFOLDERTEST))

# VPATH contains additional folders, where Makefile will look for source files (*.c)
VPATH = $(PATHSRC) $(PATHTEST) $(PATHUNITY)

SRCTESTUNIT = 	split/unit_ft_split_str.c 
SRCTESTUNITPATH = $(patsubst %,$(BASEPATHTEST)%,$(SRCTESTUNIT))

# for each *.c src file there is a *.o file
# the path is appended to each filename
OBJFNAME = $(SRC:.c=.o)
OBJ = $(patsubst %,$(PATHOBJ)%,$(OBJFNAME))

OBJTESTFNAME = $(SRCTEST:.c=.o)
OBJTEST = $(patsubst %,$(PATHOBJ)%,$(OBJTESTFNAME))

# there is one results file created for each src test file 
# (unity output is redirected to results file later)
# also one executable for each src test file

TESTOUTPUTPRINTF = $(PATHRES)test_output_pf.txt
RESULTS = $(patsubst %.c,$(PATHRES)%.txt,$(SRCTEST) )
TESTEXE = $(patsubst %.c,$(PATHTESTEXE)%.$(TARGET_EXTENSION),$(SRCTEST) )

# grab results from results files, -s suppress messages
# also count number with -c
PASS = `grep -s PASS $(PATHRES)*.txt`
PASSNUM = `grep -s -c PASS $(PATHRES)*.txt`
FAIL = `grep -s FAIL $(PATHRES)*.txt`
FAILNUM = `grep -s -c FAIL $(PATHRES)*.txt`
IGNORE = `grep -s IGNORE $(PATHRES)*.txt`
IGNORENUM = `grep -s -c IGNORE $(PATHRES)*.txt`

.PHONY: all clean fclean re bonus test testunit print

all: $(NAME)

# c archive is always createdif it doesnt exist
# s add index to archive or update if exists
# r insert files member into archive, replace previously added members with same name
$(NAME): $(OBJ)
	@ ar rcs $(NAME) $^

# create object files from source files
# any path in VPATH is searched for source files
$(PATHOBJ)%.o: %.c
	@ $(CC) $(CFLAGS) -c $< -o $@

# grab results from results files
test: testclean all $(RESULTS)
	$(call color_print_heading,$(YELLOW),IGNORES,$(IGNORENUM))
	@echo "$(IGNORE)"
	$(call color_print_heading,$(RED),FAILURES,$(FAILNUM))
	@echo "$(FAIL)"
	$(call color_print_heading,$(GREEN),PASSED,$(PASSNUM))
	@echo "$(PASS)"
	@printf "\nDONE\n"

# results files depends executable
# executable is run, otuput rediected to results files
# stdout and stderr are redirected to same stream
$(PATHRES)%.txt: $(PATHTESTEXE)%.$(TARGET_EXTENSION)
	-./$< > $@ 2>&1

#test executable is created by linking test-obj, unity and libft	
$(PATHTESTEXE)%.$(TARGET_EXTENSION): \
							$(PATHOBJ)%.o \
							$(PATHOBJ)unity.o
	$(LINK) -o $@ $^ -L. $(NAME)

# unit tests
# testfiles include all other necessary files as headers
# CFLAGS variable is adjusted, to look for headers in all src path
# that way, other files can be included without specifying relative path
# test is run for each specified unit test file
testunit: $(PATHOBJ)unity.o
	$(eval CFLAGS := $(CFLAGS) $(patsubst %,-I$(BASEPATHSRC)%,$(SUBFOLDERSRC)))
	@for unit_file in $(SRCTESTUNITPATH); do \
		$(CC) $(CFLAGS) $$unit_file $(PATHOBJ)unity.o -o test.out;\
		./test.out; \
		rm test.out; \
	done

clean: testclean
	@ $(RM) $(OBJ)

testclean:
	@ $(RM) $(OBJTEST)
	@ $(RM) $(PATHRES)test_results.txt
	@ $(RM) $(RESULTS)
	@ $(RM) $(TESTEXE)
	@ $(RM) $(PATHOBJ)unity.o

fclean: clean
	@ $(RM) $(NAME)

re: fclean all

# variables are printed using formatting functions specified at the end
print:
	@clear
	$(call print_heading, PATH)
	$(call print_path_var, PATHSRC, $(PATHSRC))
	$(call print_path_var, PATHBUILD, $(PATHBUILD))
	$(call print_path_var, PATHOBJ, $(PATHOBJ))
	$(call print_path_var, PATHTESTEXE, $(PATHTESTEXE))
	$(call print_path_var, PATHRES, $(PATHRES))
	$(call print_path_var, PATHUNITY, $(PATHUNITY))
	$(call print_path_var, PATHTEST, $(PATHTEST))
	$(call print_path_var, VPATH, $(VPATH))
	$(call print_heading, SRC FILES)
	$(call print_file_names, $(SRCFNAMERELPATH))
	$(call print_heading, SRC TEST FILES)
	$(call print_file_names, $(SRCTESTFNAMERELPATH))
	$(call print_heading, OBJ)
	$(call print_file_names, $(OBJFNAME))
	$(call print_heading, OBJTEST)
	$(call print_file_names, $(OBJTESTFNAME))
	$(call print_heading, RESULTS)
	$(call print_file_names, $(RESULTS))

# tells makefile not to delete the following files after running
.PRECIOUS: $(PATHTESTEXE)%.$(TARGET_EXTENSION)
.PRECIOUS: $(PATHOBJ)%.o
.PRECIOUS: $(PATHOBJ)%.d
.PRECIOUS: $(PATHRES)%.txt	

INDENTATION = 15
INDENTATION2 = 30
HEADINGFORMATBEG = *****************************************
HEADINGFORMATEND = $(HEADINGFORMATBEG)

BLACK=0
RED=1
GREEN=2
YELLOW=3
BLUE=4
MAGENTA=5
CYAN=6
WHITE=7

define print_file_names
	@for a in $(1) ; do \
		c=$$(( $${c:--1}+1 )); \
    	if [[ $$(($$c % 4)) == 0 ]]; then \
    	 	printf "\n"; \
		fi; \
			printf "%-$(INDENTATION2)s" $$a; \
    done
    @printf "\n";
endef 

define print_path_var 
	@printf "%-$(INDENTATION)s %-$(INDENTATION)s" $(1) $(2)
	@printf "\n"
endef

define print_heading
	@printf "\n$(HEADINGFORMATBEG)$(1)$(HEADINGFORMATEND)\n"
endef

define color_print_heading
    @tput setaf $1
	@printf "\n"
	@printf "%-20s%-s%-s%-20s" "************" $2 "($3)" "************"
	@printf "\n\n"
    @tput sgr0
endef
