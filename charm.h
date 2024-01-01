#ifndef CHARM_MACROS_H
#define CHARM_MACROS_H

// indirection pattern
#define CAT(lhs, rhs) lhs##rhs
#define CONCAT(lhs, rhs) CAT(lhs, rhs)
#define STRING(macro) #macro

#define COMMA ,
#define ID(c) c
#define LPAREN (
#define RPAREN )
#define LPAREN_S(x) ( (x)
#define RPAREN_S(x) (x) )
#define EXPAND(x) (x)

#define cases(F) F(ID, : case)
#define fallthrough ((void) 0)

#define anyof(var, F) EXPAND(LPAREN F((var) == RPAREN_S, | LPAREN_S))
#define noneof(var, F) EXPAND(LPAREN F((var) != RPAREN_S, &LPAREN_S))

#define many(F) F(ID, COMMA)

#endif // !CHARM_MACROS_H

#ifndef CHARM_H
#define CHARM_H

#include <uchar.h>
#ifndef char8_t
typedef unsigned char char8_t;
#endif // !char8_t

#define lowers(X, S) \
	X('a') \
	S X('b') S X('c') S X('d') S X('e') S X('f') S X('g') S X('h') \
	    S X('i') S X('j') S X('k') S X('l') S X('m') S X('n') S X('o') \
		S X('p') S X('q') S X('r') S X('s') S X('t') S X('u') S X('v') \
		    S X('w') S X('x') S X('y') S X('z')

#define uppers(X, S) \
	X('A') \
	S X('B') S X('C') S X('D') S X('E') S X('F') S X('G') S X('H') \
	    S X('I') S X('J') S X('K') S X('L') S X('M') S X('N') S X('O') \
		S X('P') S X('Q') S X('R') S X('S') S X('T') S X('U') S X('V') \
		    S X('W') S X('X') S X('Y') S X('Z')

#define alphas(X, S) lowers(X, S) S uppers(X, S)

#define digits(X, S) \
	X('0') \
	S X('1') S X('2') S X('3') S X('4') S X('5') S X('6') S X('7') \
	    S X('8') S X('9')

#define alphadigits(X, S) alphas(X, S) S digits(X, S)

#define blanks(X, S) X(' ') S X('\t')

#define linespaces(X, S) blanks(X, S) S X('\r') S X('\f') S X('\v')
#define spaces(X, S) linespaces(X, S) S X('\n')

#define punct(X, S) \
	X('`') \
	S X('~') S X('!') S X('@') S X('#') S X('$') S X('%') S X('^') \
	    S X('&') S X('*') S X('(') S X(')') S X('_') S X('-') S X('=') \
		S X('+') S X('[') S X('{') S X(']') S X('}') S X('\\') \
		    S X('|') S X(';') S X(':') S X('\'') S X('\"') S X(',') \
			S X('<') S X('.') S X('>') S X('/') S X('?')

#define graphs(X, S) alphadigits(X, S) S punct(X, S)

#define idents(X, S) alphas(X, S) S X('_')

#define lexemes(X, S) idents(X, S) S digits(X, S)

#define startswith(str, literal) \
	(strncmp((char *) str, literal, sizeof(literal) - 1) == 0)
#define exactly(str, literal, n) \
	(((n) == (sizeof(literal) - 1)) && startswith(str, literal))

#endif // !CHARM_H
