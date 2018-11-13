#pragma once
#ifndef FEXCEPTION_H
#define FEXCEPTION_H

#include <exception>
#include <string>




struct NULL_exception : std::exception {
	NULL_exception(const char * msg) : std::exception{msg}{}
	NULL_exception() = default;
};




#endif // !FEXCEPTION_H