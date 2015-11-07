#include <conio.h>
//TODO add other includes
void perform_debug(scp_operand operator) {
	print_debug_info(operator);
	wait_for_user_action();
}

void print_debug_info(scp_operand operator) {
	print_program_debug_info(operator);
	print_operator_debug_info(operator);
}

void print_program_debug_info(scp_operand operator) {
	scp_operand program = find_scp_program(operator);
	print_variables(program);
	print_constants(program);
}

scp_operand find_scp_program(scp_operand operator) {
  //TODO find scp_program for operator
}

void print_variables(scp_operand program) {
	scp_operand arc1, arc2, variables_set;
	MAKE_DEFAULT_OPERAND_ASSIGN(variables_set);
	MAKE_DEFAULT_ARC_ASSIGN(arc1);
	MAKE_DEFAULT_ARC_ASSIGN(arc2);
	scp_iterator5 *iterator = scp_iterator5_new(s_default_ctx, &program, &arc1, &variables_set, &arc2, &nrel_scp_program_var);
	if (SCP_RESULT_TRUE == scp_iterator5_next(s_default_ctx, iterator, &program, &arc1, &variables_set, &arc2, &nrel_scp_program_var))
		print_set(variables_set);
}

void print_constants(scp_operand program) {
  //TODO get iterator program-arc?-set?-arc?-nrel_scp_program_const
  //TODO put first matching into constants_set
	print_set(constants_set);
}

void print_set(scp_operand set) {
	set.param_type = SCP_FIXED;
	scp_operand arc, element;
	MAKE_DEFAULT_ARC_ASSIGN(arc);
	MAKE_DEFAULT_OPERAND_ASSIGN(element);
	scp_iterator3 *iterator = scp_iterator3_new(s_default_ctx, &set, &arc, &element);
	while(SCP_RESULT_TRUE == scp_iterator3_new(s_default_ctx, &set, &arc, &element))
		print_element(element);
}

void print_element(scp_operand element) {
	scp_param_type param_type = element.param_type
	element.param_type = SCP_FIXED;
	printEl(s_default_ctx, &element);
	element.param_type = param_type;
}

void print_operator_debug_info(scp_operand operator) {
	print_arguments(operator);
}

void print_arguments(scp_operand operator) {
  //TODO print each argument
}

void print_argument(scp_operand argument) {
}

void wait_for_user_action() {
	getch();
}
