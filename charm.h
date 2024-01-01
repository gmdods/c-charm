#ifndef CHARM_MACROS_H
#define CHARM_MACROS_H

// indirection pattern
#define CAT(lhs, rhs) lhs##rhs
#define CONCAT(lhs, rhs) CAT(lhs, rhs)
#define STRING(macro) #macro

#define EMPTY()
#define COMMA() ,
#define ID(c) c
#define LPAREN (
#define RPAREN )
#define LPAREN_S(x) ( (x)
#define RPAREN_S(x) (x) )
#define EXPAND(x) x
#define SINGLE(x, y) (y)

#define cases(F) F(SINGLE, : case)
#define fallthrough ((void) 0)

#define anyof(var, F) (EXPAND(LPAREN F((var) == RPAREN_S SINGLE, | LPAREN_S)))
#define noneof(var, F) (EXPAND(LPAREN F((var) != RPAREN_S SINGLE, &LPAREN_S)))

#define toenum(n, x) n = x
#define enumerate(F) EXPAND(EMPTY F(() toenum, COMMA))

#define many(F) EXPAND(EMPTY F((), COMMA))

#endif // !CHARM_MACROS_H

#ifndef CHARM_H
#define CHARM_H

#include <uchar.h>
#ifndef char8_t
typedef unsigned char char8_t;
#endif // !char8_t

#define lowers(X, S) \
	X(LOWER_A, 'a') \
	S X(LOWER_B, 'b') S X(LOWER_C, 'c') S X(LOWER_D, 'd') \
	    S X(LOWER_E, 'e') S X(LOWER_F, 'f') S X(LOWER_G, 'g') \
		S X(LOWER_H, 'h') S X(LOWER_I, 'i') S X(LOWER_J, 'j') \
		    S X(LOWER_K, 'k') S X(LOWER_L, 'l') S X(LOWER_M, 'm') \
			S X(LOWER_N, 'n') S X(LOWER_O, 'o') S X(LOWER_P, 'p') \
			    S X(LOWER_Q, 'q') S X(LOWER_R, 'r') \
				S X(LOWER_S, 's') S X(LOWER_T, 't') \
				    S X(LOWER_U, 'u') S X(LOWER_V, 'v') \
					S X(LOWER_W, 'w') S X(LOWER_X, 'x') \
					    S X(LOWER_Y, 'y') \
						S X(LOWER_Z, 'z')

#define uppers(X, S) \
	X(UPPER_A, 'A') \
	S X(UPPER_B, 'B') S X(UPPER_C, 'C') S X(UPPER_D, 'D') \
	    S X(UPPER_E, 'E') S X(UPPER_F, 'F') S X(UPPER_G, 'G') \
		S X(UPPER_H, 'H') S X(UPPER_I, 'I') S X(UPPER_J, 'J') \
		    S X(UPPER_K, 'K') S X(UPPER_L, 'L') S X(UPPER_M, 'M') \
			S X(UPPER_N, 'N') S X(UPPER_O, 'O') S X(UPPER_P, 'P') \
			    S X(UPPER_Q, 'Q') S X(UPPER_R, 'R') \
				S X(UPPER_S, 'S') S X(UPPER_T, 'T') \
				    S X(UPPER_U, 'U') S X(UPPER_V, 'V') \
					S X(UPPER_W, 'W') S X(UPPER_X, 'X') \
					    S X(UPPER_Y, 'Y') \
						S X(UPPER_Z, 'Z')

#define alphas(X, S) lowers(X, S) S uppers(X, S)

#define digits(X, S) \
	X(DIGIT_0, '0') \
	S X(DIGIT_1, '1') S X(DIGIT_2, '2') S X(DIGIT_3, '3') \
	    S X(DIGIT_4, '4') S X(DIGIT_5, '5') S X(DIGIT_6, '6') \
		S X(DIGIT_7, '7') S X(DIGIT_8, '8') S X(DIGIT_9, '9')

#define alphadigits(X, S) alphas(X, S) S digits(X, S)

#define blanks(X, S) X(SPACE, ' ') S X(TAB, '\t')

#define linespaces(X, S) \
	blanks(X, S) S X(CR, '\r') S X(FEED, '\f') S X(VTAB, '\v')
#define spaces(X, S) linespaces(X, S) S X(LF, '\n')

#define openbrackets(X, S) \
	X(OPEN_PAREN, '(') S X(OPEN_SQUARE, '[') S X(OPEN_BRACES, '{')
#define closebrackets(X, S) \
	X(CLOSE_PAREN, ')') S X(CLOSE_SQUARE, ']') S X(CLOSE_BRACES, '}')
#define brackets(X, S) openbrackets(X, S) S closebrackets(X, S)

#define points(X, S) \
	X(SEMICOLON, ';') S X(COLON, ':') S X(PERIOD, '.') S X(COMMA, ',')

#define quotes(X, S) X(BACKTICK, '`') S X(QUOTE, '\'') S X(DOUBLE_QUOTE, '\"')

#define mathematics(X, S) \
	X(TILDE, '~') \
	S X(EXCLAMATION, '!') S X(PERCENT, '%') S X(CARAT, '^') \
	    S X(AMPERSAND, '&') S X(ASTERISK, '*') S X(UNDERSCORE, '_') \
		S X(HYPHEN, '-') S X(EQUAL, '=') S X(PLUS, '+') S X(PIPE, '|') \
		    S X(LEFT_ANGLE, '<') S X(RIGHT_ANGLE, '>') S X(SLASH, '/')

#define punct(X, S) \
	brackets(X, S) S points(X, S) \
	S quotes(X, S) \
	S mathematics(X, S) \
	S X(DOLLAR, '$') S X(BACKSLASH, '\\') S X(AT, '@') S X(HASH, '#') \
	    S X(QUESTION, '?')

#define graphs(X, S) alphadigits(X, S) S punct(X, S)

#define idents(X, S) alphas(X, S) S X(UNDERSCORE, '_')

#define lexemes(X, S) idents(X, S) S digits(X, S)

#define startswith(str, literal) \
	(strncmp((char *) str, literal, sizeof(literal) - 1) == 0)
#define exactly(str, literal, n) \
	(((n) == (sizeof(literal) - 1)) && startswith(str, literal))

#endif // !CHARM_H
