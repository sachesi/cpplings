# If

`if` runs a block only when a condition is true, and `else` handles the other
case. The condition must be something that converts to `bool`. Conditions are
combined with `&&` (and), `||` (or) and `!` (not). Comparison is written `==`;
a single `=` assigns.

When one value is compared against many constants, a `switch` statement is often
clearer. Watch out: without a `break`, execution "falls through" into the next
`case`.

The conditional operator `condition ? a : b` picks one of two values. Both values
must have a common type.

## Further information

- [If statements](https://www.learncpp.com/cpp-tutorial/introduction-to-if-statements/)
- [Logical operators](https://www.learncpp.com/cpp-tutorial/logical-operators/)
- [Switch statements](https://www.learncpp.com/cpp-tutorial/switch-statement-basics/)
- [Switch fallthrough](https://www.learncpp.com/cpp-tutorial/switch-fallthrough-and-scoping/)
- [The conditional operator](https://www.learncpp.com/cpp-tutorial/the-conditional-operator/)
