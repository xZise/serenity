/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "AK/CharacterTypes.h"
#include "AK/Forward.h"
#include "AK/NonnullOwnPtr.h"
#include <LibCore/Stream.h>

#include <AK/CharacterTypes.h>
#include <AK/Debug.h>
#include <AK/DeprecatedString.h>
#include <AK/GenericLexer.h>
#include <AK/HashMap.h>
#include <AK/String.h>
#include <AK/StringView.h>
#include <AK/Utf8View.h>
#include <LibUnicode/CharacterTypes.h>
#include <stdio.h>

namespace F2 {

#define ENUMERATE_F2_TOKENS                                     \
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
    __ENUMERATE_F2_TOKEN(Return, ControlKeyword)                \
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
    __ENUMERATE_F2_TOKEN(Var, Keyword)                          \
    __ENUMERATE_F2_TOKEN(Void, Keyword)                         \
    __ENUMERATE_F2_TOKEN(While, ControlKeyword)                 \
    __ENUMERATE_F2_TOKEN(With, ControlKeyword)                  \
    __ENUMERATE_F2_TOKEN(Yield, ControlKeyword)

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

class Tokenizer {
public:
    Tokenizer(StringView source)
        : m_source(source)
    {
        keywords.set("async", TokenType::Async);
        keywords.set("await", TokenType::Await);
        keywords.set("break", TokenType::Break);
        keywords.set("case", TokenType::Case);
        keywords.set("catch", TokenType::Catch);
        keywords.set("class", TokenType::Class);
        keywords.set("const", TokenType::Const);
        keywords.set("continue", TokenType::Continue);
        keywords.set("debugger", TokenType::Debugger);
        keywords.set("default", TokenType::Default);
        keywords.set("delete", TokenType::Delete);
        keywords.set("do", TokenType::Do);
        keywords.set("else", TokenType::Else);
        keywords.set("enum", TokenType::Enum);
        keywords.set("export", TokenType::Export);
        keywords.set("extends", TokenType::Extends);
        keywords.set("false", TokenType::BoolLiteral);
        keywords.set("finally", TokenType::Finally);
        keywords.set("for", TokenType::For);
        keywords.set("function", TokenType::Function);
        keywords.set("if", TokenType::If);
        keywords.set("import", TokenType::Import);
        keywords.set("in", TokenType::In);
        keywords.set("instanceof", TokenType::Instanceof);
        keywords.set("let", TokenType::Let);
        keywords.set("new", TokenType::New);
        keywords.set("null", TokenType::NullLiteral);
        keywords.set("return", TokenType::Return);
        keywords.set("super", TokenType::Super);
        keywords.set("switch", TokenType::Switch);
        keywords.set("this", TokenType::This);
        keywords.set("throw", TokenType::Throw);
        keywords.set("true", TokenType::BoolLiteral);
        keywords.set("try", TokenType::Try);
        keywords.set("typeof", TokenType::Typeof);
        keywords.set("var", TokenType::Var);
        keywords.set("void", TokenType::Void);
        keywords.set("while", TokenType::While);
        keywords.set("with", TokenType::With);
        keywords.set("yield", TokenType::Yield);

        two_char_tokens.set("=>", TokenType::Arrow);
        two_char_tokens.set("+=", TokenType::PlusEquals);
        two_char_tokens.set("-=", TokenType::MinusEquals);
        two_char_tokens.set("*=", TokenType::AsteriskEquals);
        two_char_tokens.set("/=", TokenType::SlashEquals);
        two_char_tokens.set("%=", TokenType::PercentEquals);
        two_char_tokens.set("&=", TokenType::AmpersandEquals);
        two_char_tokens.set("|=", TokenType::PipeEquals);
        two_char_tokens.set("^=", TokenType::CaretEquals);
        two_char_tokens.set("&&", TokenType::DoubleAmpersand);
        two_char_tokens.set("||", TokenType::DoublePipe);
        two_char_tokens.set("??", TokenType::DoubleQuestionMark);
        two_char_tokens.set("**", TokenType::DoubleAsterisk);
        two_char_tokens.set("==", TokenType::EqualsEquals);
        two_char_tokens.set("<=", TokenType::LessThanEquals);
        two_char_tokens.set(">=", TokenType::GreaterThanEquals);
        two_char_tokens.set("!=", TokenType::ExclamationMarkEquals);
        two_char_tokens.set("--", TokenType::MinusMinus);
        two_char_tokens.set("++", TokenType::PlusPlus);
        two_char_tokens.set("<<", TokenType::ShiftLeft);
        two_char_tokens.set(">>", TokenType::ShiftRight);
        two_char_tokens.set("?.", TokenType::QuestionMarkPeriod);

        single_char_tokens.set('&', TokenType::Ampersand);
        single_char_tokens.set('*', TokenType::Asterisk);
        single_char_tokens.set('[', TokenType::BracketOpen);
        single_char_tokens.set(']', TokenType::BracketClose);
        single_char_tokens.set('^', TokenType::Caret);
        single_char_tokens.set(':', TokenType::Colon);
        single_char_tokens.set(',', TokenType::Comma);
        single_char_tokens.set('{', TokenType::CurlyOpen);
        single_char_tokens.set('}', TokenType::CurlyClose);
        single_char_tokens.set('=', TokenType::Equals);
        single_char_tokens.set('!', TokenType::ExclamationMark);
        single_char_tokens.set('-', TokenType::Minus);
        single_char_tokens.set('(', TokenType::ParenOpen);
        single_char_tokens.set(')', TokenType::ParenClose);
        single_char_tokens.set('%', TokenType::Percent);
        single_char_tokens.set('.', TokenType::Period);
        single_char_tokens.set('|', TokenType::Pipe);
        single_char_tokens.set('+', TokenType::Plus);
        single_char_tokens.set('?', TokenType::QuestionMark);
        single_char_tokens.set(';', TokenType::Semicolon);
        single_char_tokens.set('/', TokenType::Slash);
        single_char_tokens.set('~', TokenType::Tilde);
        single_char_tokens.set('<', TokenType::LessThan);
        single_char_tokens.set('>', TokenType::GreaterThan);
    }

    bool is_identifier_start()
    {
        return AK::is_ascii_alpha(current_char()) || current_char() == '_';
    }

    bool is_identifier_middle()
    {
        return is_identifier_start() || AK::is_ascii_alphanumeric(current_char());
    }

    Vector<Token> parse()
    {
        Vector<Token> tokens;

        size_t last_position = 0;

        while (!is_eof()) {
            dbgln("@{} (of {})", m_position, m_source.length());
            while (!is_eof() && AK::is_ascii_space(current_char())) {
                m_position++;
            }

            if (is_eof())
                break;

            last_position = m_position;

            TokenType token_type;
            if (AK::is_ascii_digit(current_char())) {
                bool hasDecimal = false;
                while (!is_eof()) {
                    if (current_char() == '.') {
                        if (hasDecimal)
                            break;
                        hasDecimal = true;
                    } else if (!AK::is_ascii_digit(current_char())) {
                        break;
                    }
                    m_position++;
                }

                token_type = TokenType::NumericLiteral;
            } else if (current_char() == '"') {
                m_position++;
                while (!is_eof()) {
                    if (current_char() == '"') {
                        break;
                    }
                    if (current_char() == '\\') {
                        m_position++;
                    }
                    m_position++;
                }

                token_type = TokenType::StringLiteral;
            } else if (is_identifier_start()) {
                while (!is_eof() && is_identifier_middle()) {
                    m_position++;
                }

                StringView identifier = m_source.substring_view(last_position, m_position - last_position);
                auto it = keywords.find(identifier.hash(), [&](auto& entry) { return entry.key == identifier; });
                if (it == keywords.end())
                    token_type = TokenType::Identifier;
                else
                    token_type = it->value;
            } else {
                bool found_two_char_token = false;
                if (m_position + 1 < m_source.length()) {
                    auto two_chars_view = m_source.substring_view(m_position, 2);
                    auto it = two_char_tokens.find(two_chars_view.hash(), [&](auto& entry) { return entry.key == two_chars_view; });
                    if (it != two_char_tokens.end()) {
                        // OptionalChainingPunctuator :: ?. [lookahead ∉ DecimalDigit]
                        if (!(it->value == TokenType::QuestionMarkPeriod && m_position + 1 < m_source.length() && is_ascii_digit(m_source[m_position + 1]))) {
                            found_two_char_token = true;
                            m_position += 2;
                            token_type = it->value;
                        }
                    }
                }

                bool found_one_char_token = false;
                if (!found_two_char_token) {
                    auto it = single_char_tokens.find(current_char());
                    if (it != single_char_tokens.end()) {
                        found_one_char_token = true;
                        m_position++;
                        token_type = it->value;
                    }
                }

                if (!found_two_char_token && !found_one_char_token) {
                    m_position++;
                    token_type = TokenType::Invalid;
                }
            }
            Token numberToken(token_type, m_source.substring_view(last_position, m_position - last_position));
            tokens.append(numberToken);
        }
        return tokens;
    }

private:
    bool is_eof() const { return m_position >= m_source.length(); }
    char current_char() const
    {
        VERIFY(!is_eof());
        return m_source[m_position];
    }

    size_t m_position = 0;
    StringView m_source;

    HashMap<DeprecatedString, TokenType> keywords;
    HashMap<DeprecatedString, TokenType> two_char_tokens;
    HashMap<char, TokenType> single_char_tokens;
};

class Parser {
public:
    void generate_ast(Tokenizer tokenizer)
    {
        Vector<Token> tokens = tokenizer.parse();
    }

private:
};

}
