/*
-----------------------------------------------------------------------------
This source file is part of OSTIS (Open Semantic Technology for Intelligent Systems)
For the latest info, see http://www.ostis.net

Copyright (c) 2012 OSTIS

OSTIS is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

OSTIS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public License
along with OSTIS. If not, see <http://www.gnu.org/licenses/>.
-----------------------------------------------------------------------------
 */

#ifndef SC_GARBAGE_COLLECTOR_FUNCTIONS_H
#define SC_GARBAGE_COLLECTOR_FUNCTIONS_H

/*! Removes all necessary elements from neigbourhood of question which become unuseful
 * @param quest sc-addr of element
 * @return Returns SC_RESULT_ERROR, if system error appeared. Otherwise returns SC_RESULT_OK.
 */
sc_result garbage_collector_unuseful_question(sc_addr quest);

#endif // SC_GARBAGE_COLLECTOR_FUNCTIONS_H
