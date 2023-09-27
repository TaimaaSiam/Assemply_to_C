#ifndef _CODE_H
#define _CODE_H

#include <stdio.h>
#include <stdbool.h>
#include "globals.h"


#define MAX_LINE_LENGTH 80



bool validate_op_addr(line_info line, addressing_type op1_addressing, addressing_type op2_addressing,
                      int op1_valid_addr_count, int op2_valid_addr_count, ...);

reg get_register_by_name(char *name);
/**
 * Print an error message with the line number and file name.
 * @param line The line information containing the error
 * @param format The format string for the error message (with optional arguments)
 * @param ... Optional arguments for the format string
 */
int printf_line_error(line_info line, char *format, ...);

/**
 * Free dynamically allocated memory used by the assembler.
 */
void free_memory();

/**
 * Analyze the operands in the source line and store them in destination array.
 * @param line The current line information
 * @param i The current index in the line content
 * @param destination Array to store the parsed operands
 * @param operand_count Pointer to store the number of operands found
 * @param c Pointer to store the character at the current index in the line content
 * @return Whether the operand analysis was successful
 */
bool analyze_operands(line_info line, int i, char **destination, int *operand_count, char *c);

/**
 * Get the opcode corresponding to the given command.
 * @param cmd The command string
 * @param opcode_out Pointer to store the corresponding opcode
 */
void get_opcode(char *cmd, opcode *opcode_out);

/**
 * Determine the addressing mode of an operand.
 * @param operand The operand string
 * @return The addressing mode of the operand
 */
addressing_type get_addressing_type(char *operand);

/**
 * Validate the operands' addressing modes based on the opcode of the instruction.
 * @param line The current source line info
 * @param first_addressing The addressing of the first operand
 * @param second_addressing The addressing of the second operand
 * @param curr_opcode The opcode of the current instruction
 * @param op_count The operand count of the current instruction
 * @return Whether the addressing modes are valid
 */
bool validate_operand_by_opcode(line_info line, addressing_type first_addressing,
                                addressing_type second_addressing, opcode curr_opcode, int op_count);

/**
 * Get the code word representation of the instruction.
 * @param line The current source line info
 * @param curr_opcode The opcode of the current instruction
 * @param op_count The operand count of the current instruction
 * @param operands Array containing the operands
 * @return Pointer to the code word representing the instruction (NULL on failure)
 */
code_word *get_code_word(line_info line, opcode curr_opcode, int op_count, char **operands);

/**
 * Build a data word representation.
 * @param addressing The addressing mode of the data
 * @param data The data value to be stored in the word
 * @param is_extern_symbol Whether the data is an external symbol
 * @return Pointer to the data word representation
 */
data_word *build_data_word(addressing_type addressing, long data, bool is_extern_symbol);



 bool is_int(char *string) ;



#endif  /* _CODE_H */
