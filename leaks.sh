make
clear
# valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell
# valgrind --leak-check=full --show-leak-kinds=all ./minishell

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
RESET='\033[0m'

run_leaks() {
    valgrind --leak-check=full --show-leak-kinds=all --suppressions=readline.supp ./minishell -c $1 >val_out.txt 2>&1

    echo -e "${RED}Invalid reads${RESET}"
    echo
    echo -e "${RED}$(grep -i "Invalid read" val_out.txt)${RESET}"
    echo
    echo -e "${RED}Invalid writes${RESET}"
    echo
    echo -e "${RED}$(grep -i "Invalid write" val_out.txt)${RESET}"
    echo
    echo -e "${RED}all Invalid${RESET}"
    echo
    echo -e "${RED}$(grep -i "Invalid" val_out.txt)${RESET}"
    echo
    echo -e "${RED}mem leaks${RESET}"
    echo
    echo -e "${RED}$(grep -i "lost" val_out.txt | grep -v "lost: 0")${RESET}"
    echo
    echo -e "${RED}signals${RESET}"
    echo
    echo -e "${RED}$(grep -i "signal" val_out.txt)${RESET}"
    echo
}

run_leaks_frame() {
    echo -e "$1"
    echo
    run_leaks $1
    read
    clear
}

run_leaks_frame "echo -n hi | pwd | env"
run_leaks_frame "echo hi"
run_leaks_frame "cd"
run_leaks_frame "env"
run_leaks_frame "export A=test"
run_leaks_frame "unset PATH"
run_leaks_frame "exit"
run_leaks_frame "pwd"
run_leaks_frame "pwd | echo hi | ls | echo 123213123 \$HOME"
run_leaks_frame "echo '213213213' | wc"
run_leaks_frame "unknown"
run_leaks_frame "$EMPTY $EMPTY"
run_leaks_frame "            "

# read
