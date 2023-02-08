/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/HashMap.h>
#include <AK/String.h>

#include "AST.h"

namespace basic {

class Interpreter {
public:
    static ErrorOr<Interpreter> create(StringView source);

    ErrorOr<void> run();
    ErrorOr<bool> run_one_line();

    size_t current_instruction() const { return m_current_instruction; }
    size_t executed_instructions() const { return m_num_executed_instructions; }

private:
    Interpreter(AST ast)
        : m_ast(move(ast))
    {
    }

    AST m_ast;
    HashMap<String, int> m_labels;
    size_t m_current_instruction { 0 };
    size_t m_num_executed_instructions { 0 };
};

};
