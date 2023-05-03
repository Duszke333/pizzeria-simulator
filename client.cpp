#include "client.h"


Client::Client(unsigned int index) :
    id(index)
{}

unsigned int Client::get_id() const noexcept {
    return id;
}

void Client::set_id(unsigned int new_id) noexcept {
    id = new_id;
}

bool Client::operator==(const Client& other) const noexcept {
    if (this->id == other.id) return true;
    return false;
}

bool Client::operator!=(const Client& other) const noexcept {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& out, const Client& client) {
    out << "Client no. " << client.id;
    return out;
}