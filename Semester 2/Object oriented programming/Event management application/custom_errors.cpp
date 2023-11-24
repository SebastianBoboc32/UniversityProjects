#include "custom_errors.h"
#include <iostream>
#include <string>

ValueError::ValueError(const char* message)
{
	this->message = message;
}

const char* ValueError::what() const noexcept
{
	return this->message;
}

RepoError::RepoError(const char* message)
{
	this->message = message;
}

const char* RepoError::what() const noexcept
{
	return this->message;
}