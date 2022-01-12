#include "nodes.hpp"
#include <iostream>
#include <cmath>

void ReceiverPreferences::add_receiver(IPackageReceiver *r)
{
    size_t n = map_.size();
    if (n != 0)
    {
        map_[r] = 0;
        double prob = 1 / (double)(n + 1);
        for (auto const &[key, val] : map_)
        {
            map_[key] = prob;
        }
    }
    else
    {
        map_[r] = 1.0;
    }
}

void ReceiverPreferences::remove_receiver(IPackageReceiver *r)
{
    map_.erase(r);
    size_t n = map_.size();
    double prob = 1 / (double)n;

    for (auto const &[key, val] : map_)
    {
        map_[key] = prob;
    }
}

IPackageReceiver *ReceiverPreferences::choose_receiver()
{
    // Da sie prosciej
    double prob = pg_();
    double sum = 0;

    for (auto const &[key, val] : map_)
    {
        sum += val;
        if (sum >= prob)
        {
            return key;
        }
    }
    auto i = map_.end();
    i--;
    return i->first;
}

void PackageSender::send_package()
{
    if (buffer_.has_value())
    {
        Package p = std::move(buffer_.value());
        IPackageReceiver *rec = receiver_preferences_.choose_receiver();
        rec->receive_package(std::move(p));
        buffer_.reset();
    }
}

void Ramp::deliver_goods(Time t)
{
    if (std::fmod(t, di_) == 0)
    {
        send_package();
    }
    else
    {
        push_package(Package());
    }
}

void Worker::do_work(Time t)
{
    if (startTime_ + pd_ < t && get_sending_buffer().has_value())
    {
        // Moze przetworzyc
        startTime_ = t;
        send_package();
    }
    else if (!get_sending_buffer().has_value())
    {
        push_package(q_->pop());
    }
}