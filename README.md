# `Functional Ascent of Turtles`
---

***Abstract:** Inspired by [CrossWing's](http://www.crosswing.com/) turtle command interface for [virtualME](http://www.crosswing.com/virtualme.html) and by Scott Wlaschin's talk *[Thirteen Ways of looking at a Turtle](https://fsharpforfunandprofit.com/turtle/)*, we explore a series of approaches to implementing a basic move/turn command interface using functional programming techniques in C++*


## Dependencies

All examples will require:

 * Cmake for building.
 * Phil Nash's unit testing library: [Catch](https://github.com/philsquared/Catch)
 * Compile time dimensional units library: [units](https://github.com/nholthaus/units)

Individual examples may have additional dependencies, to be found in their respective READEMEs.


### Compiler and STL requirements

  * Currently I'm compiling with Clang++-6.0 trunk and libc++-6.0
  * `-std=c++17`
  * `std::variant` and support functions, including `std::variant_alternative_t` (which seems to be broken in GCC 7.0.1).
  * `std::optional` and friends.


## Introduction:

Functional programming, simply put, is programming constrained by mathematical relationships. Procedures and data are both treated algebraically and on an equal footing—procedures can be assigned to variables, passed as arguments and returned from other procedures. Complexity is built by structured and lawful composition and the emergent behaviour can be understood by equational reasoning. Mathematical expressions called denotations can describe the meanings of expressions in the programming language. Programs can be derived mathematically and implemented in a way maintains much of the mathematical structure.

Programming in this way has many consequences to software quality and engineering design. However, this style of programming is most often exercised in higher level languages that explicitly support this mathematical style. At this time, there seems to be very little literature exploring the use of functional programming in languages positioned closer to the hardware like C++. C++ is used ubiquitously in demanding systems applications and it is precisely those applications which have the most to gain from the structure and clarity that functional programming can offer. However, there are consequences in performance that must be considered, and when a language doesn't have direct support for functional programming. Functional code can be *herder* to understand because the syntax obscures the meaning of the code. So there is a balance that needs to be struck, rather than a wholesale exchange of imperative style for functional style.

For the engineer using C++ and looking for that balance, there is something of a poverty of resources. There is currently one introductory book in press[^FPCPP], and a smattering of academic papers [...]. There is one major peer reviewed library that is now out of date [^Boost.Phoenix], and several informal libraries under open source licenses. Yet features from functional languages continue to diffuse into the modern C++ standard. Perhaps the most notable example is the introduction of *lambda functions* from Church's lambda calculus, which is basis for the syntax of all functional languages. The code in this repository makes heavy use of new additions to the standard library such as tuples and variants, which enable algebraic construction of data structures.

In the present exploration, we investigate the ability of the upcoming C++ language standard to express functional programming algebras in a clear and usable manner. Familiarity with C++11 is assumed along with some level of mathematical acumen. However, key concepts in functional programming will be introduced as needed.

The remaining sections of this document introduce some concepts that are used generally among the code examples in this repository. Each example has its own subdirectory that contains a `README.md` that details the theory and discusses the concepts showcased therein.

This repository should be consumed in the following order:
  1. README.md (This document)
  1. oo-turtle/README.md
  1. pipes-turtle/README.md
  1. optional-monad-turtle/README.md
  1. either-monad-turtle/README.md
  1. writer-monad-turtle/README.md (then maybe writer-class-turtle/README.md)
  1. writer-either-monad-turtle/README.md
  1. command-turtle/README.md
  1. command-writer-either-turtle/README.md

## The algebra of programs

Representable data types are viewed through type algebra as sets where each type is the set of values 


[^FPCPP]: Ivan Čukić (2018) Functional Programming in C++. Manning Publications. ISBN 9781617293818 <https://www.manning.com/books/functional-programming-in-cplusplus>

[^Boost.Phoenix]: Boost.Phoenix: https://theboostcpplibraries.com/boost.phoenix

[^Udemy]: https://www.udemy.com/functional-programming-using-cpp/