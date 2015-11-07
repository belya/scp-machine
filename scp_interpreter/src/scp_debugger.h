#include <conio.h>
//TODO add other includes
void perform_debug(scp_operand operator);

void print_debug_info(scp_operand operator);

void print_program_debug_info(scp_operand operator);

scp_operand find_scp_program(scp_operand operator);

void print_variables(scp_operand program);

void print_constants(scp_operand program);

void print_set(scp_operand set);

void print_element(scp_operand element);

void print_operator_debug_info(scp_operand operator);

void print_arguments(scp_operand operator);

void print_argument(scp_operand argument);

void wait_for_user_action();
