/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "./Interpreter.h"
#include "./AST.h"
#include "AK/Format.h"
#include "Tokenizer.h"
#include <AK/RefPtr.h>

namespace F2 {

ErrorOr<void> Interpreter::run(String const&)
{
    auto source2 = TRY(String::from_utf8("hello = 12345 == 65432"sv));

    Tokenizer t(source2);
    auto tokens = t.parse();

    dbgln(":-) {}", tokens.size());

    for (auto token : tokens) {
        dbgln("{} / {}", static_cast<u8>(token.type()), token.value());
    }

    return {};
}

}
