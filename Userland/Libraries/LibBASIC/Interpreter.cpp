/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <AK/RefPtr.h>

#include "AST.h"
#include "Interpreter.h"
#include "Parser.h"
#include "Tokenizer.h"

namespace basic {

ErrorOr<Interpreter> Interpreter::create(StringView source)
{
    Tokenizer t(source);
    Parser p;
    auto const ast = TRY(p.generate_ast(t.tokenize()));
    return Interpreter(ast);
}

ErrorOr<void> Interpreter::run()
{
    out("\nAST:\n");
    m_ast.dump();
    out("\n");

    while (TRY(run_one_line()) == false)
        ;

    return {};
}

ErrorOr<bool> Interpreter::run_one_line()
{
    ASTNode const& node = m_ast.nodes()[m_current_instruction++];
    ++m_num_executed_instructions;

    if (node.is_label()) {
        out("Exec Label\n");
        m_labels.set(dynamic_cast<Label const&>(node).name(), 0);
    } else if (node.is_print()) {
        out("Exec Print\n");
        auto const value = TRY(dynamic_cast<Print const&>(node).expr_list()[0].eval());

        value.visit(
            [&](int const& num) { out("{}\n", num); },
            [&](String const& str) { out("{}\n", str); });
    } else if (node.is_end()) {
        out("Exec End\n");
        return true;
    } else {
        return Error::from_string_literal("Unknown statement");
    }

    return false;
}

};
