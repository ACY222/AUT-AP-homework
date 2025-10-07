## `static`

### on a Member Function

When a member function is modified by `static`, it becomes a **Static Member
Function**. Its features are as following:
- **Independence**: It is not associated with any specific object instance of
    the class. It belongs to the class itself
- **Access**: A static function can only access **static member variables** and
    call **static member functions** of the class
- **`this` Pointer**: A static member function does not have a `this` pointer.
    Consequently, it cannot access any non-static (instance-specific) member
    data or call non-static methods
- **Invocation**: It is typically called using the **class name** and the scope
  resolution operator, e.g., `ClassName::static_function()`
- **Use case**: Used for utility functions or counters that manage class-wide
    data, independent of any object's state

This is an example:
```cpp
class Counter {
private:
    static int count;   // shared data
public:
    static void increment() {
        ++count;    // Correct: Accessing a static member
    }

    // callable even if no objects exist
    static int get_count() {
        return count;
    }
}
// invocation example:
// Counter::get_count();    // works without creating a counter
```

### on a Non-Member Function

Non-member function: ordinary functions (global functions or free functions)
that are not members of a class


When `static` is used to modify a function defined at the **file scope**
(outside of any class or function), its role is to control the function's
**linkage and visibility**, which is as following:
- **Linkage**: The `static` keyword changes the function's linkage from the
    default **External Linkage** to **Internal Linkage**
- **Visibility**: A `static` function can only be accessed and called from
    within the **current tranlation unit** (the specific `.cpp` source file)
    where it is defined. It is invisible to other source files in your project
- **Purpose**: This is a mechanism to create **file-local** or private helper
    functions. It prevents the function name from colliding with the identical
    names used in other parts of the project, promoting better encapsulation at
    the file level.
- In a word, *a static non-member function can only be called in that one file*

## `const`

### on a Member Function

When a member function is modified by `const` (placed after the parameter list
and before the function body), it becomes a **Const Member Function**. Its
features are as following:
- **Data Protection**: It is a promise by the function that it **will not
    modify** any of the object's non-static member variables (as we know that,
    the static member variables are shared by all instances)
- **`this` Pointer**: Inside a const function, the `this` pointer is implicitly
    treated as `const ClassName*`. This prevents any modification of instance data
- **Calling Authority**: A **const object** can only call const member
    functions. A non-const object can call both const and non-const functions
- **Use Case**: Essential for implementing **Getter** and **Query** methods,
    ensuring they maintain the object's integrity

This is an example:
```cpp
class Point {
private:
    int x_;
public:
    Point(int x) : x_(x) {}

    // Const Member Funciton: Guarantees no state change
    int get_x() const {
        // x_ = 10  // Error! Compiler prevents modification
        return x_;
    }

    void set_x(int x) {
        x_ = x;     // Correct: Modifies member variable in non-const function
    }
}

    // Invocation example:
    const Point cp(1);
    cp.get_x();     // it works
    cp.set_x(5);    // Error: Cannot call non-const function on a const object
```

### on a Non-Member Function

For non-member functions, the `const` keyword cannot be used to modify the
function itself (it cannot be placed after the parameter list). Instead, `const`
is used to qualify the function's parameters or return value

- Modifying Function Parameters
    This is the most common and useful application of `const` in non-member
    functions. Using `const` on parameters passed **by reference** or **by
    pointer** (e.g., `void func(const std::string& s)`) is crucial. It
    guarantees to the caller that the function will not modify the original data
    passed in
- Modifying the Return Value
    - Using `const` on the return typr (e.g., `const int& func()`) ensures that
    the result received by the caller **cannot be used to modify** the value
    being returned (if it's a reference or pointer)
    - e.g.,
    ```cpp
    int global_statue = 5;
    const int& get_status() {
        return global_statue;
    }
    void test_return() {
    const int& ref = get_status();
    // ref = 10;    // Error: Cannot modify the value through a const reference
    }
    ```

## `extern`

The `extern` keyword is all about **linkage** and **declarations**.
- **Declaration, Not Definition**: `extern` creates a **declaration**, not a
    **definition**. It tells the compiler that a variable (or function) is **define
    elsewhere**, typically in a different source file (as we know, the global
    variables should be defined in the source file, rather than the header file)
- **External Linkage**: It enforces **external linkage**, meaning the entity's
    name can be seen and used globally across all course files of the program
- **Default Behavior**: **Functions** and **non-`const` global variables** have
    external linkage by default, so using `extern` on them is usually redundant
    for definition, but it's required when you declare them in a seperate header
    file
- **Common Usage**: Used in a **header file** to declare a global variable that
  is **defined** exactly once in a `.cpp` file

## `inline`

The `inline` keyword is a hint to the compiler, primarily used to request that a
function call be replaced directly with the function's body. It's mainly about
optimizing performance by reducing the overhead of a function call
