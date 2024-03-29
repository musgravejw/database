/* Database
 *
 * Copyright (c) 2019, John Musgrave <musgrajw at uc dot mail dot edu>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the name of this project nor the names of its contributors may be used
 *     to endorse or promote products derived from this software without
 *     specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */



/*
SQL supported:

CREATE TABLE [VALUES]
CREATE DATABASE [name]
INSERT INTO [table] VALUES([..])
CREATE INDEX [TYPE] [TABLE]
SELECT [..]

*/

PrepareResult prepare_statement(InputBuffer *input,
                                Statement *statement) {
	if (strncmp(input->buffer, "INSERT", 6) == 0) {
		int args_assigned = sscanf(input->buffer, 
								  "INSERT %d %s %s", 
								  &(statement->row_to_insert.id),
								  statement->row_to_insert.username, 
								  statement->row_to_insert.email);

		if (args_assigned < 3) return PREPARE_SYNTAX_ERROR;

		statement->type = STATEMENT_INSERT;

		return PREPARE_SUCCESS;
	} else if (strncmp(input->buffer, "insert", 6) == 0) {
		int args_assigned = sscanf(input->buffer, 
								  "insert %d %s %s", 
								  &(statement->row_to_insert.id),
								  statement->row_to_insert.username, 
								  statement->row_to_insert.email);

		if (args_assigned < 3) return PREPARE_SYNTAX_ERROR;

		statement->type = STATEMENT_INSERT;

		return PREPARE_SUCCESS;
	} else if (strncmp(input->buffer, "CREATE", 6) == 0) {

		statement->type = STATEMENT_INSERT;

		return PREPARE_SUCCESS;
	} else if (strncmp(input->buffer, "create", 6) == 0) {

		statement->type = STATEMENT_INSERT;

		return PREPARE_SUCCESS;
	} else if (strcmp(input->buffer, "SELECT") == 0 ||
		strcmp(input->buffer, "select") == 0) {
		statement->type = STATEMENT_SELECT;
	
		return PREPARE_SUCCESS;
	}

	return PREPARE_UNRECOGNIZED_STATEMENT;
}

