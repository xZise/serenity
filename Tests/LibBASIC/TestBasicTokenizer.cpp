/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <LibBASIC/Tokenizer.h>
#include <LibTest/TestCase.h>

TEST_CASE(basic_tokenizer_no_newline_at_end)
{
    {
        basic::Tokenizer t("10 PRINT \"Hello World!\"\n20 END"sv);
        auto tokens = t.tokenize();

        EXPECT_EQ(tokens.size(), 6u);
    }

    {
        basic::Tokenizer t("10 PRINT \"Hello World!\""sv);
        auto tokens = t.tokenize();

        EXPECT_EQ(tokens.size(), 3u);
    }
}
