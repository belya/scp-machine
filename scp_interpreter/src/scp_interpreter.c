/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2010-2013 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with OSTIS.  If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
*/

#include "sc_memory_headers.h"

#include "scp_interpreter.h"
#include "scp_keynodes.h"
#include "scp_process_creator.h"
#include "scp_process_destroyer.h"

scp_result scp_interpreter_init(const sc_char *repo_path, const sc_char *config_file)
{
    if (SCP_RESULT_TRUE == scp_lib_init(repo_path, config_file) &&
        SCP_RESULT_TRUE == scp_keynodes_init() &&
        SCP_RESULT_TRUE == scp_process_destroyer_init() &&
        SCP_RESULT_TRUE == scp_process_creator_init())
        return SCP_RESULT_TRUE;
    else
        return SCP_RESULT_ERROR;
}

scp_result scp_interpreter_shutdown()
{
    if (SCP_RESULT_TRUE == scp_lib_shutdown() &&
        SCP_RESULT_TRUE == scp_process_destroyer_shutdown() &&
        SCP_RESULT_TRUE == scp_process_creator_shutdown())
        return SCP_RESULT_TRUE;
    else
        return SCP_RESULT_ERROR;
}