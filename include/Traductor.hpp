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

class Traductor {
    public:
        class TraductorException : public std::exception {
            public:
                TraductorException(std::string const &what, std::string const &where = "Unknown");
                const char *what() const noexcept override;
                const char *where() const noexcept;

            private:
                std::string _what;
                std::string _where;
        };

        static Traductor *get();
        ~Traductor() = default;

        void init(bool lazyLoading = true);

        void setLang(std::string lang);
        std::string getLang() const;

        std::string translate(std::string key);

    protected:
    private:
        class TraductorElement {
            public:
                TraductorElement() = default;
                ~TraductorElement() = default;

                std::string getName() const;
                std::vector<std::string> parseElement(std::vector<std::string> &lines);

                std::string translate(std::string &key);

            private:
                bool _isContainer = false;
                std::string _name;
                std::string _value;
                std::vector<std::unique_ptr<TraductorElement>> _childrens;

                std::pair<std::string, std::string> _parseKey(std::string &key);
                std::vector<std::string> _parseContainer(std::vector<std::string> &lines);
        };

        Traductor() = default;

        bool _initialized = false;
        bool _lazyLoading = true;
        std::string _lang;

        void _loadTranslation(std::string &lang);
        std::unordered_map<std::string, std::unique_ptr<TraductorElement>> _translations;
};

#endif /* !TRADUCTOR_HPP_ */
