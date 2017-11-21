# `pipes turtle`

In the OO turtle, the state was held privately in a mutable object which implemented the turtle interface as well as some getters for the internal data. In functional programming, mutation is to be restricted, or avoided altogether.

If we begin by making the fields of the `Pose` class immutable, then there is no reason that the data should be held private. So, we instead use a struct, and mark the fields const:
```cpp
struct Pose {
  const meter_t x{0}, y{0};
  const degree_t th{0};
}
```

Above, the implementation of `move` and `turn` are exported to free functions. The reason for this will be apparent in the next example.

For now, we won't worry about logging or exceptions. We introduce those gradually in later examples.

In the OO turtle, issuing commands was a matter of calling methods on the object holding the pose. Now, with no mutable state, we have to concern ourselves with propagating the state from one turtle command to the next. Because the turtle methods in our Pose class return new Pose objects, we can simply use the function call operator (`.`) as a means of tacitly passing the state to the next turtle command:

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

#### The crude function interface
```cpp
const auto s1 = move(10_m, initial);
const auto s2 = turn(120_deg, s1);
const auto s3 = move(10_m, s2);
const auto s4 = turn(120_deg, s3);
const auto s5 = move(10_m, s4);
const auto final = turn(120_deg, s5);
```

Pros:
  * I'll let you know when I think of any.

Cons:
  * Very verbose.
  * Needless creation of named values.
  * Hard to read through all of the noise.

#### The crude function interface with nesting

```cpp
const auto final = turn(120_deg,
                    move(10_m,
                    turn(120_deg,
                    move(10_m,
                    turn(120_deg,
                    move(10_m,
                    initial  ))))));
```
Pros:
  * Easier to read without named intermediate values

Cons:
  * U-G-L-Y you ain't go not alibi
  * Read right-to left (bottom-up), which feels wrong.


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