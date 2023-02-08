/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include <AK/DeprecatedString.h>
#include <AK/HashMap.h>

#include "Token.h"

namespace basic {

class Tokenizer {
public:
    Tokenizer(StringView source)
        : m_source(source)
    {
        keywords.set("PRINT", TokenType::Print);
        keywords.set("IF", TokenType::If);
        keywords.set("GOTO", TokenType::Goto);
        keywords.set("INPUT", TokenType::Input);
        keywords.set("LET", TokenType::Let);
        keywords.set("GOSUB", TokenType::Gosub);
        keywords.set("RETURN", TokenType::Return);
        keywords.set("CLEAR", TokenType::Clear);
        keywords.set("LIST", TokenType::List);
        keywords.set("RUN", TokenType::Run);
        keywords.set("END", TokenType::End);

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
        single_char_tokens.set('\n', TokenType::Newline);
    }

    bool is_identifier_start()
    {
        return AK::is_ascii_alpha(current_char()) || current_char() == '_';
    }

    bool is_identifier_middle()
    {
        return is_identifier_start() || AK::is_ascii_alphanumeric(current_char());
    }

    Vector<Token> tokenize();

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

}
