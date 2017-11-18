# `Functional Ascent of Turtles`
---

A series of software design kata inspired heavilty by Scott Wlaschin's talk *[Thirteen Ways of looking at a Turtle
](https://fsharpforfunandprofit.com/turtle/)*. 

 * Consider composition with list monad (or applicative functor), which would allow easy modelling of several turtles simultaneously.

## Dependencies

All examples will require:

 * Phil Nash's unit testing library: [Catch](https://github.com/philsquared/Catch)
 * Compile time dimensional units library: [units](https://github.com/nholthaus/units)

Individual examples may have additional dependencies, to be found in their respective READEMEs.

## Description:

OO handles state, errors and logging. We don't want to handle state in an object so we use functions. Pipes example shows how we can use composition on functions to handle state, but it doesn't do logging or error handling. The Writer monad helps us take care of logging along with the state, but doesn't do error handling. The optional-monad allows us to handle errors, but the OO monad let us have more specific errors. The either monad allows us to pull from a set of errors in an error type. But neither optional nor either handles logging. we have to combine monads for that.


In the literature, you'll find very little. There is currently one introductory book in press[^FPCPP], and a smattering of academic papers [...]. There is one major peer reviewed library that is now out of date [^Boost.Phoenix], and several informal libraries. Yet features from functional languages continue to diffuse into the modern C++ language standard. The people who want to do functional programming tend to use languages that directly support it, and not C++. So very little attention is focused on expressing functional concepts in C++ syntax.

[^Boost.Phoenix]: Boost.Phoenix
[^FPCPP]: https://www.manning.com/books/functional-programming-in-cplusplus
[^Udemy]: https://www.udemy.com/functional-programming-using-cpp/