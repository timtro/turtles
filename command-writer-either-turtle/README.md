# `command-writer-either-turtle`

This turtle is designed to relieve the client from the responsibility of state management, while retaining the logging and error handing behaviour in the `writer-either-monad-turtle` example.

`const Pose initial{0_m, 0_m, 0_deg};` In the case of a real robot, the user wouldn't need to deal with this at all, and the middleware would sit between the client and the robot+.