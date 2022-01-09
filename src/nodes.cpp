#include "nodes.hpp"
#include <cmath>

void ReceiverPreferences::add_receiver(IPackageReceiver *r)
{
    size_t n = map_.size();
    map_[r] = 0;
    double prob = 1 / n;
    for (auto const &[key, val] : map_)
    {
        map_[key] = prob;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r)
{
    map_.erase(r);
    size_t n = map_.size();
    double prob = 1 / n;

    for (auto const &[key, val] : map_)
    {
        map_[key] = prob;
    }
}

IPackageReceiver *ReceiverPreferences::choose_receiver()
{
    // Da sie prosciej
    double prob = pg_();
    int sum = 0;

    for (auto const &[key, val] : map_)
    {
        if (sum >= prob)
        {
            return key;
        }
        sum += val;
    }
}

void PackageSender::send_package()
{
    if (buffer_.has_value())
    {
        Package p = std::move(buffer_.value());
        IPackageReceiver *rec = receiver_preferences.choose_receiver();
        rec->receive_package(std::move(p));
    }
}

void Ramp::deliver_goods(Time t)
{
    if (std::fmod(t, di_) == 0)
    {
        push_package(Package());
    }
}

void Worker::do_work(Time t)
{
    //
}