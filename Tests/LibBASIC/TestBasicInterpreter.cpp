/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibBASIC/Interpreter.h>
#include <LibTest/TestCase.h>

TEST_CASE(basic_interpreter)
{
    auto i = MUST(basic::Interpreter::create("10 PRINT \"Hello World!\"\n20 END\n30 PRINT \"Test\"\n"sv));
    MUST(i.run());
}
