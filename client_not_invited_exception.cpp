#include "client_not_invited_exception.h"


ClientNotInvitedException::ClientNotInvitedException() :
    std::invalid_argument("Client was not invited or is already a part of the group.")
{}