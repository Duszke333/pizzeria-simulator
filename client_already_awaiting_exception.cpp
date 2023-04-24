#include "client_already_awaiting_exception.h"

ClientAlreadyAwaitingException::ClientAlreadyAwaitingException():
    std::invalid_argument("Already awaiting for this client.")
{}
