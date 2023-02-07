/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "./Interpreter.h"
#include "./AST.h"
#include <AK/RefPtr.h>

namespace F2 {

ErrorOr<void> Interpreter::run(String const& source)
{
    auto node = make_ref_counted<AssignmentOp>(0, 0, source,
        make_ref_counted<Val>(0, 0, source, TRY(String::from_utf8("a"sv))),
        make_ref_counted<StringLiteral>(0, 0, source, TRY(String::from_utf8("b"sv))));

    return {};
}

}
