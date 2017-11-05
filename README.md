# `Functional Ascent of Turtles`
---

A series of software design kata inspired heavilty by Scott Wlaschin's talk *[Thirteen Ways of looking at a Turtle
](https://fsharpforfunandprofit.com/turtle/)*. 

 * Consider composition with list monad (or applicative functor), which would allow easy modelling of several turtles simultaneously.

## Dependencies

 * Phil Nash's unit testing library: [Catch](https://github.com/philsquared/Catch)
 * Compile time dimensional units library: [units](https://github.com/nholthaus/units)


## Description:

OO handles state, errors and logging. We don't want to handle state in an object so we use functions. Pipes example shows how we can use composition on functions to handle state, but it doesn't do logging or error handling. The Writer monad helps us take care of logging along with the state, but doesn't do error handling. The optional-monad allows us to handle errors, but the OO monad let us have more specific errors. The either monad allows us to pull from a set of errors in an error type. But neither optional nor either handles logging. we have to combine monads for that.

### `Object-Oriented turtle`

Found in directory `turtles/oo-turtle`.

### `pipes turtle`

Found in directory `turtles/pipes-turtle`.


Overall cons:
  * No logging.
  * No error handling.

#### The crude function interface
```cpp
const auto s1 = move(10, initial);
const auto s2 = turn(degree_t{120}, s1);
const auto s3 = move(10, s2);
const auto s4 = turn(degree_t{120}, s3);
const auto s5 = move(10, s4);
const auto final = turn(degree_t{120}, s5);
```

Pros:
  * I'll let you know when I think of any.

Cons:
  * Very verbose.
  * Needless creation of named values.
  * Hard to read through all of the noise.

#### The crude function interface with nesting

```cpp
const auto final = turn(degree_t{120},
                    move(10,
                    turn(degree_t{120},
                    move(10,
                    turn(degree_t{120},
                    move(10,
                    initial  ))))));
```
Pros:
  * Easier to read without named intermediate values

Cons:
  * U-G-L-Y you ain't go not alibi
  * Read right-to left (bottom-up), which feels wrong.


#### The dot-style piping
```cpp
const auto final = move(10, initial)
                        .turn(degree_t{120})
                        .move(10)
                        .turn(degree_t{120})
                        .move(10)
                        .turn(degree_t{120});
```
Cons:
  * Requires turtle commands to be part of the `Pose` data type.


#### Approximately point-free style
```cpp
const auto triangle = tf::compose(
                        cmove(10),
                        cturn(degree_t{120}),
                        cmove(10),
                        cturn(degree_t{120}),
                        cmove(10),
                        cturn(degree_t{120}));

const auto final = triangle(initial);
```

#### Curried functions and the pipe function template
```cpp
const auto final = tf::pipe(initial,
                          cmove(10),
                          cturn(degree_t{120}),
                          cmove(10),
                          cturn(degree_t{120}),
                          cmove(10),
                          cturn(degree_t{120}));
```