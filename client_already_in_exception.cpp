#include "client_already_in_exception.h"


ClientAlreadyInException::ClientAlreadyInException() :
    std::invalid_argument("Client already in the group.")
{}
