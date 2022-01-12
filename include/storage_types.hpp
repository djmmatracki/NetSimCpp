#ifndef SIECI_STORAGE_TYPES_HPP
#define SIECI_STORAGE_TYPES_HPP
#include "types.hpp"
#include "package.hpp"

enum class PackageQueueType
{
    FIFO,
    LIFO
};

class IPackageStockpile
{
public:
    using const_iterator = std::list<Package>::const_iterator;
    // Wszystko to to powinny byc metody wirtualne
    virtual void push(Package &&pack) = 0;
    virtual const_iterator begin() = 0;
    virtual const_iterator cbegin() = 0;
    virtual const_iterator end() = 0;
    virtual const_iterator cend() = 0;

    virtual bool empty() = 0;
    virtual size_t size() = 0;
    virtual ~IPackageStockpile() = default;
};

class IPackageQueue : public IPackageStockpile
{
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() const = 0;
};

class PackageQueue : public IPackageQueue
{
public:
    PackageQueue(PackageQueueType type) : type_(type){};
    const_iterator begin() override { return product_list_.begin(); };
    const_iterator cbegin() override { return product_list_.cbegin(); };
    const_iterator end() override { return product_list_.end(); };
    const_iterator cend() override { return product_list_.cend(); };

    void push(Package &&pack) override { product_list_.emplace_back(std::move(pack)); }
    size_t size() override { return product_list_.size(); }

    bool empty() override { return product_list_.empty(); }
    PackageQueueType get_queue_type() const override { return type_; };
    Package pop() override;

private:
    PackageQueueType type_;
    std::list<Package> product_list_;
};

#endif