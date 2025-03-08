#include "client.h"


Client::Client(unsigned int index) :
    Human(index)
{}

std::ostream& operator<<(std::ostream& out, const Client& client) {
    out << "Client no. " << client.id;
    return out;
}