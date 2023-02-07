/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "AK/Forward.h"
#include "LibJS/AST.h"
#include <AK/NonnullRefPtrVector.h>
#include <AK/RefPtr.h>
#include <AK/String.h>

namespace F2 {

class ASTNode : public RefCounted<ASTNode> {
public:
    ASTNode(size_t line_number, size_t line_column, StringView line)
        : m_line_number(line_number)
        , m_line_column(line_column)
        , m_line(line)
    {
    }
    virtual ~ASTNode() = default;

    virtual bool is_val() const { return false; }
    virtual bool is_assignment_op() const { return false; }
    virtual bool is_function_call() const { return false; }
    virtual bool is_number_literal() const { return false; }
    virtual bool is_string_literal() const { return false; }

    u32 line_number() const { return m_line_number; }
    u32 line_column() const { return m_line_column; }
    StringView line() const { return m_line; }

private:
    size_t m_line_number { 0 };
    size_t m_line_column { 0 };
    StringView m_line;
};

class Val : public ASTNode {
public:
    Val(size_t line_number, size_t line_column, StringView line, String const& identifier)
        : ASTNode(line_number, line_column, line)
        , m_identifier(identifier)
    {
    }

    virtual bool is_val() const override { return true; }

    String const& identifier() const { return m_identifier; }

private:
    String m_identifier;
};

class AssignmentOp : public ASTNode {
public:
    AssignmentOp(size_t line_number, size_t line_column, StringView line, NonnullRefPtr<ASTNode> const& rhs, NonnullRefPtr<ASTNode> const& lhs)
        : ASTNode(line_number, line_column, line)
        , m_lhs(move(lhs))
        , m_rhs(move(rhs))
    {
    }

    virtual bool is_assignment_op() const override { return true; }

    NonnullRefPtr<ASTNode> const& lhs() const { return m_lhs; }
    NonnullRefPtr<ASTNode> const& rhs() const { return m_rhs; }

private:
    NonnullRefPtr<ASTNode> m_lhs;
    NonnullRefPtr<ASTNode> m_rhs;
};

class FunctionCall : public ASTNode {
public:
    FunctionCall(size_t line_number, size_t line_column, StringView line, String const& name, NonnullRefPtrVector<ASTNode> const& arguments)
        : ASTNode(line_number, line_column, line)
        , m_name(move(name))
        , m_arguments(move(arguments))
    {
    }

    virtual bool is_function_call() const override { return true; }

    String const& name() const { return m_name; }
    NonnullRefPtrVector<ASTNode> const& arguments() const { return m_arguments; }

private:
    String m_name;
    NonnullRefPtrVector<ASTNode> m_arguments;
};

class NumberLiteral : public ASTNode {
public:
    NumberLiteral(size_t line_number, size_t line_column, StringView line, double value)
        : ASTNode(line_number, line_column, line)
        , m_value(value)
    {
    }

    virtual bool is_number_literal() const override { return true; }

    double value() const { return m_value; }

private:
    double m_value { 0 };
};

class StringLiteral : public ASTNode {
public:
    StringLiteral(size_t line_number, size_t line_column, StringView line, String const& value)
        : ASTNode(line_number, line_column, line)
        , m_value(value)
    {
    }

    virtual bool is_string_literal() const override { return true; }

    String const& value() const { return m_value; }

private:
    String m_value;
};

};
