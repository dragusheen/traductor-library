/*
** EPITECH PROJECT, 2024
** traductor-library
** File description:
** TraductorElement
*/

#include "Traductor.hpp"

std::string Traductor::TraductorElement::getName() const
{
    return _name;
}

std::vector<std::string> Traductor::TraductorElement::parseElement(std::vector<std::string> &lines)
{

    std::regex traductionRegex("^([a-zA-Z0-9_-]+): \"(.*)\"");
    std::regex containerRegex("(^([a-zA-Z0-9_-]+) \\{$)");
    std::smatch match;

    if (std::regex_match(lines[0], match, traductionRegex)) {
        _name = match[1];
        _value = match[2];
        _value = std::regex_replace(_value, std::regex("\\\\\""), "\"");
        _value = std::regex_replace(_value, std::regex("\\\\n"), "\n");
        return std::vector<std::string>(lines.begin() + 1, lines.end());
    }
    if (std::regex_match(lines[0], match, containerRegex))
        return _parseContainer(lines);
    throw Traductor::TraductorException("Invalid line: [" + lines[0] + "]", "TraductorElement::parseElement");
}

std::string Traductor::TraductorElement::translate(std::string &key)
{
    if (key.empty()) {
        if (_isContainer)
            throw Traductor::TraductorException("\"" + _name + "\" is a container", "TraductorElement::translate");
        return _value;
    }
    std::pair<std::string, std::string> parsedKey = _parseKey(key);
    for (auto &child : _childrens) {
        if (child->getName() == parsedKey.first)
            return child->translate(parsedKey.second);
    }
    throw Traductor::TraductorException("Key :\"" + key + "\" not found in \"" + _name + "\"", "TraductorElement::translate");
}


std::pair<std::string, std::string> Traductor::TraductorElement::_parseKey(std::string &key)
{
    std::pair<std::string, std::string> result;
    if (key.find('.') == std::string::npos) {
        result.first = key;
        result.second = "";
        return result;
    }
    result.first = key.substr(0, key.find('.'));
    result.second = key.substr(key.find('.') + 1);
    return result;
}

std::vector<std::string> Traductor::TraductorElement::_parseContainer(std::vector<std::string> &lines)
{
    std::regex endContainerRegex("^\\}$");
    std::smatch match;

    _isContainer = true;
    _name = lines[0];
    _name = _name.substr(0, _name.size() - 2);
    lines.erase(lines.begin());
    while (!lines.empty()) {
        if (std::regex_match(lines[0], match, endContainerRegex))
            return std::vector<std::string>(lines.begin() + 1, lines.end());
        std::unique_ptr<TraductorElement> child = std::make_unique<TraductorElement>();
        lines = child->parseElement(lines);
        std::string childName = child->getName();
        for (auto &c : _childrens) {
            if (c->getName() == childName)
                throw Traductor::TraductorException("Duplicate key: \"" + childName + "\" in \"" + _name + "\"", "TraductorElement::_parseContainer");
        }
        _childrens.push_back(std::move(child));
    }
    throw Traductor::TraductorException("Missing end of container in \"" + _name + "\"", "TraductorElement::_parseContainer");
}
