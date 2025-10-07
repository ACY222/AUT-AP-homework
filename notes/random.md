## Random library

The C++ `<random>` library, introduced in C++11, is the modern and powerful
standard for generating high-quality pseudo-random numbers. It completely
replaces the old, flawed `std::rand()`

### Why use `<random>`

1. **High Quality Randomness**: The engines (like `std::mt19937`) are statically
    robust, unlike the poor quality of platform-dependent `rand`
2. **Eliminates Module Bias**: When using the traditional method ($rand() % N$),
   smaller numbers are slightly more likely to appear. The `<random>`
    distributions eliminate this bias
3. **Portability**: Using the same engine and the same seed guarantees the exact
   same sequence of numbers on any C++ compiler, which is crucial for testing
    and sumilation

### Key Classes and Functions

#### Random Number Engines

Engines are the objects that generate the fundamental stream of random bits.
They hold the internal state and are initialized with a *seed*
- `std::mt19937`: **Mersenne Twister Engine** with a 32-bit state size. This is
  the *most recommended and widely used* general-purpose PRNG
- std::mt19937_64: The engine with a 64-bit state size, useful when dealing with
  very large ranges
- `std::default_random_engine`: This engine is compiler-dependent, so its
    performance is not guaranteed, and usually it's no better than `std::mt19937`,
    so use `std::mt19937` instead

**Note**: Always initialize an engine once and reuse the same object to maintain
the random sequence. So we need to using `static` variable for functions, in
this way, the engine is initialized once per program lifetime, the engine state
persists across all function calls. `static std::mt19937 engine;` in a function.
Or using a member variable for classes, this encapsulates the random state
within the class instance. `private: std::mt19937 engine;` in a class

#### Random Num Distributions

Distributions are **function objects** that take the raw output from an engine
and transform it into a statiscally meaningful value within a specified range or
shape
- `std::uniform_int_distribution`: Generrates **integers** uniformly distributed
across a closed range $[a, b]$. `std::uniform_int_distribution dist(1, 100)`
- `std::uniform_real_distribution`: Generates **floating-point numbers**
    uniformly distributed across a half-open interval $[a, b]$.
    `std::uniform_real_distribution dist(1.0, 2.0)`
- `std::normal_distribution`: Generates floating-point numbers according to the
    **Gaussian distribution** defined by its mean($\mu$) and standard
    deviation($\sigma$). `std::normal_distribution dist(0, 1.0)`
- `std::bernoulli_distribution`: Generates a `bool` based on a probability $p$.
    Useful for coin flips. `std::bernoulli_distribution dist(0.75)`
- Check [cppreference](cppreference.com) for more distributions

#### Seeding Components

The method used to start the engine's sequence
- `std::random_device`: A non-deterministic (truly random) source of entropy,
typically used to generate a high-quality seed for the PRNG engine.
    ```cpp
    // for rd: operator(): advances the engine's state and returns the generated value
    std::random_device rd;
    std::mt19937 engine(rd());
    ```
- `std::seed_seq`: Used to generate a high-quality seed sequence from multiple
input values, effectively improving the initial state of the engine
    ```cpp
    std::seed_seq ss(1, 2, 3, 4);
    std::mt 19937 engine(ss);
    ```

### Common Usage Pattern

Here is the standard recommended way to generate random numbers in modern C++
```cpp
#include <iostream>
#include <random>
#include <ctime>

int main() {
    // 1. seed the engine
    std::mt19937 engine(static_cast<unsigned int>(std::time(0)));
    // 2. define the distribution
    std::uniform_int_distribution int_dist(1, 10);
    std::uniform_real_distribution real_dist(0.0, 10.0);
    // 3. generate numbers
    for (int i = 0; i < 10; ++i) {
        std::cout << "Random Integer in [1, 10]: " << int_dist(engine) << std::endl;
        std::cout << "Random Double in [0, 10): " << real_dist(engine) << std::endl;
    }

}

```
