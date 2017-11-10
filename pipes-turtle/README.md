# `pipes turtle`

Overall cons:
  * No logging.
  * No error handling.

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


#### The dot-style piping
```cpp
const auto final = move(10_m, initial)
                        .turn(120_deg)
                        .move(10_m)
                        .turn(120_deg)
                        .move(10_m)
                        .turn(120_deg);
```
Cons:
  * Requires turtle commands to be part of the `Pose` data type.


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