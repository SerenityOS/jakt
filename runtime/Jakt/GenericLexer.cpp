/*
 * Copyright (c) 2020, Benoit Lormeau <blormeau@outlook.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <Jakt/Assertions.h>
#include <Jakt/CharacterTypes.h>
#include <Jakt/GenericLexer.h>
#include <Jakt/StringBuilder.h>

#ifndef KERNEL
#    include <Jakt/String.h>
#endif

namespace Jakt {
// Consume a number of characters
StringView GenericLexer::consume(size_t count)
{
    if (count == 0)
        return {};

    size_t start = m_index;
    size_t length = min(count, m_input.length() - m_index);
    m_index += length;

    return m_input.substring_view(start, length);
}

// Consume the rest of the input
StringView GenericLexer::consume_all()
{
    if (is_eof())
        return {};

    auto rest = m_input.substring_view(m_index, m_input.length() - m_index);
    m_index = m_input.length();
    return rest;
}

// Consume until a new line is found
StringView GenericLexer::consume_line()
{
    size_t start = m_index;
    while (!is_eof() && peek() != '\r' && peek() != '\n')
        m_index++;
    size_t length = m_index - start;

    consume_specific('\r');
    consume_specific('\n');

    if (length == 0)
        return {};
    return m_input.substring_view(start, length);
}

// Consume and return characters until `stop` is peek'd
StringView GenericLexer::consume_until(char stop)
{
    size_t start = m_index;
    while (!is_eof() && peek() != stop)
        m_index++;
    size_t length = m_index - start;

    if (length == 0)
        return {};
    return m_input.substring_view(start, length);
}

// Consume and return characters until the string `stop` is found
StringView GenericLexer::consume_until(char const* stop)
{
    size_t start = m_index;
    while (!is_eof() && !next_is(stop))
        m_index++;
    size_t length = m_index - start;

    if (length == 0)
        return {};
    return m_input.substring_view(start, length);
}

// Consume and return characters until the string `stop` is found
StringView GenericLexer::consume_until(StringView stop)
{
    size_t start = m_index;
    while (!is_eof() && !next_is(stop))
        m_index++;
    size_t length = m_index - start;

    if (length == 0)
        return {};
    return m_input.substring_view(start, length);
}

/*
 * Consume a string surrounded by single or double quotes. The returned
 * StringView does not include the quotes. An escape character can be provided
 * to capture the enclosing quotes. Please note that the escape character will
 * still be in the resulting StringView
 */
StringView GenericLexer::consume_quoted_string(char escape_char)
{
    if (!next_is(is_quote))
        return {};

    char quote_char = consume();
    size_t start = m_index;
    while (!is_eof()) {
        if (next_is(escape_char))
            m_index++;
        else if (next_is(quote_char))
            break;
        m_index++;
    }
    size_t length = m_index - start;

    if (peek() != quote_char) {
        // Restore the index in case the string is unterminated
        m_index = start - 1;
        return {};
    }

    // Ignore closing quote
    ignore();

    return m_input.substring_view(start, length);
}

}
