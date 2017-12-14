# `Functional Ascent of Turtles`
---

***Abstract:** Inspired by [CrossWing's](http://www.crosswing.com/) turtle command interface for [virtualME](http://www.crosswing.com/virtualme.html) and by Scott Wlaschin's talk *[Thirteen Ways of looking at a Turtle](https://fsharpforfunandprofit.com/turtle/)*, this series explores the various approaches to implementing a basic move/turn control/command interface using functional programming techniques in C++*

<!-- @import "[TOC]" {cmd="toc" depthFrom=1 depthTo=6 orderedList=false} -->
<!-- code_chunk_output -->

* [`Functional Ascent of Turtles`](#functional-ascent-of-turtles)
	* [Introduction](#introduction)
		* [The turtle problem](#the-turtle-problem)
	* [Overview](#overview)
		* [1. oo-turtle](#1-oo-turtle)
		* [2. pipes-turtle](#2-pipes-turtle)
		* [3. optional-monad-turtle](#3-optional-monad-turtle)
		* [4. either-monad-turtle](#4-either-monad-turtle)
		* [5. writer-monad-turtle](#5-writer-monad-turtle)
			* [5.1 writer-class-turtle](#51-writer-class-turtle)
		* [6. writer-either-monad-turtle](#6-writer-either-monad-turtle)
		* [7. command-turtle](#7-command-turtle)
		* [8. command-writer-either-turtle](#8-command-writer-either-turtle)
		* [9. promise-monad-turtle](#9-promise-monad-turtle)
		* [10. actor-promise-turtle](#10-actor-promise-turtle)
		* [11. frp-turtle](#11-frp-turtle)
	* [Theoretical background: the algebra of programs](#theoretical-background-the-algebra-of-programs)
		* [Product types and the Cartesian product](#product-types-and-the-cartesian-product)
		* [Sum types and the tagged union](#sum-types-and-the-tagged-union)
		* [A quick example of type algebraic construction](#a-quick-example-of-type-algebraic-construction)
		* [Exponentiation, function types and currying.](#exponentiation-function-types-and-currying)
	* [The Tutrtle problem](#the-tutrtle-problem)
	* [Dependencies](#dependencies)
		* [Compiler and STL requirements](#compiler-and-stl-requirements)
	* [Building:](#building)
		* [Groundwork: Common code for all cases](#groundwork-common-code-for-all-cases)

<!-- /code_chunk_output -->

## Introduction

Functional programming, simply put, is programming constrained by mathematical relationships. Procedures and data are both treated algebraically and on an equal footing—procedures can be assigned to variables, passed as arguments and returned from other procedures. Complexity is built by structured and lawful composition and the emergent behaviour can be understood by equational reasoning. Mathematical expressions called denotations can describe the meanings of expressions in the programming language. Programs can be derived mathematically and implemented in a way maintains much of the mathematical structure.

Programming in this way has many consequences to software quality and engineering design[^namely]. However, this style of programming is most often exercised in higher level languages that explicitly support this mathematical style. That may explain the deficit of literature exploring the use of functional programming in languages positioned closer to the hardware like C++. C++ is used ubiquitously in demanding systems applications and it is precisely those applications which have the most to gain from the structure and clarity that functional programming can offer. However, there are consequences in performance that must be considered. Moreover, when a language doesn't have direct support for functional programming, functional code can be *herder* to understand because the syntax obscures the codified mathematical meaning. So there is a balance that needs to be struck, rather than a wholesale exchange of imperative style for functional style.

[^namely]: The relevant software engineering concerns reuse, separation of concerns and formal methods.

For the engineer using C++ and looking for that balance, there is a poverty of resources. There is currently one introductory book in press[^FPCPP], and a smattering of academic papers [...]. There is one major peer reviewed support library that is now out of date [^Boost.Phoenix], and several informal libraries under open source licenses. Still, features from functional languages continue to diffuse into the modern C++ standard. Perhaps the most notable example is the introduction of *lambda functions* from Church's lambda calculus, which is basis for the syntax of all functional languages. The code in this repository makes heavy use of new additions to the standard library such as tuples and variants, which enable algebraic construction of data structures.

The passages and code in this repository are a documented exercise in functional programming in C++. In it, I have explored some of the various trade-offs in striving for functional purity in an inherently impure language. The end result of this exercise will inform my design of a general research framework for Nonlinear Model Predictive Controllers. You may notice some of that bias in the coming passages.


### The turtle problem

I believe CrossWing and Wlaschin both take their inspiration from [Turtle graphics](https://en.wikipedia.org/wiki/Turtle_graphics), of which Wikipedia offers a very straightforward explanation:
> In computer graphics, turtle graphics are vector graphics using a relative cursor (the "turtle") upon a Cartesian plane. Turtle graphics is a key feature of the Logo programming language.[1]
> …
> The turtle has three attributes: a location, an orientation (or direction), and a pen. The pen, too, has attributes: color, width, and on/off state.
>
> The turtle moves with commands that are relative to its own position, such as "move forward 10 spaces" and "turn left 90 degrees". The pen carried by the turtle can also be controlled, by enabling it, setting its color, or setting its width. A student could understand (and predict and reason about) the turtle's motion by imagining what they would do if they were the turtle. Seymour Papert called this "body syntonic" reasoning.
>
> A full turtle graphics system requires control flow, procedures, and recursion: many turtle drawing programs fall short. From these building blocks one can build more complex shapes like squares, triangles, circles and other composite figures. The idea of turtle graphics, for example is useful in a Lindenmayer system for generating fractals.
>
> Turtle geometry is also sometimes used in graphics environments as an alternative to a strictly coordinate-addressed graphics system.

Since the turtle interface in this project is inspired by a robotic interface, I've no need for the pen-related state and have elided those from the treatment herein. Instead, the *Pose* of the robot is represented as a simple structure:
```cpp
struct Pose {
  const meter_t x{0}, y{0};
  const degree_t th{0};

  // …
};
```
Here, the definition can be found in `./include/Pose.hpp`. A version without the `const` fields is in `./include/nonconst-Pose.hpp`. The `meter_t` and `degree_t` types are from Nic Holthaus' [units](https://github.com/nholthaus/units) library which allows compile-time checking and implicit conversion of units. No repeats of the [Mars Climate Orbiter](https://en.wikipedia.org/wiki/Mars_Climate_Orbiter) mishap, please.

Since we are not implementing pen state, the only transformations on a Pose based on the turtle interface are `move` and `turn` which will move or turn relative to an input Pose, producing a transformed Pose.

I think this is an excellent demonstration of modern functional programming because it demonstrates the ability of FP to maintain the purity of Papert's *body syntonic reasoning* while simultaneously handling peripheral concerns like logging, error handling, asynchronous computation and external events, which would otherwise frustrate such simple reasoning.


## Overview

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


### 1. oo-turtle

To start off from familiar ground, we begin with a straightforward Object-Oriented (OO) implementation of the turtle problem that any OO programmer would feel comfortable reading or writing. The state is stored privately in an object behind an interface which implements the turtle commands. Logging is handled through a ostream object which is injected through te turtles constructor. Errors are handled with exceptions.


### 2. pipes-turtle

When we exchange mutable state for functional style, we must explicitly pass the turtle state into the turtle commands. Since the turtle interface should take a previous state as input and return a new state as output, this passing of state takes the form of function composition. In this repository we explore C++ notations that can be used for such composition. In doing so, we temporarily ignore logging and error handling.


### 3. optional-monad-turtle

The optional monad offers composition over functions for handing optional values. An optional (AKA a *maybe* type) is represented in the type algebra as $() + T$ for some type $T$. (Not sure? Type theory is introduced [later](#theoretical-background-the-algebra-of-programs) in the README) In C++ it is implemented as the `std::optional` type constructor and represents a container for a value that may or may not be empty.

In this example, the output values of the turtle functions are optional to represent a computation that might fail. This is a partial replacement for exceptions. The structure of a monad is used to hide the complexity of unwrapping optional values to pass to the next function in the composition.


### 4. either-monad-turtle

While the optional-monad gives us purchase on computations that might fail, it doesn't offer a wealth of information about the nature of the failure. All we know is that at some point in the binding composition, there was a failure. The either-monad (AKA the error-monad) exchanges the empty type in the optional for an arbitrary error type. In this example, we create an `enum class` for named errors.

As with the optional monad, we make composition automatic through a monadic binding operation. The visitor pattern is used to handle the variant return type. (More on variant types in [this section](#sum-types-and-the-tagged-union))


### 5. writer-monad-turtle

In this example, we use the writer monad to pass a log around between turtle calls, returning the logging behaviour we relinquished after the oo-turtle example. The return values of the turtle functions is embellished with a string: `std::pair<std::string, Pose>` and the monad structure is used to hide the complexity as it was in the optional- and either-monad examples.

In general, the writer monad allows us to tacitly carry a monoid around with our return value. The monoid is fixed in the monad. For example, if we have a Writer which carries an integer, it can't be composed with a writer that carries a String: those are two different monads.


#### 5.1 writer-class-turtle

Instead of using `std::pair` for the Writer, this example offers a small variation where a struct template is used for the monad values. The struct has `value` and `log` fields. The idea is to advantage the client by not requiring them to remember if the log is the first or second item in the `std::pair`.


### 6. writer-either-monad-turtle

In general there is no straightforward technique for composing monads. Among the most thorough theoretical treatments comes from Jones and Duponcheel[^Jones1993] where they narrow the problem down to the impossibility of deriving a `join` operation automatically for arbitrary compositions of monads. 

In this example, I demonstrate the manual composition of the either- and writer- monads so that we can fully regain the functionality of the oo-turtle, in mathematically pure way.

[^Jones1993]: Jones, M. P., & Duponcheel, L. (1993). Composing monads. Technical Report YALEU/DCS/RR-1004, Department of Computer Science. Yale University.


### 7. command-turtle

In the case of virtualME, the state is stored in the actual physical position of the robot and it is not the job of any client of the turtle interface to keep track of it. A command might be regarded as a transformation on a Pose, but perhaps it is even more intuitive to model a command as the instruction itself.

In this example, two data structures are defined: `TurtleMove` and `TurtleTurn` containing the distance to move or the angle to turn respectively. A `TurtleCommand` is then variant type that is either one or the other. A function called `run` replaces both the `move` and `turn` functions: `run : (Pose, TurtleCommand) → Pose`, while a command `run_all` will execute a vector of turtle commands: `run_all : (Pose, [TurtleCommand]) → Pose`.

The client code still passes in the state: this is only a step toward exporting the responsibility of state management. But taking this step cost us logging and error handling, yet again. It will be restored in the next example.


### 8. command-writer-either-turtle

The next step toward exporting the responsibility of state management is regaining the logging and error handling. This is a matter of bringing back the writer- and either-monads. Those monads are now used within the executor code, and the client code need not deal with them. From the point of view of the client, they get back the final `Pose` and a string log OR an error code and a string log.


### 9. promise-monad-turtle

Yet to come.


### 10. actor-promise-turtle

Yet to come.


### 11. frp-turtle

Yet to come.


## Theoretical background: the algebra of programs

The spirit of algebra is the structure of composition and transformation. Superficially, we might look for structure on three levels:

  * Withing a given type. For example, can addition and scalar multiplication be defined on pairs of integers so as to make them a vector space?

  * Between types where operations are parameterised over types and produce new types. In C++ this is achieved through template metaprogramming.

  * Between procedures, which can be composed if the argument and return types align.

The distinction between these structures is naive, as they can all be unified in the theory of categories. However, when writing C++ code, these three areas of concern have palpably different qualities. Our focus will be the theoretical and practical unification of the latter two.

Types are viewed as sets where elements are the representable values in each type. For example, the set $\mathtt{bool}$ has a cardinality of two: $\left|\,\{\mathtt{true}, \mathtt{false}\}\,\right| = 2$, and $\left|\, \mathtt{int32}\,\right| = 2^{32}$, and so on. Operations on types produce new types. In order to formalise these operations into an algebraic structure, we will need a set of all types: $\mathbf{\mathtt{Type}}$. There are two operations on types, $+$ and $\times$, which form a commutative semiring over $\mathbf{\mathtt{Type}}$, which is the set of all distinct pairs that can be made elements of $\mathtt{bool}$ and $\mathtt{int}$.


### Product types and the Cartesian product

Types formed by application of the $(\times)$ operator called product types. As the title of the subsection suggests, the product operation is the cartesian product which builds tuples. This should be familiar to anyone with experience on the Cartesian plane $\mathbf{R}^2 = \mathbf{R}\times\mathbf{R}$, which is pairs of real numbers which can be represented by a plane of points. But more generally, and in terms of types, the cartesian product forms non-homogeneous compound types. For example $\mathtt{bool}\times\mathtt{int32} = \{(\mathtt{true}, a), (\mathtt{false}, a)\ \vert\  a\in\mathtt{int32}\}$, wich is the set of all distinct pairs which can be formed between values of boolean and 32-bit integer types.

In order to form a semiring over \mathtt{Type}, \mathtt{Type} must constitute a monoid with its product operation $(\mathbf{\mathtt{Type}}, \times)$. Demonstrating closure and associativity is straightforward. The more interesting property is the existence of a multiplicative identity so that
$$
  1\times A \cong A\times 1 \cong A
$$ 
where $\cong$ indicates isomorphism. In type theory, the $1$ element is usually notated as and empty pair of parentheses, $()$ and is called the *unit type*, and it is the singleton set—the set with only one element. In terms of a type, it is the type with only a single construction:
```cpp
struct Unit {};
```
A value of type `Unit` can be constructed, but since there is no internal structure, it is meaningless to ask what it's value is. So when this type appears in a product, it adds no information: $()\times A = \{(\bullet, a) \ \vert\ a\in A\}\cong A$.

In C++, the keyword `void` is a stand-in for the multiplicitive unit when describing the return value of a function. A function returning void returns nothing, which is equivalent to returning a unit. Furthermore, a function taking no arguments, `foo()`, is equivalent to a function taking a unit parameter. This, I believe, is the origin of the '$()$' notation. 

**Exercise:** What is the cardinality of $\mathtt{bool}\times\mathtt{int32}$? Note the integer operation you used to compute the cardinality based on the cardinalities of $\mathtt{bool}$ and $\mathtt{int}$.


### Sum types and the tagged union

Sum types, AKA variant types are less common than product types, but are incredibly useful as we we will come to see. A value in a variant type can be an element from any term in the sum. So for types $A$ and $B$, a value from $A+B$ can be a value from either type $A$ or type $B$. From the point of view of set theory, this is a union operation, with one additional detail. To be computationally useful, I must be able to ask if a value from $A+B$ is an element from $A$ or from $B$. This is why the operation is called a *tagged union*: values are tagged with information about their originating type.

For example, if I have a value $a : \mathtt{bool} + \mathtt{int}$, then $a$ may hold either a boolean value or an integer. But additionally, I must be able to query the type of the element in $a$.

Although I have not introduced categorical concepts yet, it is worth mentioning that the sum operation is the categorical dual of the product operation. As such, it is often called the *coproduct*.

In order to form a semiring over \mathtt{Type}, \mathtt{Type} must constitute a commutative monoid with its sum operation $(\mathbf{\mathtt{Type}}, \times)$. As with the $(\mathtt{Type},\times)$ monoid, it is straightforward to show closure and associativity, and we can say the same of commutivity in this case. Again, the interesting notion is the additive identity:
$$
  \emptyset + A = A + \emptyset = A.
$$
In type theory, the additive identity is often notated as $\mathtt{Void}$ (with an uppercase initial), not to be confused with `void` in C++. This $\mathtt{Void}$ is a type with *no constructor*. If your program requests the construction of a value from $\mathtt{Void}$, it is broken. In set theoretical terms, $\mathtt{Void}$ is the empty set, and with no elements, this is why in type theoretical terms it has no constructor.

Intuitively, if a variant can be either a value from $A$ or a value from $\mathtt{Void}$, then since $\mathtt{Void}$ has no values, the value *must* be from $A$, and so $A + \emptyset = A$.

Since the additive identity has no constructable value, it has no expression C++. It is a necessary and useful theoretical concept, but by its very nature no code can be written that relies on its construction.

The multiplicative unit has utility with the sum operation as well. For example, the bool type may be implemented as $\mathtt{bool} = () + ()$. In C++ code:
```cpp
struct True {};
struct False {};
using Bool = std::variant<True, False>;

Bool a = True();
```
The `std::variant` type constructor is new to C++17, and is the only standardized mechanism for constructing general sum-types. Notably it is implemented at the library level, and there is not yet language support for variant types, though it is being proposed[^p0095r0].

[^p0095r0]: D. Sankel. (2015) ISO Proposal P0095R0: The Case for a Language Based Variant <http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/p0095r0.html>

### A quick example of type algebraic construction

Consider the equation
$$
  L\langle T\rangle = () + T \times L\langle T\rangle.
$$
Here, $L$ is a *type constructor*. That is, its a mapping which issues a type based on its type arguments. (Confer that with data constructors, which take values and return new values, or with dependent types which take values and return a type.) So given a type $T$, $L\langle T\rangle$ represents another type.

The above equation is a recursive definition. Self-substitution leads to the series:
$$
  L\langle T\rangle = () + T + T^2 + T^3 + \cdots.
$$ 
The expression on the right contains both sums and products. It can be read as
> The unit type OR a single $T$ OR a pair of $T$s OR a triple of $T$s or …

which describes an arbitrary sized *list* of $T$s. Since the $+$ represents a tagged union, we must have a method to query the size, which is standard kit in most list interfaces. It is distinct from C-style arrays where the size is part of the type: `int[3]` is a list of three integers. The way C handles arbitrarily sized arrays is to provide a mechanism to equivocate arrays and pointers, so that a pointer to and integer, `int*` can point to the beginning of an array of `int`s. This way, pointers to arrays can be passed without function signatures having dependence on array sizes.


### Exponentiation, function types and currying.

We saw that types raised to an integer power represents repeated application of the Cartesian product: $\mathtt{int}^3 = \mathtt{int}\times\mathtt{int}\times\mathtt{int} = \{(x,y,z)\ |\ x,y,z\in\mathtt{int}\}$. Cetegory theory offers another exponentiation, $B^A$ for $A,B\in\mathtt{Type}$. Strange as it may seem, $B^A$ is the set of all functions from $A$ to $B$. That is, it is the set of all function mappings with signature $A\rightarrow B$. While this may seem like purely a notational move, it is backed by some rather deep insight into the generalisation of exponentiation.

Details aside (as beautiful as those details are), there is a particular result that will be used repeatedly in this repository. It is based on the identity
$$
  C^{A\times B} = (C^B)^A
$$
The expression on the left indicates a function mapping $A\times B\rightarrow C$, while on the right hand side we have $A\rightarrow B\rightarrow C$. The former is simply a function taking a pair of values, one from a $A$ and the other from $B$, and mapping them to $C$. The latter is a function that takes a value of type $A$ and returns a function that takes value from $B$ and returns a $C$. This identity brings to light a rather simple idea: any multivariate function can be transformed into a chain of functions which apply arguments one at a time. That transformation is called Currying after the great Haskell Curry.

This is where we must begin viewing functions as values from function types and treat them as any other values from a type. In particular, can be returned from other functions and stored in variables. For some this may be an unfamiliar concept, so let us explore it in a simple example:
```cpp
// add : int x int → int
int add(int a, int b) {
  return a + b;
}
// cadd : int → int → int
auto cadd = curry(add)
// add5 : int → int
auto add5 = cadd(5)

std::cout << add5(5) << ", " <<  add5(10); // prints "10, 15"
```
The `curry` function,
$$
  \mathtt{curry} : \left( Y^{A\times B\times C\times\cdots\times N}\rightarrow Z\right)   \rightarrow ((\cdots(Z^N)^\cdots)^B)^A,
$$
is implemented in my `tfunc` library which is a collection of some basics for functional programming in C++. If we did not want to use a general tool, we could have manually curried the `add` function in the above example using lambdas:
```cpp
auto cadd = [](int a){ return [a](int b){ return a + b; }; };
```
but that is a little hard to read. Alternatively, we could have done the partial application of the `5` manually:
```cpp
auto add5 = [](int b){ return 5 + b; };
```

[^FPCPP]: Ivan Čukić (2018) Functional Programming in C++. Manning Publications. ISBN 9781617293818 <https://www.manning.com/books/functional-programming-in-cplusplus>

[^Boost.Phoenix]: Boost.Phoenix: https://theboostcpplibraries.com/boost.phoenix

[^Udemy]: https://www.udemy.com/functional-programming-using-cpp/

## The Tutrtle problem

## Dependencies

All examples will require:

 * Cmake for building.
 * Phil Nash's unit testing library: [Catch2](https://github.com/philsquared/Catch)
 * Compile time dimensional units library: [units](https://github.com/nholthaus/units)

Individual examples may have additional dependencies, to be found in their respective READEMEs.


### Compiler and STL requirements

  * Currently I'm compiling with Clang++-6.0 trunk and libc++-6.0
  * `-std=c++17`
  * `std::variant` and support functions, including `std::variant_alternative_t` (which seems to be broken in GCC 7.0.1).
  * `std::optional` and friends.

## Building:
```sh
# from project root:
mkdir build && cd build
cmake .. && make
# To run all examples:
make test
```

### Groundwork: Common code for all cases


```cpp
struct Pose {
  const meter_t x{0}, y{0};
  const degree_t th{0};

  friend std::ostream &operator<<(std::ostream &os, const Pose &p) {
    os << '[' << p.x << ", " << p.y << ", " << p.th << ']';
    return os;
  }
};
```

*[OO]: Object-Oriented