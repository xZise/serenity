/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include "Parser.h"

namespace basic {

ErrorOr<AST> Parser::generate_ast(Vector<Token> const& tokens)
{
    out("\nFound {} tokens:\n", tokens.size());

    NonnullRefPtrVector<ASTNode> ast;
    bool fresh_line = true;
    for (TokenIterator it = tokens.begin(); it != tokens.end(); ++it) {
        out("{} / {}\n", static_cast<u8>(it->type()), it->value());

        if (fresh_line) {
            if (it->type() == TokenType::NumericLiteral) {
                out("Found line number {}\n", it->value());
                ast.append(AK::make_ref_counted<Label>(0, 0, ""sv, it->value()));
                fresh_line = false;
                continue;
            }

            return Error::from_string_literal("Expected line number at start of line");
        }

        if (it->type() == TokenType::Print) {
            out("Found print statement\n");
            ast.append(AK::make_ref_counted<Print>(0, 0, ""sv, TRY(parse_expr_list(it, tokens.end()))));
        }

        if (it->type() == TokenType::End) {
            out("Found end statement\n");
            ast.append(AK::make_ref_counted<End>(0, 0, ""sv));
        }

        fresh_line = it->type() == TokenType::Newline;
    }

    return AST(move(ast));
}

ErrorOr<NonnullRefPtrVector<Expression>> Parser::parse_expr_list(TokenIterator& it, TokenIterator end)
{
    NonnullRefPtrVector<Expression> expr_list;

    for (++it; it != end; ++it) {
        if (it->type() == TokenType::Plus || it->type() == TokenType::Minus) {
            // expr_list.append(AK::make_ref_counted<UnaryOp>(0, 0, ""sv, it->type() == TokenType::Plus ? UnaryOp::Type::Plus : UnaryOp::Type::Minus, TRY(parse_expr(++begin, end))));
        } else if (it->type() == TokenType::StringLiteral) {
            expr_list.append(AK::make_ref_counted<StringLiteral>(0, 0, ""sv, it->value()));
        } else if (it->type() == TokenType::Newline) {
            break;
        } else {
            return Error::from_string_literal("Unexpected token in expression list");
        }
    }

    return expr_list;
}

};
