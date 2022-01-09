#include "storage_types.hpp"
#include "package.hpp"

Package PackageQueue::pop()
{
    switch (type_)
    {
    case (PackageQueueType::LIFO):
    {
        auto e = std::move(*product_list_.end());
        product_list_.pop_back();
        return e;
    }

    case (PackageQueueType::FIFO):
    {
        Package e = std::move(*product_list_.begin());
        product_list_.pop_front();
        return e;
    }
    default:
        throw;
    }
}