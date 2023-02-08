/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibBASIC/Parser.h>
#include <LibBASIC/Tokenizer.h>
#include <LibTest/TestCase.h>

TEST_CASE(basic_parser_no_newline_at_end)
{
    basic::Tokenizer t("10 PRINT \"Hello World!\"\n20 END"sv);
    basic::Parser p;
    auto ast = MUST(p.generate_ast(t.tokenize()));

    EXPECT_EQ(ast.size(), 6u);
}
