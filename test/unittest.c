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
						"if (var <= 32)\n"
						"\tvar + (letter - 'a') * 3\n"
						"else 30";
	enum tags {
		LET,
		IF,
		ELSE,
		IDENT = 'i',
		DECIMAL = 'd',
		enumerate(, punct), // add namespace
	};

	const struct token {
		enum tags tag;
		const char8_t * ptr;
		size_t span;
	} expected[] = {
	    {LET, str + 0, 3},	  {IDENT, str + 4, 3},
	    {'=', str + 8, 1},	  {DECIMAL, str + 10, 2},
	    {';', str + 12, 1},	  {LET, str + 14, 3},
	    {IDENT, str + 18, 6}, {'=', str + 25, 1},
	    {'\'', str + 28, 1},  {';', str + 30, 1},
	    {IF, str + 32, 2},	  {'(', str + 35, 1},
	    {IDENT, str + 36, 3}, {'<', str + 40, 1},
	    {'=', str + 41, 1},	  {DECIMAL, str + 43, 2},
	    {')', str + 45, 1},	  {IDENT, str + 48, 3},
	    {'+', str + 52, 1},	  {'(', str + 54, 1},
	    {IDENT, str + 55, 6}, {'-', str + 62, 1},
	    {'\'', str + 65, 1},  {')', str + 67, 1},
	    {'*', str + 69, 1},	  {DECIMAL, str + 71, 1},
	    {ELSE, str + 73, 4},  {DECIMAL, str + 78, 2},
	};
#define ensure_token(a, b) \
	ensure(((a).tag == (b).tag) & ((a).ptr == (b).ptr) & \
	       ((a).span == (b).span))

	char8_t c = '\0', q = '\0';
	size_t index = 0;
	size_t linenum = 0, lineindex = 0;
	struct token ret = {0};
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
			ret = (struct token){c, it, 1};
			ensure_token(expected[index], ret), ++index;
			++it;
			break;
		case cases(quotes):
			for (ptr = ++it, q = c; (c = *it) && (c != q); ++it)
				;
			ret = (struct token){q, ptr, it - ptr};
			ensure_token(expected[index], ret), ++index;
			++it;
			break;
		case cases(alphas):
			for (ptr = it; (c = *(++it)) && anyof(c, lexemes);)
				;

			if (exactly(ptr, "let", it - ptr))
				ret = (struct token){LET, ptr, it - ptr};
			else if (exactly(ptr, "if", it - ptr))
				ret = (struct token){IF, ptr, it - ptr};
			else if (exactly(ptr, "else", it - ptr))
				ret = (struct token){ELSE, ptr, it - ptr};
			else
				ret = (struct token){IDENT, ptr, it - ptr};
			ensure_token(expected[index], ret), ++index;
			break;
		case cases(digits):
			for (ptr = it; (c = *(++it)) && anyof(c, digits);)
				;
			ret = (struct token){DECIMAL, ptr, it - ptr};
			ensure_token(expected[index], ret), ++index;
			break;
		default: ensure(false); break;
		case '\0': goto token_ret;
		}
token_ret:;
	ensure(linenum == 4), ensure(lineindex == 73);
}
