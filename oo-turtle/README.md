# `Object-Oriented turtle`

This first iteration of the turtle is programmed in a strightforward object-oriented style. The state is held in the private fields of the `OOTurtle` object defined in `OOTrutle.hpp`:
```cpp
class OOTurtle {
  Pose m_pose{meter_t{0}, meter_t{0}, 0_deg};
  std::ostringstream &m_oss;
  …
```
The state of the object is mutated through the public `move` and `turn` methods. The `move` method takes a signle parameter of `meter_t` type while the `turn` method takes a single parameter of `degree_t` type:
```cpp
public:
  OOTurtle() = default;
  OOTurtle(std::ostringstream &);
  void move(meter_t);
  void turn(degree_t);
```
and of course, we require getters for the state which return copies of the data:
```cpp
  decltype(Pose::x) get_x() const { return this->m_pose.x; }
  decltype(Pose::y) get_y() const { return this->m_pose.y; }
  decltype(Pose::th) get_th() const { return this->m_pose.th; }
};
```
In the same header, there are also two exceptions defined: `MovingError` and `TurningError`. The `move` and `turn` methods are implemented in `OOTurtle.cpp`.

The constructor for `OOTurtle` takes a reference to an `ostringstream` which it will use for logging.

In `oo-turtle.cpp`, some unit tests demonstrate usage. In the first case, exception are uncaught and the methods are called to mutate the OOTurtle instance through a path:
```cpp
  turtle.move(10_m);
  turtle.turn(120_deg);
  turtle.move(10_m);
  …
```
If any of those methods were to throw, the program would terminate.

The next test is identical except that motion commands are placed in try/catch blocks for exception handling:
```cpp
  try {
    turtle.move(10_m);
  } catch (MovingError) {
    std::cout << "Moving error\n";
    // + More complex logic with more try/catch?
  }
  try {
    turtle.turn(120_deg);
  } catch (TurningError) {
    std::cout << "Moving error\n";
    // + More complex logic with more try/catch?
  }
```

## Advantages
  * Familiar
  * Easy to implement
  * Easy to understand

## Disadvantages
  * Stateful code is harder to reason about
  * Stateful code is harder to test
  * No abstraction from the interface means the user is enjoined to use a particular implementation.