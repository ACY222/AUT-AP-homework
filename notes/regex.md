## Regular expressions library

The regular expressions library provides a class that represents regular
expressions. Almost all operations with regexes can be characterized by
operating on several of the following objects:
    - `Target sequence`: The character sequence that is searched for a pattern.
    This may be a range specified by two iterators, a null-terminated character
    string or a `std::string`.
    - `Pattern`: This is the regular expression itself. It determines what
    constitutes a match. It is an object of type `std::basic_regex`, constructed
    from a string with special grammer.
    - `Matched array`: The information about the matches may be retrieved as an
    object  of type `std::match_results`
    - `Replacement string`: This is a string that determines how to replace the
    matches

### Main clsses

- `std::regex`: The **Pattern Object**. This object stores and compiles the
regular expression pattern. It must be created before any matching operation
- `std::match_results`: The **Result Container**. This is a container
(`std::smatch = std::match_results<std::string::const_iterator>`, which is
most commonly used) used to store the results of a match, including
information about all **captured groups**
    - Element access:
        - `[n]`: Return the $n_{th}$ match elements as a `std::sub_match`.
            The `[0]` is the entire matched string, and `[1]` onwards are captured
            strings, `sm[k].str()` will transfer the element into `std::string`
        - `.str(n)`: Return the $n_{th}$ match elements as a `std::string`
        - `.position(n)`: Return the **starting index** of the $n_{th}$
            match elements within the original string
        - `.length(n)`: Return the length/size of the $n_{th}$ match elements
    - Status and Container Interfaces
        - `.size()`: Return the total number of matched sub-expressions (i.e.,
            the entire match + all captured groups)
        - `.empty()`: Checks if the match object contains any results, returns
            *true* if no match was found
        - `.prefix()`: Returns the `std::sub_match` for the substring before the
            match (only meaningful with `std::regex_search`)
        - `.suffix()`: Returns the `std::sub_match` for the substring after the
            match (only meaningful with `std::regex_search`)
- `std::regex_iterator`: **Iterator**. Used to find and iterate over all
non-overlapping matches in a sequence
- `std::regex_token_iterator`: **Token iterator**. Used to split a string into
tokens based on a regex pattern (similar to `split` functions)

### Core functions

- `std::regex_match`: **Full Match**. Checks if the entire input sequence
*perfectly matches* the regex pattern from start to end
- `std::regex_search`: **Search Match**. Checks if the input sequence *contains
a subsequence* that matches the regex pattern
- `std::regex_replace`: **Replace**. Finds *all subsequences* in the input and
*replaces* them with a specified format string

### Example

```cpp
// check if the input string is formatted as "name-name-number(double)"
std::string pattern = "(\\w+)-(\\w+)-(\\d+\\.\\d+)";
std::regex r(pattern);
std::smatch result;

if (std::regex_match(input_str, result, r)) {   // if perfectly matches
    std::string name1 = result.str(1);  // = result[1] / result[1].str()
    std::string name2 = result.str(2);  // they are slightly different
    double number = std::stod(result.str(3));
}
```
