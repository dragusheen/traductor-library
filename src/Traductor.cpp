/*
** EPITECH PROJECT, 2024
** traductor-library
** File description:
** Traductor
*/

#include "Traductor.hpp"

Traductor *Traductor::get()
{
    static Traductor instance;
    return &instance;
}

void Traductor::init(bool lazyLoading)
{
    _lazyLoading = lazyLoading;
    _initialized = true;

    if (_lazyLoading) return;

    DIR *dir = opendir("lang");
    struct dirent *entry;

    if (!dir)
        throw TraductorException("Could not open directory: lang", "Traductor::init");
    while ((entry = readdir(dir))) {
        if (entry->d_type == DT_REG) {
            std::string lang = entry->d_name;
            lang = lang.substr(0, lang.find_last_of('.'));
            _loadTranslation(lang);
        }
    }
    closedir(dir);
}

void Traductor::setLang(std::string lang)
{
    if (!_initialized)
        throw TraductorException("Traductor not initialized", "Traductor::setLang");
    if (_lazyLoading && _translations.find(lang) == _translations.end())
        _loadTranslation(lang);
    if (_translations.find(lang) == _translations.end())
        throw TraductorException("Language not found: " + lang, "Traductor::setLang");
    _lang = lang;
}

std::string Traductor::getLang() const
{
    if (!_initialized)
        throw TraductorException("Traductor not initialized", "Traductor::getLang");
    if (_lang.empty())
        throw TraductorException("No language set", "Traductor::getLang");

    return _lang;
}

std::string Traductor::translate(std::string key)
{
    if (!_initialized)
        throw TraductorException("Traductor not initialized", "Traductor::translate");
    if (_lang.empty())
        throw TraductorException("No language set", "Traductor::translate");
    if (_translations.find(_lang) == _translations.end())
        throw TraductorException("Language not found: " + _lang, "Traductor::translate");

    try {
        return _translations[_lang]->translate(key);
    } catch (TraductorException &e) {
        return key;
    }
}


void Traductor::_loadTranslation(std::string &lang)
{
    std::string path = "lang/" + lang + ".trad";
    std::ifstream file(path);
    std::string line;
    std::vector<std::string> lines;

    if (!file.is_open())
        throw TraductorException("Could not open file: " + path, "Traductor::_loadTranslation");
    lines.push_back(lang + " {");
    while (std::getline(file, line))
        lines.push_back(line);
    file.close();
    lines.push_back("}");

    for (std::size_t i = 0; i < lines.size();) {
        std::string cleaned = std::regex_replace(lines[i], std::regex("^\\s+"), "");
        cleaned = std::regex_replace(cleaned, std::regex("\\s+$"), "");
        lines[i] = cleaned;
        if (cleaned.empty()) {
            lines.erase(lines.begin() + i);
            continue;
        }
        char lastChar = cleaned[cleaned.size() - 1];
        if (lastChar == '{' || lastChar == '}' || lastChar == '"') {
            i++;
            continue;
        }
        while (lastChar != '"' && i + 1 < lines.size()) {
            cleaned += "\\n" + lines[i + 1];
            lastChar = cleaned[cleaned.size() - 1];
            lines.erase(lines.begin() + i + 1);
        }
        lines[i] = cleaned;
        i++;
    }

    _translations[lang] = std::make_unique<TraductorElement>();
    _translations[lang]->parseElement(lines);
}
