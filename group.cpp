#include <algorithm>
#include "group.h"
#include "client_already_in_exception.h"
#include "client_already_awaiting_exception.h"
#include "client_not_invited_exception.h"


Group::Group() :
    group_id(0),
    group_size(0),
    group_complete(true)
{}

Group::Group(unsigned int id) :
    group_id(id),
    group_size(0),
    group_complete(true)
{}

unsigned int Group::get_id() {
    return group_id;
}

unsigned int Group::get_group_size() {
    return group_size;
}

void Group::set_id(unsigned int new_id) {
    group_id = new_id;
}

void Group::add_client(Client new_client) {
    for (Client& client : clients) if (client == new_client) throw ClientAlreadyInException();
    clients.push_back(new_client);
    group_size ++;
}

void Group::remove_client(Client ex_client) noexcept {
    auto it = std::find(clients.begin(), clients.end(), ex_client);
    if (it != clients.end()){
        clients.erase(it);
        group_size--;
    }
}

void Group::add_awaiting(unsigned int client_id) {
    for (unsigned int& id : awaiting_ids) if (id == client_id) throw ClientAlreadyAwaitingException();
    awaiting_ids.push_back(client_id);
    group_size++;
    group_complete = false;
}

void Group::remove_awaiting(unsigned int client_id) noexcept {
    auto it = std::find(awaiting_ids.begin(), awaiting_ids.end(), client_id);
    if (it != awaiting_ids.end()) {
        awaiting_ids.erase(it);
        group_size--;
        if (awaiting_ids.size() == 0) group_complete = true;
    }
}

void Group::join(Client client) {
    unsigned int client_id = client.get_id();
    auto it = std::find(awaiting_ids.begin(), awaiting_ids.end(), client_id);
    if (it == awaiting_ids.end()) throw ClientNotInvitedException();
    clients.push_back(client);
    awaiting_ids.erase(it);
    if(awaiting_ids.size() == 0) group_complete = true;
}

bool Group::is_complete() const noexcept {
    return group_complete;
}

std::ostream& operator<<(std::ostream& out, const Group& group) {
    out << "Group no. " << group.group_id << std::endl;
    out << "Clients: " << std::endl;
    for (auto cl : group.clients) out << cl << std::endl;
    out << "Awaiting: ";
    for (auto id : group.awaiting_ids) out << id << ", ";
    out << std::endl;
    return out;
}