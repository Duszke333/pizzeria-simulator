#include "read.h"
#include "bad_file_exception.h"
#include "missing_data_exception.h"
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream>


Read::Read(std::string path) {
    std::ifstream file(path);
    if (!file) throw BadFileException();
    std::string line;
    while (getline(file, line)) {
        std::vector<std::string> obj;
        std::stringstream object(line);
        std::string helper;
        while (getline(object, helper, ',')) {
            obj.push_back(helper);
        }
        if (obj[0] == "DRINK") {
            add_drinks(obj);
        } else if (obj[0] == "APPETIZER") {
            add_appetizers(obj);
        } else if (obj[0] == "PIZZA") {
            add_pizzas(obj);
        } else throw MissingDataException();
    }
    file.close();
}

void Read::add_drinks(std::vector<std::string> data) {
    // Only name and price
    if (data.size() < 3) throw MissingDataException();
    std::string name = data[1];
    unsigned int price = std::stoul(data[2]);
    menu.add_drink(name, price, 1, Volume::ml330);
    menu.add_drink(name, price, 1, Volume::ml500);
    menu.add_drink(name, price, 1, Volume::l1);
}

void Read::add_appetizers(std::vector<std::string> data) {
    // Name, price and prep time
    if (data.size() < 4) throw MissingDataException();
    std::string name = data[1];
    unsigned int price = std::stoul(data[2]);
    unsigned int prep = std::stoul(data[3]);
    menu.add_appetizer(name, price, prep);
}

void Read::add_pizzas(std::vector<std::string> data) {
    // Name, price and prep time
    if (data.size() < 4) throw MissingDataException();
    std::string name = data[1];
    unsigned int price = std::stoul(data[2]);
    unsigned int prep = std::stoul(data[3]);
    menu.add_pizza(name, price, prep, Size::S);
    menu.add_pizza(name, price, prep, Size::M);
    menu.add_pizza(name, price, prep, Size::L);
    menu.add_pizza(name, price, prep, Size::XL);
}

Menu Read::get_menu() const noexcept {
    return menu;
}
