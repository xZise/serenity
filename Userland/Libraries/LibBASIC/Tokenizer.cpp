/*
 * Copyright (c) 2023, Florian Kaiser <mail@floriankaiser.org>
 * Copyright (c) 2023, Fabian Neundorf <CommodoreFabianus@gmx.de>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

// #include <AK/CharacterTypes.h>
// #include <AK/Forward.h>
// #include <AK/NonnullOwnPtr.h>
// #include <LibCore/Stream.h>
// #include <AK/CharacterTypes.h>
// #include <AK/Debug.h>
//
// #include <AK/GenericLexer.h>
//
// #include <AK/String.h>
// #include <AK/StringView.h>
// #include <AK/Utf8View.h>
// #include <LibUnicode/CharacterTypes.h>
// #include <stdio.h>

#include "Tokenizer.h"

namespace basic {

Vector<Token> Tokenizer::tokenize()
{
    Vector<Token> tokens;

    size_t last_position = 0;

    while (!is_eof()) {
        while (!is_eof() && current_char() != '\n' && AK::is_ascii_blank(current_char())) {
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
                    m_position++;
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

};
