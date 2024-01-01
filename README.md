# c-charm
A macro library for characters in C

This defines characters sets and macro operations, include:

- `cases`: Expand to fallthrough cases.
- `anyof/noneof`: Expand to many or-equals, resp. and-not-equals.
- `list`: Comma-separated list, can be used to define `enum`s.

Note that one can override the names via `#define`.

[For more macro magic](https://github.com/pfultz2/Cloak/wiki/C-Preprocessor-tricks,-tips,-and-idioms)

