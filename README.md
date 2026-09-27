# Custom Templated Vector (`MoveVector<T>`)

## Overview
This repository contains a highly optimized, dynamically resizing array designed 
to mimic the core functionality of `std::vector`. The primary goal is manual memory management,
strict adherence to C++11 move semantics, and robust exception safety.

For an in-depth breakdown of the architecture and validation strategy, please reference `DESIGN_NOTES_2.txt` and `TEST_PLAN.txt`.

## Architectural Highlights
*   **Decoupled Allocation:** Utilizes `std::allocator` and `std::allocator_traits`
*   to acquire uninitialized memory space without forcing default construction on every
*   element. Objects are constructed in-place only when explicitly requested and destroyed individually upon removal.
*   **Perfect Forwarding:** Implements `emplace_back` using variadic templates
*    (`Args&&`) and `std::forward` to construct objects directly in the vector's memory space, eliminating temporary copy overhead.
*   **Exception Safety & Relocation:** Evaluates element types at compile time using `move_if_noexcept`.
*   If an exception is thrown during reallocation, the strong exception guarantee ensures the partially
*   built memory block is destroyed and the original vector state remains untouched.

## Testing Framework
The validation suite evaluates memory safety, exception handling, and standard library compliance across 28 distinct test cases.
*   **Custom Macro Evaluation:** Testing logic is abstracted into a custom `RUN_TEST` preprocessor macro, providing a
*   scalable, isolated way to evaluate boolean conditions at compile time without passing local variables by reference.
*   **Memory Leak Verification:** Injects custom struct trackers (e.g., `FailsOnCopyType`, `MemoryLeakTracker`)
*   into a 5-phase testing sequence to definitively prove zero memory leaks upon destruction.
