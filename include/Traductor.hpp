/*
** EPITECH PROJECT, 2024
** traductor-library
** File description:
** Traductor
*/

#ifndef TRADUCTOR_HPP_
    #define TRADUCTOR_HPP_

    #include <string>
    #include <unordered_map>
    #include <exception>
    #include <memory>
    #include <regex>
    #include <vector>
    #include <fstream>
    #include <dirent.h>
    #include <iostream>

/**
 * @brief Traductor class
 *
 * @note The Traductor class is a singleton
 * @note The translations are stored in files with the following format:
 * ```
 * key1: "value1"
 * key2: "value2"
 * conainter {
 *    key3: value3
 *    key4: value4
 * }
 * ```
 * @note The translations have to be stored in a folder named `lang` in the root of the project
 * @note Each translation file has to be named "file_name.lang"
*/
class Traductor {
    public:
        /**
         * @brief TraductorException class
         * @details Exception class for the Traductor class
        */
        class TraductorException : public std::exception {
            public:
                /**
                 * @brief Construct a new Traductor Exception object
                 *
                 * @param what The message of the exception
                 * @param where The location of the exception
                */
                TraductorException(std::string const &what, std::string const &where = "Unknown");

                /**
                 * @brief Get the message of the exception
                 *
                 * @return `const char *` The message of the exception
                */
                const char *what() const noexcept override;

                /**
                 * @brief Get the location of the exception
                 *
                 * @return `const char *` The location of the exception
                */
                const char *where() const noexcept;

            private:
                /**
                 * @brief The message of the exception
                */
                std::string _what;

                /**
                 * @brief The location of the exception
                */
                std::string _where;
        };

        /**
         * @brief Get the Traductor instance
         *
         * @return `Traductor *` The Traductor instance
         * @note The Traductor class is a singleton
        */
        static Traductor *get();
        ~Traductor() = default;

        /**
         * @brief Initialize the Traductor instance
         *
         * @param lazyLoading If the translations should be loaded lazily (default: true)
         *
         * @note If lazyLoading is set to false, all the files in the `lang` folder will be loaded.
        */
        void init(bool lazyLoading = true);

        /**
         * @brief Set the language of the Traductor instance
         *
         * @param lang The language to set. The language is basically the name of the file where the translations are stored
         *
         * @note If the Traductor instance has been initialized with lazyLoading set to false, the translations will be loaded when the language is set
        */
        void setLang(std::string lang);

        /**
         * @brief Get the language of the Traductor instance
         *
         * @return `std::string` The language of the Traductor instance
        */
        std::string getLang() const;

        /**
         * @brief Translate a key
         *
         * @param key The key to translate. The key have to respect the following format: "path.to.key.through.containers"
         *
         * @return `std::string` The translation of the key. If the translation is not found, the key is returned.
        */
        std::string translate(std::string key);

    protected:
    private:
        /**
         * @brief TraductorElement class
         *
         * @note Class to represent an element of the translation file
         * @note An element can be a key-value pair or a container
        */
        class TraductorElement {
            public:
                TraductorElement() = default;
                ~TraductorElement() = default;

                /**
                 * @brief Get the name of the element
                 *
                 * @return `std::string` The name of the element
                */
                std::string getName() const;

                /**
                 * @brief Get the value of the element
                 *
                 * @return `std::string` The value of the element
                */
                std::vector<std::string> parseElement(std::vector<std::string> &lines);

                /**
                 * @brief Get the value of the element
                 *
                 * @return `std::string` The value of the element
                */
                std::string translate(std::string &key);

            private:
                /**
                 * @brief If the element is a container
                */
                bool _isContainer = false;

                /**
                 * @brief The name of the element
                */
                std::string _name;

                /**
                 * @brief The value of the element (if it's not a container)
                */
                std::string _value;

                /**
                 * @brief The children of the element (if it's a container)
                */
                std::vector<std::unique_ptr<TraductorElement>> _childrens;

                /**
                 * @brief Parse the key of the element
                 *
                 * @param key The key to parse. The key have to respect the following format: "path.to.key.through.containers"
                 *
                 * @return `std::pair<std::string, std::string>` The key parsed in a pair of strings. The first string is the name of the key, the second string is the rest of the key
                */
                std::pair<std::string, std::string> _parseKey(std::string &key);

                /**
                 * @brief Parse the container
                 *
                 * @param lines The lines to parse
                 *
                 * @return `std::vector<std::string>` The rest of the lines after the parsing
                */
                std::vector<std::string> _parseContainer(std::vector<std::string> &lines);
        };

        Traductor() = default;

        /**
         * @brief If the Traductor instance has been initialized
        */
        bool _initialized = false;

        /**
         * @brief If the translations should be loaded lazily
         *
         * @note If lazyLoading is set to false, all the files in the `lang` folder will be loaded at the initialization
        */
        bool _lazyLoading = true;

        /**
         * @brief The language of the Traductor instance
        */
        std::string _lang;

        /**
         * @brief The translations
        */
        std::unordered_map<std::string, std::unique_ptr<TraductorElement>> _translations;

        /**
         * @brief Load the translations
         *
         * @param lang The language to load
        */
        void _loadTranslation(std::string &lang);
};

#endif /* !TRADUCTOR_HPP_ */
