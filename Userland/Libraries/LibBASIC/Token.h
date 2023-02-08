/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/String.h>

namespace basic {

#define ENUMERATE_F2_TOKENS                                     \
    __ENUMERATE_F2_TOKEN(Newline, Punctuation)                  \
    __ENUMERATE_F2_TOKEN(Ampersand, Operator)                   \
    __ENUMERATE_F2_TOKEN(AmpersandEquals, Operator)             \
    __ENUMERATE_F2_TOKEN(Arrow, Operator)                       \
    __ENUMERATE_F2_TOKEN(Asterisk, Operator)                    \
    __ENUMERATE_F2_TOKEN(AsteriskEquals, Operator)              \
    __ENUMERATE_F2_TOKEN(Async, Keyword)                        \
    __ENUMERATE_F2_TOKEN(Await, Keyword)                        \
    __ENUMERATE_F2_TOKEN(BigIntLiteral, Number)                 \
    __ENUMERATE_F2_TOKEN(BoolLiteral, Keyword)                  \
    __ENUMERATE_F2_TOKEN(BracketClose, Punctuation)             \
    __ENUMERATE_F2_TOKEN(BracketOpen, Punctuation)              \
    __ENUMERATE_F2_TOKEN(Break, Keyword)                        \
    __ENUMERATE_F2_TOKEN(Caret, Operator)                       \
    __ENUMERATE_F2_TOKEN(CaretEquals, Operator)                 \
    __ENUMERATE_F2_TOKEN(Case, ControlKeyword)                  \
    __ENUMERATE_F2_TOKEN(Catch, ControlKeyword)                 \
    __ENUMERATE_F2_TOKEN(Class, Keyword)                        \
    __ENUMERATE_F2_TOKEN(Colon, Punctuation)                    \
    __ENUMERATE_F2_TOKEN(Comma, Punctuation)                    \
    __ENUMERATE_F2_TOKEN(Const, Keyword)                        \
    __ENUMERATE_F2_TOKEN(Continue, ControlKeyword)              \
    __ENUMERATE_F2_TOKEN(CurlyClose, Punctuation)               \
    __ENUMERATE_F2_TOKEN(CurlyOpen, Punctuation)                \
    __ENUMERATE_F2_TOKEN(Debugger, Keyword)                     \
    __ENUMERATE_F2_TOKEN(Default, ControlKeyword)               \
    __ENUMERATE_F2_TOKEN(Delete, Keyword)                       \
    __ENUMERATE_F2_TOKEN(Do, ControlKeyword)                    \
    __ENUMERATE_F2_TOKEN(DoubleAmpersand, Operator)             \
    __ENUMERATE_F2_TOKEN(DoubleAmpersandEquals, Operator)       \
    __ENUMERATE_F2_TOKEN(DoubleAsterisk, Operator)              \
    __ENUMERATE_F2_TOKEN(DoubleAsteriskEquals, Operator)        \
    __ENUMERATE_F2_TOKEN(DoublePipe, Operator)                  \
    __ENUMERATE_F2_TOKEN(DoublePipeEquals, Operator)            \
    __ENUMERATE_F2_TOKEN(DoubleQuestionMark, Operator)          \
    __ENUMERATE_F2_TOKEN(DoubleQuestionMarkEquals, Operator)    \
    __ENUMERATE_F2_TOKEN(Else, ControlKeyword)                  \
    __ENUMERATE_F2_TOKEN(Enum, Keyword)                         \
    __ENUMERATE_F2_TOKEN(Eof, Invalid)                          \
    __ENUMERATE_F2_TOKEN(Equals, Operator)                      \
    __ENUMERATE_F2_TOKEN(EqualsEquals, Operator)                \
    __ENUMERATE_F2_TOKEN(EqualsEqualsEquals, Operator)          \
    __ENUMERATE_F2_TOKEN(EscapedKeyword, Identifier)            \
    __ENUMERATE_F2_TOKEN(ExclamationMark, Operator)             \
    __ENUMERATE_F2_TOKEN(ExclamationMarkEquals, Operator)       \
    __ENUMERATE_F2_TOKEN(ExclamationMarkEqualsEquals, Operator) \
    __ENUMERATE_F2_TOKEN(Export, Keyword)                       \
    __ENUMERATE_F2_TOKEN(Extends, Keyword)                      \
    __ENUMERATE_F2_TOKEN(Finally, ControlKeyword)               \
    __ENUMERATE_F2_TOKEN(For, ControlKeyword)                   \
    __ENUMERATE_F2_TOKEN(Function, Keyword)                     \
    __ENUMERATE_F2_TOKEN(GreaterThan, Operator)                 \
    __ENUMERATE_F2_TOKEN(GreaterThanEquals, Operator)           \
    __ENUMERATE_F2_TOKEN(Identifier, Identifier)                \
    __ENUMERATE_F2_TOKEN(If, ControlKeyword)                    \
    __ENUMERATE_F2_TOKEN(Implements, Keyword)                   \
    __ENUMERATE_F2_TOKEN(Import, Keyword)                       \
    __ENUMERATE_F2_TOKEN(In, Keyword)                           \
    __ENUMERATE_F2_TOKEN(Instanceof, Keyword)                   \
    __ENUMERATE_F2_TOKEN(Interface, Keyword)                    \
    __ENUMERATE_F2_TOKEN(Invalid, Invalid)                      \
    __ENUMERATE_F2_TOKEN(LessThan, Operator)                    \
    __ENUMERATE_F2_TOKEN(LessThanEquals, Operator)              \
    __ENUMERATE_F2_TOKEN(Let, Keyword)                          \
    __ENUMERATE_F2_TOKEN(Minus, Operator)                       \
    __ENUMERATE_F2_TOKEN(MinusEquals, Operator)                 \
    __ENUMERATE_F2_TOKEN(MinusMinus, Operator)                  \
    __ENUMERATE_F2_TOKEN(New, Keyword)                          \
    __ENUMERATE_F2_TOKEN(NullLiteral, Keyword)                  \
    __ENUMERATE_F2_TOKEN(NumericLiteral, Number)                \
    __ENUMERATE_F2_TOKEN(Package, Keyword)                      \
    __ENUMERATE_F2_TOKEN(ParenClose, Punctuation)               \
    __ENUMERATE_F2_TOKEN(ParenOpen, Punctuation)                \
    __ENUMERATE_F2_TOKEN(Percent, Operator)                     \
    __ENUMERATE_F2_TOKEN(PercentEquals, Operator)               \
    __ENUMERATE_F2_TOKEN(Period, Operator)                      \
    __ENUMERATE_F2_TOKEN(Pipe, Operator)                        \
    __ENUMERATE_F2_TOKEN(PipeEquals, Operator)                  \
    __ENUMERATE_F2_TOKEN(Plus, Operator)                        \
    __ENUMERATE_F2_TOKEN(PlusEquals, Operator)                  \
    __ENUMERATE_F2_TOKEN(PlusPlus, Operator)                    \
    __ENUMERATE_F2_TOKEN(Private, Keyword)                      \
    __ENUMERATE_F2_TOKEN(PrivateIdentifier, Identifier)         \
    __ENUMERATE_F2_TOKEN(Protected, Keyword)                    \
    __ENUMERATE_F2_TOKEN(Public, Keyword)                       \
    __ENUMERATE_F2_TOKEN(QuestionMark, Operator)                \
    __ENUMERATE_F2_TOKEN(QuestionMarkPeriod, Operator)          \
    __ENUMERATE_F2_TOKEN(RegexFlags, String)                    \
    __ENUMERATE_F2_TOKEN(RegexLiteral, String)                  \
    __ENUMERATE_F2_TOKEN(Semicolon, Punctuation)                \
    __ENUMERATE_F2_TOKEN(ShiftLeft, Operator)                   \
    __ENUMERATE_F2_TOKEN(ShiftLeftEquals, Operator)             \
    __ENUMERATE_F2_TOKEN(ShiftRight, Operator)                  \
    __ENUMERATE_F2_TOKEN(ShiftRightEquals, Operator)            \
    __ENUMERATE_F2_TOKEN(Slash, Operator)                       \
    __ENUMERATE_F2_TOKEN(SlashEquals, Operator)                 \
    __ENUMERATE_F2_TOKEN(Static, Keyword)                       \
    __ENUMERATE_F2_TOKEN(StringLiteral, String)                 \
    __ENUMERATE_F2_TOKEN(Super, Keyword)                        \
    __ENUMERATE_F2_TOKEN(Switch, ControlKeyword)                \
    __ENUMERATE_F2_TOKEN(TemplateLiteralEnd, String)            \
    __ENUMERATE_F2_TOKEN(TemplateLiteralExprEnd, Punctuation)   \
    __ENUMERATE_F2_TOKEN(TemplateLiteralExprStart, Punctuation) \
    __ENUMERATE_F2_TOKEN(TemplateLiteralStart, String)          \
    __ENUMERATE_F2_TOKEN(TemplateLiteralString, String)         \
    __ENUMERATE_F2_TOKEN(This, Keyword)                         \
    __ENUMERATE_F2_TOKEN(Throw, ControlKeyword)                 \
    __ENUMERATE_F2_TOKEN(Tilde, Operator)                       \
    __ENUMERATE_F2_TOKEN(TripleDot, Operator)                   \
    __ENUMERATE_F2_TOKEN(Try, ControlKeyword)                   \
    __ENUMERATE_F2_TOKEN(Typeof, Keyword)                       \
    __ENUMERATE_F2_TOKEN(UnsignedShiftRight, Operator)          \
    __ENUMERATE_F2_TOKEN(UnsignedShiftRightEquals, Operator)    \
    __ENUMERATE_F2_TOKEN(UnterminatedRegexLiteral, String)      \
    __ENUMERATE_F2_TOKEN(UnterminatedStringLiteral, String)     \
    __ENUMERATE_F2_TOKEN(UnterminatedTemplateLiteral, String)   \
    __ENUMERATE_F2_TOKEN(Print, ControlKeyword)                 \
    __ENUMERATE_F2_TOKEN(Goto, ControlKeyword)                  \
    __ENUMERATE_F2_TOKEN(Gosub, ControlKeyword)                 \
    __ENUMERATE_F2_TOKEN(Clear, ControlKeyword)                 \
    __ENUMERATE_F2_TOKEN(List, ControlKeyword)                  \
    __ENUMERATE_F2_TOKEN(Return, ControlKeyword)                \
    __ENUMERATE_F2_TOKEN(End, ControlKeyword)                   \
    __ENUMERATE_F2_TOKEN(Input, ControlKeyword)                 \
    __ENUMERATE_F2_TOKEN(Run, ControlKeyword)

enum class TokenType {
#define __ENUMERATE_F2_TOKEN(type, category) type,
    ENUMERATE_F2_TOKENS
#undef __ENUMERATE_F2_TOKEN
        _COUNT_OF_TOKENS
};

enum class TokenCategory {
    Invalid,
    Number,
    String,
    Punctuation,
    Operator,
    Keyword,
    ControlKeyword,
    Identifier
};

class Token {
public:
    Token(TokenType type, StringView value)
        : m_type(type)
        , m_value(value)
    {
    }

    TokenType type() const { return m_type; }
    StringView value() const { return m_value; }

private:
    TokenType m_type;
    StringView m_value;
};

};
