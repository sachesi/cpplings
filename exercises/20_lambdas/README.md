# Lambdas

A lambda expression creates an unnamed function object right where it's needed:

    auto add = [](int a, int b) { return a + b; };

The square brackets list the *captures*: variables from the surrounding scope that
the lambda can use. `[x]` copies `x` into the lambda when it's created, `[&x]`
refers to the original variable. `[=]` and `[&]` capture everything that's used,
by copy or by reference. A lambda that changes its own copies must be `mutable`.

Every lambda has its own unique type. To store different callables in the same
variable or container, use `std::function`.

## Further information

- [Introduction to lambdas](https://www.learncpp.com/cpp-tutorial/introduction-to-lambdas-anonymous-functions/)
- [Lambda captures](https://www.learncpp.com/cpp-tutorial/lambda-captures/)
- [std::function](https://en.cppreference.com/w/cpp/utility/functional/function)
