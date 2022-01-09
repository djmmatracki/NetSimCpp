#ifndef SIECI_PACKAGE_HPP
#define SIECI_PACKAGE_HPP
#include "types.hpp"

class Package
{
public:
    Package();
    Package(ElementID el);
    // Package &operator=(Package &pac) = delete;
    Package &operator=(Package &&pac);
    Package(Package &&pack);
    ElementID get_id() const { return ElementID_; }
    ~Package();

private:
    ElementID ElementID_;
    static inline ID my_list_id_ = ID(std::set<ElementID>(), std::set<ElementID>());
};
#endif