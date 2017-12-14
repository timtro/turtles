# `pipes turtle`

In the OO turtle, the state was held privately in a mutable object which implemented the turtle interface as well as some getters for the internal data. In pure functional programming mutation is forbidden. In these examples, it will be avoided where possible, and heavily restricted otherwise.

Starting with the oo-turtle example in mind, the first step toward immutable state is making the fields of the state type immutable. I briefly mentioned in the README section [The Turtle Problem.](../README.md#the-turtle-problem) that the state or *pose* of the turtle can be easily represented as:
```cpp
struct Pose {
  const meter_t x{0}, y{0};
  const degree_t th{0};
}
```
which is the definition in `../include/Pose.hpp`. If the fields of the structure are immutable (`const`), then there is no reason that the data should be private, so the `struct` keyword is used.

Note also that the name `OOTurtle` makes no reference to the `pose`, since the internal representation of the data is completely abstracted away. (Except the getter methods: some consider the need for getter methods as a symptom of a bad design. I find their arguments compelling.) When we separate behaviour from data, types can be given names which reveal their meanings, and not their interfaces.

Another result of separating the data from the behaviour is that the implementations of `move` and `turn` are exported to free functions. For now, we won't worry about logging or exceptions. We introduce those gradually in later examples.

The implications of immutable data and free-function interfaces to the usage of these structures are severe. Each section of this README describes an idiom for working with these basic functional interfaces.


#### The crude function interface

Without deliberation, a first attempt to use the free move and turn functions with immutable data strucutres may look something like this:
```cpp
const auto s1 = move(10_m, initial);
const auto s2 = turn(120_deg, s1);
const auto s3 = move(10_m, s2);
const auto s4 = turn(120_deg, s3);
const auto s5 = move(10_m, s4);
const auto final = turn(120_deg, s5);
```
While it is straightforward to work out what's happening here, there is a lot of syntactical noise that obscures the simplicity of what is taking place. There is also a noticeable lack of parsimony with namespace real estate.

Pros:
  * Straightforward to anyone putting in the effort to see through the syntax.
Cons:
  * Very verbose.
  * Needless creation of named values.
  * Hard to read through all of the noise.


#### The crude function interface with point-full composition

If the major complaint of the crude function interface is merely the named variables: eliminate them. We can explicitly nest function calls into arguments of the functions to come after:
```cpp
const auto final = turn(120_deg,
                    move(10_m,
                    turn(120_deg,
                    move(10_m,
                    turn(120_deg,
                    move(10_m,
                    initial  ))))));
```
Aside from the garish use of parenthesis, which gets worse with longer compositions, for someone speaking languages which are read from top to bottom, it is counterintuitive to read the comppsition from bottom to top.

Pros:
  * Easier to read without named intermediate values

Cons:
  * U-G-L-Y you ain't go not alibi
  * Read right-to left (bottom-up), which feels wrong.


#### Dot-style piping

In the OO turtle, issuing commands was a matter of calling methods on the object holding the pose. The original goal was to eliminate mutable state. That doesn't preclude the use of member functions if they return a new object rather than a mutated on.

In `turtle.hpp`, 


Now, with no mutable state, we have to concern ourselves with propagating the state from one turtle command to the next. Because the turtle methods in our Pose class return new Pose objects, we can simply use the function call operator (`.`) as a means of tacitly passing the state to the next turtle command:

```cpp
    const auto final = static_cast<const TPose &>(initial)
                           .move(10_m)
                           .turn(120_deg)
                           .move(10_m)
                           .turn(120_deg)
                           .move(10_m)
                           .turn(120_deg);
```
Here, `initial.move(10_m)` returns a new `Pose` object, allowing us in turn to call `.turn(120_deg)`. The new Pose created by `initial.move(10_m)` is implicitly passed as a pointer to the `turn` method call and this cycle can be extended indefinitely.

Pros:
  * Looks even simpler than than the OO version if you ignore the cast. (And the cast may not be necessary if you don't plan to mix TPose and Pose in the same code.)
  * Immutable data.
  * Pure functions.

Cons:
  * Casting the TPose interface onto Pose is a bit ugly.


#### Approximately point-free style
```cpp
const auto triangle = tf::compose(
                        cmove(10_m),
                        cturn(120_deg),
                        cmove(10_m),
                        cturn(120_deg),
                        cmove(10_m),
                        cturn(120_deg));

const auto final = triangle(initial);
```

#### Curried functions and the pipe function template
```cpp
const auto final = tf::pipe(initial,
                          cmove(10_m),
                          cturn(120_deg),
                          cmove(10_m),
                          cturn(120_deg),
                          cmove(10_m),
                          cturn(120_deg));
```

[^Martin2002]: Martin, Robert (2002). Agile Software Development: Principles, Patterns and Practices. Pearson Education.

[^Meyer1988]: Meyer, Bertrand (1988). Object-Oriented Software Construction. Prentice Hall. ISBN 0-13-629049-3.