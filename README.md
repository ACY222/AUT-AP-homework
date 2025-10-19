This repository contains the assignments for `Advanced Programming Course`
provided by Amirkabir University of Technology

And my thoughts about there assignments are as follows:

### homework 1

- In this homework, we will implement a **Linear Algebra** library, mainly about
  matrix operations, in c++
- Actually, I don't like this assignment.
- The main problem is, the description about the functions are too vague for
me. For example, what should I do if you call `mutiply(matrix1, matrix2)` and
`matrix1.size() == 0`? Throw an error? Or `return {};`? Actually, the answer is
`return matrix2;`. However, in another funciton, what you need to do might be
completely different. Honestly, this is not obvious for me. So I must check the
`unit_test.cpp` to realize what should I do.
- So, you may want to skip this homework

### homework 2

- In this homework, we will implement a simple program to simulate what is
happening in **cryptocurrencies**
- This homework is unbelievably nice. I learnt many things from it:
    - How to use `<random>` library to generate random numbers
    - How to use `<regex>` library. I also review the semantics about regex
    - The modifiers, such as `static, const` and so on
    - How to organize a "big" project
Therefore, I tried it again after finishing it.
- After all, this homework really impresses me, highly recommanded

### homework 3

- In this homework, we will implement a *binary search tree*
- Same thing with homework, the description is vague, some are even wrong!
And some function designs are odd to me. For example:
    ```cpp
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    ```
    You cannot imagine that, the successor of current node could be the
    node before current node in inorder traversal. And I don't know how to cope
    with the edge cases unless I test the program and check `unit_test.cpp`

### homework 4

- In this homework, we will implement our own `shared_ptr` and `unique_ptr`
- The quality of this homework is roughly equal to homework2, you can learn
deeply into the thoughts and realization of smart pointer, which is the new
feature in C++11
- But after finishing the first four assignments. I found a new problem: The
`unit_test` is neither complete enough, nor strong enought: the test cases are
too simple and the number of test cases is low. Therefore, even if there are
many vulnerabilities or bugs in your code, you may still pass all the tests.
But I have not figured out a good way to fix this.
- After all, this homework is nice, highly recommended

### homework 5

- In this homework, we will make different kinds of espresso-based coffees using
their ingredients to tackle `inheritance` and `polymorphism` in C++.
- The quality of this homework is very high. For me, the two concepts are both
new and unfamiliar. And I also learnt about `virtual` and some related keyword
from it
- Highly recommended
