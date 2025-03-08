#pragma once
#include <iostream>
#include "human.h"


class Client : public Human{
    public:
        Client(unsigned int index);
        friend std::ostream& operator<<(std::ostream& out, const Client& client);
};