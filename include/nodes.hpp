#ifndef IMPLEMENTATION_NODES_HPP
#define IMPLEMENTATION_NODES_HPP
#include "types.hpp"
#include "helpers.hpp"
#include "storage_types.hpp"
#include <memory>
#include <optional>
#include <map>

enum class ReceiverType
{
    // implement
    Worker,
    Storehouse,
    Ramp
};

// interface
/* Generacja raportów o strukturze sieci,
 * interfejs odbiorcy połproduków, powinien poznwalac na zidentyfikowanie typu odbiorcy,
 * Receiver preferences przechowuje wskaznik na IPackageReciver
 * Zwraca unikalny identyfikator danego typu odbiorcy(typ wyliczeniowy) + Id
 */
class IPackageReceiver
{
public:
    virtual void receive_package(Package &&p); //(p: Package&&)
    virtual ElementID get_id();
    virtual const_iterator begin();
    virtual const_iterator cbegin();
    virtual const_iterator end();
    virtual const_iterator cend();
};

class Storehouse : public IPackageReceiver
{
public:
    Storehouse(ElementID id, std::unique_ptr<IPackageStockpile> d) : id_(id), d_(std::move(d)) {}
    void receive_package(Package &&p) override { d_->push(std::move(p)); };
    const_iterator begin() override { d_->begin(); }
    const_iterator end() override { d_->end(); }
    const_iterator cbegin() override { d_->cbegin(); }
    const_iterator cend() override { d_->cend(); }
    ElementID get_id() override { return id_; }

private:
    ElementID id_;
    std::unique_ptr<IPackageStockpile> d_;
};

/*
 * Mapy do preferencji
 * klucz: wskaznik na odbiorce
 * wartosc: prawdopodobienstwo wyboru danego odbiorcy (suma prawdopodobienst to 1)
 * konstruktor przyjmuje uchwyt do funkcji zwracającej 'losowa' wartosc
 * dzieki polu na to /|\ wykorzystujemy do uzyskania wartosci pseudolosowej wew. met do wyboru los. odbiorce
 */

class ReceiverPreferences
{
    using preferences_t = std::map<IPackageReceiver *, double>;
    using const_iterator = preferences_t::const_iterator;

public:
    ReceiverPreferences(ProbabilityGenerator pg = probability_generator) : pg_(pg) {}
    void add_receiver(IPackageReceiver *r);           // implement
    void remove_receiver(IPackageReceiver *r);        // implement
    IPackageReceiver *choose_receiver();              // implement
    preferences_t &get_preferences() { return map_; } // implement

private:
    ProbabilityGenerator pg_;
    preferences_t map_;
};

/*
 * przechowuje obiekt preferencji odbiorcy(pole publiczne)
 */
class PackageSender
{
public:
    PackageSender(PackageSender &&) = default;
    PackageSender(){};
    void send_package(); // daj do buffera
    // 1. Sprawdzamy czy buffer pusty
    // 2. Choose receiver
    // 3. Receive package, dajemy package ktory w bufferze
    std::optional<Package> &get_sending_buffer() { return buffer_; }  // implement
    void push_package(Package &&p) { buffer_.emplace(std::move(p)); } // jezeli cos w buferze to wyslij
    ReceiverPreferences receiver_preferences;

private:
    std::optional<Package> buffer_;
};

class Ramp : public PackageSender
{
    Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {}
    void deliver_goods(Time t);                        // implement
    TimeOffset get_delivery_interval() { return di_; } // implement
    ElementID get_id() { return id_; }                 // implement

private:
    ElementID id_;
    TimeOffset di_;
};

class Worker : public PackageSender, IPackageReceiver
{
    Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q) : id_(id), pd_(pd), q_(std::move(q)) {}
    void do_work(Time t);                                // implement
    TimeOffset get_processing_duration() { return pd_; } // implement
    Time get_package_processing_start_time() {}          // implement

private:
    ElementID id_;
    TimeOffset pd_;
    std::unique_ptr<IPackageQueue> q_;
};
#endif // IMPLEMENTATION_NODES_HPP
