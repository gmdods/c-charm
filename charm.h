#ifndef CHARM_MACROS_H
#define CHARM_MACROS_H

// indirection pattern
#define CAT(lhs, rhs) lhs##rhs
#define CONCAT(lhs, rhs) CAT(lhs, rhs)
#define STRING(macro) #macro

#define CHAR(c) C_##c
#define CHAR_S(c) (C_##c)
#define CHAR_P(c) (c, C_##c)

#define EMPTY()
#define ID(c) c
#define EXPAND(x) x
#define COMMA() ,
#define LPAREN (
#define RPAREN )

#define cases(F) F(CHAR, : case)
#if __has_attribute(fallthrough)
#define fallthrough __attribute__((fallthrough))
#else
#define fallthrough ((void) 0)
#endif

#define PAREN_OR() ) | (
#define PAREN_AND() ) & (
#define anyof(var, F) \
	(LPAREN EXPAND(EMPTY F(()(var) == CHAR_S, PAREN_OR)) RPAREN)
#define noneof(var, F) \
	(LPAREN EXPAND(EMPTY F(()(var) != CHAR_S, PAREN_AND)) RPAREN)

#define list(Fn, F) EXPAND(EMPTY F(() Fn CHAR_P, COMMA))

#endif // !CHARM_MACROS_H

#ifndef CHARM_H
#define CHARM_H

#include <string.h>

#ifndef char8_t
typedef unsigned char char8_t;
#endif // !char8_t

enum chars {
	C_SPACE = ' ',
	C_TAB = '\t',
	C_CR = '\r',
	C_FEED = '\f',
	C_VTAB = '\v',
	C_LF = '\n',
	C_LOWER_A = 'a',
	C_LOWER_B = 'b',
	C_LOWER_C = 'c',
	C_LOWER_D = 'd',
	C_LOWER_E = 'e',
	C_LOWER_F = 'f',
	C_LOWER_G = 'g',
	C_LOWER_H = 'h',
	C_LOWER_I = 'i',
	C_LOWER_J = 'j',
	C_LOWER_K = 'k',
	C_LOWER_L = 'l',
	C_LOWER_M = 'm',
	C_LOWER_N = 'n',
	C_LOWER_O = 'o',
	C_LOWER_P = 'p',
	C_LOWER_Q = 'q',
	C_LOWER_R = 'r',
	C_LOWER_S = 's',
	C_LOWER_T = 't',
	C_LOWER_U = 'u',
	C_LOWER_V = 'v',
	C_LOWER_W = 'w',
	C_LOWER_X = 'x',
	C_LOWER_Y = 'y',
	C_LOWER_Z = 'z',
	C_UPPER_A = 'A',
	C_UPPER_B = 'B',
	C_UPPER_C = 'C',
	C_UPPER_D = 'D',
	C_UPPER_E = 'E',
	C_UPPER_F = 'F',
	C_UPPER_G = 'G',
	C_UPPER_H = 'H',
	C_UPPER_I = 'I',
	C_UPPER_J = 'J',
	C_UPPER_K = 'K',
	C_UPPER_L = 'L',
	C_UPPER_M = 'M',
	C_UPPER_N = 'N',
	C_UPPER_O = 'O',
	C_UPPER_P = 'P',
	C_UPPER_Q = 'Q',
	C_UPPER_R = 'R',
	C_UPPER_S = 'S',
	C_UPPER_T = 'T',
	C_UPPER_U = 'U',
	C_UPPER_V = 'V',
	C_UPPER_W = 'W',
	C_UPPER_X = 'X',
	C_UPPER_Y = 'Y',
	C_UPPER_Z = 'Z',
	C_DIGIT_0 = '0',
	C_DIGIT_1 = '1',
	C_DIGIT_2 = '2',
	C_DIGIT_3 = '3',
	C_DIGIT_4 = '4',
	C_DIGIT_5 = '5',
	C_DIGIT_6 = '6',
	C_DIGIT_7 = '7',
	C_DIGIT_8 = '8',
	C_DIGIT_9 = '9',
	C_OPEN_PAREN = '(',
	C_OPEN_SQUARE = '[',
	C_OPEN_BRACES = '{',
	C_CLOSE_PAREN = ')',
	C_CLOSE_SQUARE = ']',
	C_CLOSE_BRACES = '}',
	C_SEMICOLON = ';',
	C_COLON = ':',
	C_PERIOD = '.',
	C_COMMA = ',',
	C_BACKTICK = '`',
	C_QUOTE = '\'',
	C_DOUBLE_QUOTE = '\"',
	C_EQUAL = '=',
	C_LEFT_ANGLE = '<',
	C_RIGHT_ANGLE = '>',
	C_TILDE = '~',
	C_EXCLAMATION = '!',
	C_PERCENT = '%',
	C_CARAT = '^',
	C_AMPERSAND = '&',
	C_ASTERISK = '*',
	C_UNDERSCORE = '_',
	C_HYPHEN = '-',
	C_PLUS = '+',
	C_PIPE = '|',
	C_SLASH = '/',
	C_DOLLAR = '$',
	C_BACKSLASH = '\\',
	C_AT = '@',
	C_HASH = '#',
	C_QUESTION = '?',
	C_ASCII = 0x7f,
	C_UTF8 = 0xc0,
	C_BYTE = 0x100,
};

#define lowers(X, S) \
	X(LOWER_A) \
	S X(LOWER_B) \
	S X(LOWER_C) \
	S X(LOWER_D) \
	S X(LOWER_E) \
	S X(LOWER_F) \
	S X(LOWER_G) \
	S X(LOWER_H) \
	S X(LOWER_I) \
	S X(LOWER_J) \
	S X(LOWER_K) \
	S X(LOWER_L) \
	S X(LOWER_M) \
	S X(LOWER_N) \
	S X(LOWER_O) \
	S X(LOWER_P) \
	S X(LOWER_Q) \
	S X(LOWER_R) \
	S X(LOWER_S) \
	S X(LOWER_T) \
	S X(LOWER_U) \
	S X(LOWER_V) \
	S X(LOWER_W) \
	S X(LOWER_X) \
	S X(LOWER_Y) \
	S X(LOWER_Z)

#define uppers(X, S) \
	X(UPPER_A) \
	S X(UPPER_B) \
	S X(UPPER_C) \
	S X(UPPER_D) \
	S X(UPPER_E) \
	S X(UPPER_F) \
	S X(UPPER_G) \
	S X(UPPER_H) \
	S X(UPPER_I) \
	S X(UPPER_J) \
	S X(UPPER_K) \
	S X(UPPER_L) \
	S X(UPPER_M) \
	S X(UPPER_N) \
	S X(UPPER_O) \
	S X(UPPER_P) \
	S X(UPPER_Q) \
	S X(UPPER_R) \
	S X(UPPER_S) \
	S X(UPPER_T) \
	S X(UPPER_U) \
	S X(UPPER_V) \
	S X(UPPER_W) \
	S X(UPPER_X) \
	S X(UPPER_Y) \
	S X(UPPER_Z)

#define alphas(X, S) lowers(X, S) S uppers(X, S)

#define digits(X, S) \
	X(DIGIT_0) \
	S X(DIGIT_1) \
	S X(DIGIT_2) \
	S X(DIGIT_3) \
	S X(DIGIT_4) \
	S X(DIGIT_5) \
	S X(DIGIT_6) \
	S X(DIGIT_7) \
	S X(DIGIT_8) \
	S X(DIGIT_9)

#define alphadigits(X, S) alphas(X, S) S digits(X, S)

#define blanks(X, S) X(SPACE) S X(TAB)

#define linespaces(X, S) \
	blanks(X, S) S X(CR) \
	S X(FEED) \
	S X(VTAB)
#define spaces(X, S) linespaces(X, S) S X(LF)

#define openbrackets(X, S) \
	X(OPEN_PAREN) S X(OPEN_SQUARE) \
	S X(OPEN_BRACES)
#define closebrackets(X, S) \
	X(CLOSE_PAREN) S X(CLOSE_SQUARE) \
	S X(CLOSE_BRACES)
#define brackets(X, S) openbrackets(X, S) S closebrackets(X, S)

#define points(X, S) \
	X(SEMICOLON) S X(COLON) \
	S X(PERIOD) \
	S X(COMMA)

#define quotes(X, S) \
	X(BACKTICK) S X(QUOTE) \
	S X(DOUBLE_QUOTE)

#define compares(X, S) \
	X(EQUAL) S X(LEFT_ANGLE) \
	S X(RIGHT_ANGLE)

#define mathematics(X, S) \
	X(TILDE) \
	S X(EXCLAMATION) \
	S X(PERCENT) \
	S X(CARAT) \
	S X(AMPERSAND) \
	S X(ASTERISK) \
	S X(UNDERSCORE) \
	S X(HYPHEN) \
	S X(PLUS) \
	S X(PIPE) \
	S X(SLASH)

#define punctuations(X, S) \
	brackets(X, S) S points(X, S) \
	S quotes(X, S) \
	S mathematics(X, S) \
	S compares(X, S) \
	S X(DOLLAR) \
	S X(BACKSLASH) \
	S X(AT) \
	S X(HASH) \
	S X(QUESTION)

#define graphs(X, S) alphadigits(X, S) S punctuations(X, S)

#define idents(X, S) alphas(X, S) S X(UNDERSCORE)

#define lexemes(X, S) idents(X, S) S digits(X, S)

#define startswith(str, literal) \
	(strncmp((char *) str, literal, sizeof(literal) - 1) == 0)
#define exactly(str, literal, n) \
	(((n) == (sizeof(literal) - 1)) && startswith(str, literal))

#endif // !CHARM_H
