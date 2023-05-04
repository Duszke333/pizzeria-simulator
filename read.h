#pragma once
#include <string>
#include <vector>
#include "menu.h"

class Read {
    private:
        Menu menu;
        void add_drinks(std::vector<std::string> data);
        void add_appetizers(std::vector<std::string> data);
        void add_pizzas(std::vector<std::string> data);
    public:
        Read(std::string path);
        Menu get_menu() const noexcept;
};