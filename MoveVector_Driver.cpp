/*
Author: Viacheslav Shapoval
Title: Templated Vector
Description: implementation of a templated dynamic-array class
             named MoveVector<T>. The class will provide functionality
             similar to a limited version of std::vector.
Date Created: 9/12/2026
Date Last Modified: 9/14/2026
*/
#include <iostream>
#include <string>
#include <memory>
#include <stdexcept>
#include "MoveVector.h"

using namespace std;

// description: A type that refuses to be built without a starting value.
//              Proves vector doesn't construct garbage objects in empty space.
struct NeedsValueToBuild {
    NeedsValueToBuild() = delete;
    explicit NeedsValueToBuild(int) {}
};

// description: A type that tracks exactly how many copies of itself
//              currently exist. Used to prove every created object is
//              perfectly destroyed (no memory leaks).
struct MemoryLeakTracker {
    static int active_objects;
    MemoryLeakTracker() { ++active_objects; }
    MemoryLeakTracker(const MemoryLeakTracker&) { ++active_objects; }
    MemoryLeakTracker(MemoryLeakTracker&&) noexcept { ++active_objects; }
    ~MemoryLeakTracker() { --active_objects; }
    MemoryLeakTracker& operator=(const MemoryLeakTracker&) = default;
    MemoryLeakTracker& operator=(MemoryLeakTracker&&) = default;
};
int MemoryLeakTracker::active_objects = 0;

// description: A type with an unsafe move constructor that might throw errors.
//              Proves vector uses move_if_noexcept to safely copy this
//              instead.
struct UnsafeMoveType {
    static int copy_count;
    UnsafeMoveType() = default;
    UnsafeMoveType(const UnsafeMoveType&) { ++copy_count; }
    UnsafeMoveType(UnsafeMoveType&&) { ++copy_count; } // Missing 'noexcept'
};
int UnsafeMoveType::copy_count = 0;

// description: A type with a guaranteed safe move constructor.
//              Proves vector aggressively moves this rather than copying it.
struct SafeMoveType {
    static int move_count;
    SafeMoveType() = default;
    SafeMoveType(const SafeMoveType&) {}
    SafeMoveType(SafeMoveType&&) noexcept { ++move_count; } // Safe 'noexcept'
};
int SafeMoveType::move_count = 0;

// description: Made to intentionally crash when copied.
//              Proves the original vector survives if a reallocation fails.
struct FailsOnCopyType {
    FailsOnCopyType() = default;
    FailsOnCopyType(const FailsOnCopyType&) {
        throw std::runtime_error("Intentionally failed copy");
    }
};

// description: Macro to format and track test results directly
// to console.
#define RUN_TEST(num, name, cond) \
if (cond) { \
    cout << "PASS: " << num << ". " << name << "\n"; \
    ++passed; \
} else { \
    cout << "FAIL: " << num << ". " << name << "\n"; \
} \
++total;

int main() {
    int passed = 0;
    int total = 0;

    // Inner scope ensures all vector destructors run before final memory
    // leak check
    {
        MoveVector<int> def_vec;
        RUN_TEST(1, "default construction", def_vec.empty() &&
            def_vec.capacity() == 0);

        MoveVector<int> size_vec(3);
        RUN_TEST(2, "size constructor", size_vec.size() == 3 &&
            size_vec.capacity() == 3);

        MoveVector<string> str_vec(2, "x");
        RUN_TEST(3, "fill constructor with string", str_vec.size() == 2 &&
            str_vec[0] == "x");

        str_vec[0] = "y";
        RUN_TEST(4, "operator[] and at access", str_vec.at(0) == "y");

        bool bounds_caught = false;
        try {
            def_vec.at(0); // Attempt to access out of bounds
        } catch (const std::out_of_range&) {
            bounds_caught = true;
        }
        RUN_TEST(5, "at bounds checking", bounds_caught);

        RUN_TEST(6, "front back and data", str_vec.front() == "y" &&
            str_vec.back() == "x" && str_vec.data() != nullptr);

        // Utilizes pointer iterators for traversal
        int loop_count = 0;
        for (auto it = str_vec.begin(); it != str_vec.end(); ++it) {
            ++loop_count;
        }
        RUN_TEST(7, "pointer iterator traversal", loop_count == 2);

        string temp_str = "z";
        str_vec.push_back(temp_str);
        RUN_TEST(8, "push_back lvalue copy", str_vec.back() == "z" &&
            str_vec.size() == 3);

        str_vec.push_back("w");
        RUN_TEST(9, "push_back rvalue move", str_vec.back() == "w" &&
            str_vec.size() == 4);

        str_vec.emplace_back(3, 'a');
        RUN_TEST(10, "emplace_back perfect forwarding", str_vec.back()
            == "aaa" && str_vec.size() == 5);

        MoveVector<int> growth_vec;
        growth_vec.push_back(1);
        growth_vec.push_back(2);
        growth_vec.push_back(3);
        RUN_TEST(11, "required capacity growth rule", growth_vec.capacity()
            == 4); // Should double to 4

        growth_vec.reserve(10);
        bool reserved_up = (growth_vec.capacity() == 10);
        growth_vec.reserve(2);
        RUN_TEST(12, "reserve and no-shrink reserve", reserved_up &&
            growth_vec.capacity() == 10);

        growth_vec.shrink_to_fit();
        RUN_TEST(13, "shrink_to_fit", growth_vec.capacity() == 3 &&
            growth_vec.size() == 3);

        growth_vec.resize(4);
        RUN_TEST(14, "resize with default construction", growth_vec.size()
            == 4 && growth_vec.back() == 0);

        growth_vec.resize(5, 9);
        RUN_TEST(15, "resize with fill value", growth_vec.size() == 5 &&
            growth_vec.back() == 9);

        growth_vec.resize(2); // Demolishes excess objects
        RUN_TEST(16, "resize shrink", growth_vec.size() == 2 &&
            growth_vec.capacity() >= 2);

        growth_vec.pop_back();
        growth_vec.clear();
        RUN_TEST(17, "pop_back and clear", growth_vec.empty() &&
            growth_vec.capacity() > 0);

        MoveVector<int> copy_vec(size_vec);
        copy_vec[0] = 99;
        RUN_TEST(18, "copy constructor deep copy", size_vec[0] == 0 &&
            copy_vec[0] == 99);

        growth_vec = copy_vec;
        MoveVector<int>* copy_ptr = &growth_vec;
        growth_vec = *copy_ptr; // Self-assignment check that bypasses
                                // compiler warnings
        RUN_TEST(19, "copy assignment and self-assignment", growth_vec.size()
            == copy_vec.size() && growth_vec[0] == 99);

        MoveVector<int> move_vec(std::move(copy_vec));
        RUN_TEST(20, "move constructor ownership transfer", copy_vec.data()
            == nullptr && move_vec.size() == 3);

        growth_vec = std::move(move_vec);
        MoveVector<int>* move_ptr = &growth_vec;
        growth_vec = std::move(*move_ptr); // Self-move check that bypasses
                                           // compiler warnings
        RUN_TEST(21, "move assignment and self-move", move_vec.data() ==
            nullptr && growth_vec.size() == 3);

        MoveVector<int> swap_vec;
        swap_vec.swap(growth_vec);
        RUN_TEST(22, "constant-time swap", swap_vec.size() == 3 &&
            growth_vec.empty());

        MoveVector<std::unique_ptr<int>> unique_vec;
        unique_vec.push_back(std::unique_ptr<int>(new int(5)));
        RUN_TEST(23, "move-only unique_ptr elements", unique_vec.size() == 1 &&
            *unique_vec[0] == 5);

        MoveVector<NeedsValueToBuild> no_def_vec;
        no_def_vec.emplace_back(42);
        RUN_TEST(24, "non-default-constructible elements", no_def_vec.size()
            == 1);

        MoveVector<UnsafeMoveType> unsafe_vec(2);
        UnsafeMoveType::copy_count = 0;
        unsafe_vec.reserve(10);
        RUN_TEST(25, "move_if_noexcept copy preference",
            UnsafeMoveType::copy_count > 0);

        MoveVector<SafeMoveType> safe_vec(2);
        SafeMoveType::move_count = 0;
        safe_vec.reserve(10);
        RUN_TEST(26, "noexcept move relocation preference",
            SafeMoveType::move_count > 0);

        MoveVector<FailsOnCopyType> crash_vec(2);
        bool strong_exception = false;
        try {
            // Attempt to reserve, expects a crash
            crash_vec.reserve(10);
        } catch (...) {
            strong_exception = (crash_vec.size() == 2 && crash_vec.capacity()
                == 2);
        }
        RUN_TEST(27, "reserve exception cleanup and strong guarantee",
            strong_exception);

        MoveVector<MemoryLeakTracker> tracker_vec(5);
        tracker_vec.push_back(MemoryLeakTracker());
        tracker_vec.clear();
    } // All objects fall out of scope and are destroyed here

    RUN_TEST(28, "balanced object lifetime management",
        MemoryLeakTracker::active_objects == 0);

    cout << "\nTests passed: " << passed << " / " << total << "\n";
    return 0;
}