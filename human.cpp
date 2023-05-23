#include "human.h"


Human::Human(unsigned int index) :
    id(index)
{}

unsigned int Human::get_id() const noexcept {
    return id;
}

void Human::set_id(unsigned int new_id) noexcept {
    id = new_id;
}

bool Human::operator==(const Human& other) const noexcept {
    if (this->id == other.id) return true;
    return false;
}

bool Human::operator!=(const Human& other) const noexcept {
    return !(*this == other);
}
