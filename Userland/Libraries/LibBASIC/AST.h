/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/NonnullRefPtrVector.h>
#include <AK/RefPtr.h>
#include <AK/String.h>

namespace basic {

class ASTNode : public RefCounted<ASTNode> {
public:
    ASTNode(size_t line_number, size_t line_column, StringView line)
        : m_line_number(line_number)
        , m_line_column(line_column)
        , m_line(MUST(String::from_utf8(line)))
    {
    }
    virtual ~ASTNode() = 0;

    virtual bool is_label() const { return false; }
    virtual bool is_print() const { return false; }
    // virtual bool is_if() const { return false; }
    // virtual bool is_goto() const { return false; }
    // virtual bool is_input() const { return false; }
    // virtual bool is_let() const { return false; }
    // virtual bool is_gosub() const { return false; }
    // virtual bool is_return() const { return false; }
    virtual bool is_clear() const { return false; }
    virtual bool is_end() const { return false; }
    virtual bool is_number_literal() const { return false; }
    virtual bool is_string_literal() const { return false; }

    virtual void dump(int indent = 0) const = 0;
    virtual size_t size() const = 0;

    size_t line_number() const { return m_line_number; }
    size_t line_column() const { return m_line_column; }
    String const& line() const { return m_line; }

private:
    size_t m_line_number { 0 };
    size_t m_line_column { 0 };
    String m_line;
};

class AST {
public:
    AST(NonnullRefPtrVector<ASTNode> const& nodes)
        : m_nodes(move(nodes))
    {
    }

    void dump() const;
    size_t size() const;

    NonnullRefPtrVector<ASTNode> const& nodes() const { return m_nodes; }

private:
    NonnullRefPtrVector<ASTNode> m_nodes;
};

class Label : public ASTNode {
public:
    Label(size_t line_number, size_t line_column, StringView line, StringView name)
        : ASTNode(line_number, line_column, line)
        , m_name(MUST(String::from_utf8(name)))
    {
    }

    bool is_label() const override { return true; }
    size_t size() const override { return 1; }

    String const& name() const { return m_name; }

    void dump(int indent) const override
    {
        out("{}Label: {}\n", MUST(String::repeated(' ', indent)), m_name);
    }

private:
    String m_name;
};

class Expression : public ASTNode {
public:
    Expression(size_t line_number, size_t line_column, StringView line)
        : ASTNode(line_number, line_column, line)
    {
    }

    virtual ErrorOr<Variant<int, String>> eval() const = 0;
};

class BinaryOp : public Expression {
public:
    enum class Type {
        Plus,
        Minus,
        Multiply,
        Divide,
    };

    BinaryOp(size_t line_number, size_t line_column, StringView line, RefPtr<Expression> const& lhs, RefPtr<Expression> const& rhs, Type op)
        : Expression(line_number, line_column, line)
        , m_lhs(move(lhs))
        , m_rhs(move(rhs))
        , m_op(op)
    {
    }

private:
    RefPtr<Expression> m_lhs;
    RefPtr<Expression> m_rhs;
    Type m_op;
};

// class UnaryOp : public Expression {
// public:
//     enum class Type {
//         Plus,
//         Minus,
//     };

//     UnaryOp(size_t line_number, size_t line_column, StringView line, RefPtr<Expression> const& expr, Type op)
//         : Expression(line_number, line_column, line)
//         , m_expr(move(expr))
//         , m_op(op)
//     {
//     }

// private:
//     RefPtr<Expression> m_expr;
//     Type m_op;
// };

class Print : public ASTNode {
public:
    Print(size_t line_number, size_t line_column, StringView line, NonnullRefPtrVector<Expression> const& expr_list)
        : ASTNode(line_number, line_column, line)
        , m_expr_list(expr_list)
    {
    }

    virtual bool is_print() const override { return true; }
    size_t size() const override { return 1 + m_expr_list.size(); }

    void dump(int indent) const override
    {
        out("{}Print:\n", MUST(String::repeated(' ', indent)));
        for (auto& expr : m_expr_list) {
            expr.dump(indent + 2);
        }
    }

    NonnullRefPtrVector<Expression> const& expr_list() const { return m_expr_list; }

private:
    NonnullRefPtrVector<Expression> m_expr_list;
};

class Clear : public ASTNode {
public:
    Clear(size_t line_number, size_t line_column, StringView line)
        : ASTNode(line_number, line_column, line)
    {
    }

    virtual bool is_clear() const override { return true; }
    size_t size() const override { return 1; }
};

class End : public ASTNode {
public:
    End(size_t line_number, size_t line_column, StringView line)
        : ASTNode(line_number, line_column, line)
    {
    }

    virtual bool is_end() const override { return true; }
    size_t size() const override { return 1; }

    void dump(int indent) const override
    {
        out("{}End\n", MUST(String::repeated(' ', indent)));
    }
};

class NumberLiteral : public ASTNode {
public:
    NumberLiteral(size_t line_number, size_t line_column, StringView line, double value)
        : ASTNode(line_number, line_column, line)
        , m_value(value)
    {
    }

    virtual bool is_number_literal() const override { return true; }
    size_t size() const override { return 1; }

    double value() const { return m_value; }

private:
    double m_value { 0 };
};

class StringLiteral : public Expression {
public:
    StringLiteral(size_t line_number, size_t line_column, StringView line, StringView value)
        : Expression(line_number, line_column, line)
        , m_value(MUST(String::from_utf8(value)))
    {
    }

    virtual bool is_string_literal() const override { return true; }
    size_t size() const override { return 1; }

    virtual ErrorOr<Variant<int, String>> eval() const override { return TRY(m_value.trim("\""sv)); }

    void dump(int indent) const override
    {
        out("{}StringLiteral: {}\n", MUST(String::repeated(' ', indent)), m_value);
    }

private:
    String m_value;
};

};
