#include <iostream>
#include <vector>
#include "client.h"


class Group {
    private:
        unsigned int group_id;
        unsigned int group_size;
        bool group_complete;
        std::vector<Client> clients;
        std::vector<unsigned int> awaiting_ids;
    public:
        Group(unsigned int id=0);

        unsigned int get_id();
        unsigned int get_group_size();
        void set_id(unsigned int new_id);

        void add_client(Client new_client);
        void remove_client(Client ex_client) noexcept;

        void add_awaiting(unsigned int client_id);
        void remove_awaiting(unsigned int client_id) noexcept;

        void join(Client client);

        bool is_complete() const noexcept;

        friend std::ostream& operator<<(std::ostream& out, const Group& group);
};
