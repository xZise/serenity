/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/NonnullRefPtrVector.h>

#include "AST.h"
#include "Token.h"

namespace basic {

class Parser {
    typedef Vector<Token>::ConstIterator TokenIterator;

public:
    ErrorOr<AST> generate_ast(Vector<Token> const& tokens);

private:
    ErrorOr<NonnullRefPtrVector<Expression>> parse_expr_list(TokenIterator& it, TokenIterator end);
};

}
