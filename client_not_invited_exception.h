#pragma once
#include <stdexcept>


class ClientNotInvitedException : public std::invalid_argument {
    public:
        ClientNotInvitedException();
};
