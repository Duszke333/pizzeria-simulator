#include "client.h"


Client::Client(unsigned int index) :
    id(index)
{}

unsigned int Client::get_id() {
    return id;
}

void Client::set_id(unsigned int new_id) {
    id = new_id;
}

std::ostream& operator<<(std::ostream& out, const Client& client) {
    out << "Client no. " << client.id;
    return out;
}