/*
** EPITECH PROJECT, 2024
** traductor-library
** File description:
** TraductorError
*/

#include "Traductor.hpp"

Traductor::TraductorException::TraductorException(std::string const &what, std::string const &where)
    : _what(what), _where(where)
{
}

const char *Traductor::TraductorException::what() const noexcept
{
    return _what.c_str();
}

const char *Traductor::TraductorException::where() const noexcept
{
    return _where.c_str();
}
