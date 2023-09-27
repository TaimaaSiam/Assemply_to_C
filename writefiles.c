#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"
#include "table.h"

#define KEEP_ONLY_24_LSB(value) ((value) & 0xFFFFFF)
/**
 * "Cuts" the msb of the value, keeping only it's lowest 21 bits
 * 0b00000000000111111111111111111111 = 0x1FFFFF
 */
#define KEEP_ONLY_21_LSB(value) ((value) & 0x1FFFFF)

/**
 * Writes the code and data image into an .ob file, with lengths on top
 * @param code_img The code image
 * @param data_img The data image
 * @param icf The final instruction counter
 * @param dcf The final data counter
 * @param filename The filename, without the extension
 * @return Whether succeeded
 */
static bool write_ob(machine_word **code_img, long *data_img, long icf, long dcf, char *filename);


bool write_table_to_file(table tab, char *filename, char *file_extension) {
    FILE *file_desc;
    /* concatenate filename & extension, and open the file for writing: */
    char *full_filename = strallocat(filename, file_extension);
    file_desc = fopen(full_filename, "w");
    free(full_filename);
    /* if failed, print error and exit */
    if (file_desc == NULL) {
        printf("Can't create or rewrite to file %s.", full_filename);
        return FALSE;
    }
    /* if table is null, nothing to write */
    if (tab == NULL) return TRUE;

    /* Write first line without \n to avoid extraneous line breaks */
    fprintf(file_desc, "%s %.7ld", tab->key, tab->value);
    while ((tab = tab->next) != NULL) {
        fprintf(file_desc, "\n%s %.7ld", tab->key, tab->value);
    }
    fclose(file_desc);
    return TRUE;
}
/**
 * Writes a symbol table to a file. Each symbol and it's address in line, separated by a single space.
 * @param tab The symbol table to write
 * @param filename The filename without the extension
 * @param file_extension The extension of the file, including dot before
 * @return Whether succeeded
 */





int write_output_files(machine_word **code_img, long *data_img, long icf, long dcf, char *filename,table symbol_table) {
	bool result;
	table externals = filter_table_by_type(symbol_table, EXTERNAL_REFERENCE);
	table entries = filter_table_by_type(symbol_table, ENTRY_SYMBOL);
	/* Write .ob file */
	result = write_ob(code_img, data_img, icf, dcf, filename) &&
	         /* Write *.ent and *.ext files: call with symbols from external references type or entry type only */
	         write_table_to_file(externals, filename, ".ext") &&
	         write_table_to_file(entries, filename, ".ent");
	/* Release filtered tables */
	free_table(externals);
	free_table(entries);
	return result;
}

static  bool write_ob(machine_word **code_img, long *data_img,long icf, long dcf, char *filename){
   
    FILE *file_desc;
    /* add extension of file to open */
    char *output_filename = strallocat(filename, ".ob");
    /* Try to open the file for writing */
    file_desc = fopen(output_filename, "w");
    free(output_filename);
    if (file_desc == NULL) {
        printf("Can't create or rewrite to file %s.", output_filename);
        return FALSE;
    }

    return true;
}

