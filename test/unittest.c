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
						"let letter = 'a';";
	enum tags { LET, IDENT, EQUAL, DECIMAL, CHAR, SEMICOLON };
	const struct token {
		enum tags tag;
		const char8_t * ptr;
		size_t length;
	} expected[] = {
	    {LET, str + 0, 3},	      {IDENT, str + 4, 3},
	    {EQUAL, str + 8, 1},      {DECIMAL, str + 10, 2},
	    {SEMICOLON, str + 12, 1}, {LET, str + 14, 3},
	    {IDENT, str + 18, 6},     {EQUAL, str + 25, 1},
	    {CHAR, str + 28, 1},      {SEMICOLON, str + 30, 1},
	};
#define ensure_token(a, b) ensure(memcmp(&(a), &(b), sizeof(struct token)) == 0)

	char8_t c = '\0';
	size_t index = 0;
	size_t linenum = 0, lineindex = 0;
	for (const char8_t *it = str, *ptr = 0;;)
		switch (c = *it) {
		case cases(linespaces): ++it; break;
		case '\n':
			++it, ++linenum;
			lineindex = it - str;
			break;
		case '=':
			ensure_token(expected[index++],
				     ((struct token){EQUAL, it, 1}));
			++it;
			break;
		case ';':
			ensure_token(expected[index++],
				     ((struct token){SEMICOLON, it, 1}));
			++it;
			break;
		case '\'':
			for (ptr = ++it; (c = *it) && (c != '\''); ++it)
				;
			ensure_token(expected[index++],
				     ((struct token){CHAR, ptr, it - ptr}));
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
	ensure(linenum == 1), ensure(lineindex == 14);
}
