#pragma once
#include <stdexcept>


class ClientAlreadyInException : public std::invalid_argument {
    public:
        ClientAlreadyInException();
};
