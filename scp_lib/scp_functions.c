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

#include "scp_functions.h"
#include "sc_stream.h"
#include "sc_helper.h"
#include "sc_memory.h"
#include "sc_iterator3.h"
#include <stdio.h>
#include <malloc.h>

scp_result printError(const char* operator_name, const char* text){
    printf("\nSCP LIBRARY ERROR: %s : %s\n",operator_name,text);
    return SCP_ERROR;
}

scp_result scp_lib_init(const sc_char *repo_path, const sc_char *config_file)
{
    if (sc_memory_initialize(repo_path,config_file)==SC_FALSE)
    {
        return SCP_FALSE;
    }
    sc_helper_init();
    return SCP_TRUE;
}

scp_result scp_lib_shutdown()
{
    sc_memory_shutdown();
    sc_helper_shutdown();
    return SCP_TRUE;
}

scp_result genEl(scp_operand *param){
    if (param->param_type != SCP_ASSIGN){
        return printError("genEl", "Parameter must have ASSIGN modifier");
    }
    if ((param->element_type & scp_type_node) != scp_type_node){
        return printError("genEl", "Only node element can be generated. Use genElStr3 for arcs");
    }
    param->addr = sc_memory_node_new(param->element_type);
    if (SC_ADDR_IS_EMPTY(param->addr)){
        return printError("genEl", "Element cannot be generated");
    }
    return SCP_TRUE;
}

scp_result genElStr3(scp_operand *param1, scp_operand *param2, scp_operand *param3){
    /*if (param->param_type != SCP_ASSIGN){
        return printError("genEl", "Parameter must have ASSIGN modifier");
    }
    if ((param->element_type & scp_type_node) != scp_type_node){
        return printError("genEl", "Only node element can be generated. Use genElStr3 for arcs");
    }
    param->addr = sc_memory_node_new(param->element_type);
    if (SC_ADDR_IS_EMPTY(param->addr)){
        return printError("genEl", "Element cannot be generated");
    }*/
    /*if (param1->param_type == SCP_ASSIGN && param2->param_type == SCP_ASSIGN && param3->param_type == SCP_ASSIGN)
    {
        return printError("genElStr3", "All elements");
    }*/
    return SCP_TRUE;
}

scp_result ifVarAssign(scp_operand *param)
{
    if (SC_ADDR_IS_EMPTY(param->addr))
        return SCP_FALSE;
    else
        return SCP_TRUE;
}

scp_result ifCoin(scp_operand *param1, scp_operand *param2)
{
    if (SC_ADDR_IS_EMPTY(param1->addr)){
        return printError("ifCoin", "Parameter 1 has no value");
    }
    if (SC_ADDR_IS_EMPTY(param2->addr)){
        return printError("ifCoin", "Parameter 2 has no value");
    }
    if (SC_ADDR_IS_EQUAL(param1->addr,param2->addr))
        return SCP_TRUE;
    else
        return SCP_FALSE;
}

scp_result ifType(scp_operand *param)
{
    if (SC_ADDR_IS_EMPTY(param->addr)){
        return printError("ifType", "Parameter has no value");
    }
    sc_type elType;
    if (sc_memory_get_element_type(param->addr,&elType)!=SC_RESULT_OK)
    {
        return printError("ifType", "Type checking error");
    }
    if ((param->element_type & elType) == elType)
        return SCP_TRUE;
    else
        return SCP_FALSE;
}

scp_result printEl(scp_operand *param){
    if (SC_ADDR_IS_EMPTY(param->addr)){
        return printError("printEl", "Parameter is empty");
    }
    sc_addr element=param->addr;
    sc_addr addr2,addr3;
    sc_addr idtf;
    if (SC_RESULT_OK==sc_helper_get_system_identifier(element,&idtf)){
        sc_stream *stream;
        sc_memory_get_link_content(idtf,&stream);
        sc_uint length=0,read_length=0;
        sc_stream_get_length(stream,&length);
        sc_char *data=calloc(length,sizeof(sc_char));
        sc_stream_read_data(stream,data,length,&read_length);
        printf("\nPrint element: %s =\n",data);
        sc_stream_free(stream);
        free(data);
    }else{
        printf("\nPrint element: %u|%u =\n", element.seg, element.offset);
    }

    sc_iterator3 *it=sc_iterator3_a_a_f_new(0,0,element);
    if (it==0){
        return SCP_ERROR;
    }
    printf("Input arcs:\n");
    while (sc_iterator3_next(it))
    {
        addr2 = sc_iterator3_value(it, 0);
        addr3 = sc_iterator3_value(it, 1);

        if (SC_RESULT_OK==sc_helper_get_system_identifier(addr3,&idtf)){
            sc_stream *stream;
            sc_memory_get_link_content(idtf,&stream);
            sc_uint length=0,read_length=0;
            sc_stream_get_length(stream,&length);
            sc_char *data=calloc(length,sizeof(sc_char));
            sc_stream_read_data(stream,data,length,&read_length);
            printf("\t%s <- ",data);
            sc_stream_free(stream);
            free(data);
        }else{
            printf("\t%u|%u <- ", addr3.seg, addr3.offset);
        }
        if (SC_RESULT_OK==sc_helper_get_system_identifier(addr2,&idtf)){
            sc_stream *stream;
            sc_memory_get_link_content(idtf,&stream);
            sc_uint length=0,read_length=0;
            sc_stream_get_length(stream,&length);
            sc_char *data=calloc(length,sizeof(sc_char));
            sc_stream_read_data(stream,data,length,&read_length);
            printf("%s;\n",data);
            sc_stream_free(stream);
            free(data);
        }else{
            printf("%u|%u;\n", addr2.seg, addr2.offset);
        }
    }
    sc_iterator3_free(it);

    it=sc_iterator3_f_a_a_new(element,0,0);
    if (it==0){
        return SCP_ERROR;
    }
    printf("Output arcs:\n");
    while (sc_iterator3_next(it))
    {
        addr2 = sc_iterator3_value(it, 1);
        addr3 = sc_iterator3_value(it, 2);

        if (SC_RESULT_OK==sc_helper_get_system_identifier(addr2,&idtf)){
            sc_stream *stream;
            sc_memory_get_link_content(idtf,&stream);
            sc_uint length=0,read_length=0;
            sc_stream_get_length(stream,&length);
            sc_char *data=calloc(length,sizeof(sc_char));
            sc_stream_read_data(stream,data,length,&read_length);
            printf("\t%s -> ",data);
            sc_stream_free(stream);
            free(data);
        }else{
            printf("\t%u|%u -> ", addr2.seg, addr2.offset);
        }
        if (SC_RESULT_OK==sc_helper_get_system_identifier(addr3,&idtf)){
            sc_stream *stream;
            sc_memory_get_link_content(idtf,&stream);
            sc_uint length=0,read_length=0;
            sc_stream_get_length(stream,&length);
            sc_char *data=calloc(length,sizeof(sc_char));
            sc_stream_read_data(stream,data,length,&read_length);
            printf("%s;\n",data);
            sc_stream_free(stream);
            free(data);
        }else{
            printf("%u|%u;\n", addr3.seg, addr3.offset);
        }
    }
    sc_iterator3_free(it);
    return SCP_TRUE;
}