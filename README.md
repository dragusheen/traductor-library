# Traductor 💬🌎

Traductor is a C++ library designed to facilitate language translation within your applications. It provides a simple interface for loading translations from files and accessing them throughout your codebase. With support for lazy loading and efficient parsing, Traductor aims to streamline the process of internationalization in your projects.

<br>
<br>

## Summary 📝

- [Installation](#-installation): Find instructions on how to install and build the library.
- [Usage](#-usage): Explore examples and code snippets to get started with Traductor.
- [Documentation](#-documentation): Dive into detailed documentation of the Traductor class and its methods.
- [Contributing](#-contributing): Contribute to the development of Traductor by submitting enhancements or bug fixes.
- [License](#-license): Understand the terms of use and licensing for the Traductor Library.
- [Authors](#-authors): Meet the creators behind Traductor.

<br>
<br>

## 🛠️ Installation

To use Traductor in your project, simply include the `Traductor.hpp` header file and link against the `libTraductor.a` static library.

<br>
<br>

### 📋 Prerequisites

- C++17 compiler

<br>

### 🏗️ Building from source

1. Clone the repository:

    ```bash
    git clone https://github.com/dragusheen/traductor-library
    ```

<br>

2. Build the library using the provided Makefile:

    ```bash
    cd Traductor
    ```
    ```bash
    make
    ```

<br>

This will create a static library named `libtraductor.a`.

<br>

## 🚀 Usage

Include the Traductor header in your project and link against the `libtraductor.a` library.

### Example

Here's a simple example demonstrating how to use Traductor:

```cpp
#include "Traductor.hpp"
#include <iostream>

int main() {
    Traductor::get()->init();
    Traductor::get()->setLang("en_US");

    std::string translated = Traductor::get()->translate("hello.world");
    std::cout << "Translated text: " << translated << std::endl;

    return 0;
}
```

<br>

Compile and run the example:
```bash
g++ -o example example.cpp -I./include -L./ -ltraductor
```

```bash
./example
```


<br>
<br>

## 📚 Documentation

### `class Traductor`

#### Overview

The `Traductor` class provides a singleton interface for language translation.

#### Methods

##### `static Traductor *get()`

- **Description**: Retrieves the instance of the `Traductor` class.
- **Returns**: Pointer to the `Traductor` instance.
- **Example:**
    ```cpp
    Traductor *translator = Traductor::get();
    ```

<br>

##### `void init(bool lazyLoading = true)`

- **Description**: Initializes the `Traductor` instance.
- **Parameters**:
  - `lazyLoading` (optional, default: `true`): If `true`, translations will be loaded lazily.
- **Example:**
    ```cpp
    Traductor::get()->init();
    ```

<br>

##### `void setLang(std::string lang)`

- **Description**: Sets the language of the `Traductor` instance.
- **Parameters**:
  - `lang`: The language to set.
- **Example:**
    ```cpp
    Traductor::get()->setLang("fr_FR");
    ```

<br>

##### `std::string getLang() const`

- **Description**: Retrieves the current language of the `Traductor` instance.
- **Returns**: The current language as a string.
- **Example:**
    ```cpp
    std::string currentLang = Traductor::get()->getLang();
    ```

<br>

##### `std::string translate(std::string key)`

- **Description**: Translates a given key.
- **Parameters**:
  - `key`: The key to translate.
- **Returns**: The translated text, or the key itself if translation is not found.
- **Example:**
    ```cpp
    std::string translated = Traductor::get()->translate("hello.world");
    ```

<br>
<br>


### `class Traductor::TraductorElement`

#### Overview

The `TraductorElement` class represents an element of the translation file.

#### Methods

##### `std::string getName() const`

- **Description**: Retrieves the name of the element.
- **Returns**: The name of the element as a string.
- **Example:**
    ```cpp
    std::string elementName = element.getName();
    ```

<br>

##### `std::vector<std::string> parseElement(std::vector<std::string> &lines)`

- **Description**: Parses an element from the provided lines.
- **Parameters**:
  - `lines`: The lines to parse.
- **Returns**: The remaining lines after parsing.
- **Example:**
    ```cpp
    std::vector<std::string> remainingLines = element.parseElement(lines);
    ```

<br>

##### `std::string translate(std::string &key)`

- **Description**: Translates a given key within the element.
- **Parameters**:
  - `key`: The key to translate.
- **Returns**: The translated text, or the key itself if translation is not found.
- **Example:**
    ```cpp
    std::string translated = element.translate("hello.world");
    ```

<br>
<br>


### `class Traductor::TraductorException`

#### Overview

The `TraductorException` class represents an exception thrown by the `Traductor` class.

#### Methods

##### `TraductorException(std::string const &what, std::string const &where)`

- **Description**: Constructs a new `TraductorException` object.
- **Parameters**:
  - `what`: The message of the exception.
  - `where`: The location of the exception.
- **Example:**
    ```cpp
    throw Traductor::TraductorException("Translation file not found", "Traductor::init");
    ```

<br>

##### `const char *what() const noexcept`

- **Description**: Retrieves the message of the exception.
- **Returns**: The message of the exception as a `const char *`.
- **Example:**
    ```cpp
    try {
        // code that produce an error
    } catch (Traductor::TraductorException &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    ```

<br>

##### `const char *where() const noexcept`

- **Description**: Retrieves the location of the exception.
- **Returns**: The location of the exception as a `const char *`.
- **Example:**
    ```cpp
    try {
        // code that produce an error
    } catch (Traductor::TraductorException &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cerr << ">> " << e.where() << std::endl;
    }
    ```

<br>
<br>


## 💖 Contributing

Contributions are welcome! Please fork the repository and submit a pull request for any enhancements or bug fixes.

<br>
<br>

## 📜 License

This library is free to use, modify, and distribute. The only requirement is to give credit to the original author in any commercial or public use.

The author is not responsible for any issues or problems that may arise from using this library. As a small developer, errors may occur. If you find any errors or problems, please inform me so I can address them.

<br>
<br>

## 👨‍💻 Authors

- [dragusheen](https://github.com/dragusheen) - Initial work