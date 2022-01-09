#include "package.hpp"
#include <iostream>

ElementID find_min(std::set<ElementID>::iterator begin, std::set<ElementID>::iterator end)
{
    ElementID min_val = 999999;
    for (auto it = begin; it != end; ++it)
    {
        if (min_val > *it)
        {
            min_val = *it;
        }
    }
    return min_val;
}
ElementID find_max(std::set<ElementID>::iterator begin, std::set<ElementID>::iterator end)
{
    ElementID max_val = 0;
    for (auto it = begin; it != end; ++it)
    {
        if (max_val < *it)
        {
            max_val = *it;
        }
    }
    return max_val;
}

Package::Package()
{
    freed_IDs freedIdSet = my_list_id_.second;
    assigned_IDs assignedIdSet = my_list_id_.first;

    if (!freedIdSet.empty())
    {
        // Jezeli nie jest puste to zabieramy z freed ids
        // Usuwamy z tego
        ElementID id = find_min(freedIdSet.begin(), freedIdSet.end());
        ElementID_ = std::move(id);

        assignedIdSet.insert(id);
        freedIdSet.erase(id);
    }
    else
    {
        ElementID max_id = find_max(assignedIdSet.begin(), assignedIdSet.end());
        for (ElementID i = 1; i <= max_id + 1; ++i) // 1 do max + 1
        {
            if (assignedIdSet.find(i) == assignedIdSet.end())
            {
                ElementID_ = std::move(i);
                break;
            }
        }

        assignedIdSet.insert(ElementID_);
    }

    my_list_id_ = ID(assignedIdSet, freedIdSet);
}

Package::Package(ElementID el)
{
    if (my_list_id_.first.find(el) == my_list_id_.first.end())
    {
        my_list_id_.first.insert(el);
    }
    ElementID_ = std::move(el);
}

Package::~Package()
{
    my_list_id_.second.insert(ElementID_);
    my_list_id_.first.erase(ElementID_);
}

Package::Package(Package &&pack)
{
    ElementID_ = std::move(pack.ElementID_);
}
Package &Package::operator=(Package &&pack)
{
    ElementID_ = std::move(pack.ElementID_);
    return (*this);
}