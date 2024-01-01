#ifndef UNITTEST_MAIN
#include "unittest.h"
#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "../charm.h"

#endif /* ifndef UNITTEST_MAIN */

unittest("switch") {
	const char8_t * str = (const char8_t *) "abc01";
	for (const char8_t * it = str;; ++it)
		switch (*it) {
		case cases(alphas): ensure(isalpha(*it)); break;
		case cases(digits): ensure(isdigit(*it)); break;
		default: ensure(false); break;
		case '\0': goto switch_end;
		}
switch_end:;
}

unittest("anyof") {
	bool d = anyof('a', digits);
	bool u = noneof('a', uppers);
	ensure(!d), ensure(u);
}

unittest("lexer") {

	const char8_t * str = (const char8_t *) "let var = 30;\n"
						"let letter = 'a';\n"
						"var + (letter - 'a') * 3";
	enum tags {
		LET,
		IDENT,
		DECIMAL,
		enumerate(punct),
	};
	const struct token {
		enum tags tag;
		const char8_t * ptr;
		size_t length;
	} expected[] = {
	    {LET, str + 0, 3},		{IDENT, str + 4, 3},
	    {EQUAL, str + 8, 1},	{DECIMAL, str + 10, 2},
	    {SEMICOLON, str + 12, 1},	{LET, str + 14, 3},
	    {IDENT, str + 18, 6},	{EQUAL, str + 25, 1},
	    {QUOTE, str + 28, 1},	{SEMICOLON, str + 30, 1},
	    {IDENT, str + 32, 3},	{PLUS, str + 36, 1},
	    {OPEN_PAREN, str + 38, 1},	{IDENT, str + 39, 6},
	    {HYPHEN, str + 46, 1},	{QUOTE, str + 49, 1},
	    {CLOSE_PAREN, str + 51, 1}, {ASTERISK, str + 53, 1},
	    {DECIMAL, str + 55, 1},
	};
#define ensure_token(a, b) ensure(memcmp(&(a), &(b), sizeof(struct token)) == 0)

	char8_t c = '\0', q = '\0';
	size_t index = 0;
	size_t linenum = 0, lineindex = 0;
	for (const char8_t *it = str, *ptr = 0;;)
		switch (c = *it) {
		case cases(linespaces): ++it; break;
		case '\n':
			++it, ++linenum;
			lineindex = it - str;
			break;
		case '#': // Comment
			while ((c = *(++it)) && (c != '\n'))
				;
			++it;
			break;
		case cases(mathematics):
		case cases(points):
		case cases(brackets):
			ensure_token(expected[index++],
				     ((struct token){c, it, 1}));
			++it;
			break;
		case cases(quotes):
			for (ptr = ++it, q = c; (c = *it) && (c != q); ++it)
				;
			ensure_token(expected[index++],
				     ((struct token){q, ptr, it - ptr}));
			++it;
			break;
		case cases(alphas):
			for (ptr = it; (c = *(++it)) && anyof(c, lexemes);)
				;
			if (exactly(ptr, "let", it - ptr))
				ensure_token(
				    expected[index++],
				    ((struct token){LET, ptr, it - ptr}));
			else
				ensure_token(
				    expected[index++],
				    ((struct token){IDENT, ptr, it - ptr}));
			break;
		case cases(digits):
			for (ptr = it; (c = *(++it)) && anyof(c, digits);)
				;
			ensure_token(expected[index++],
				     ((struct token){DECIMAL, ptr, it - ptr}));
			break;
		default: ensure(false); break;
		case '\0': goto token_ret;
		}
token_ret:
	ensure(linenum == 2), ensure(lineindex == 32);
}
