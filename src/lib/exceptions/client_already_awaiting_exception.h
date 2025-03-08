#pragma once
#include <stdexcept>


class ClientAlreadyAwaitingException : public std::invalid_argument {
    public:
        ClientAlreadyAwaitingException();
};
