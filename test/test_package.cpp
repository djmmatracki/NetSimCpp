#include "gtest/gtest.h"
#include "package.hpp"
#include "storage_types.hpp"

// Test sprawdzajacy konstruktor nie przyjmujacy argumentow
TEST(PackageTest, konstruktor_1)
{
    Package pack1 = Package(6);
    Package pack2 = Package(5);
    Package pack3 = Package();
    ASSERT_EQ(pack3.get_id(), 0); // Sprawdzamy czy paczka ma mozliwie najmniejszy id
    ASSERT_EQ(pack2.get_id(), 5);
    ASSERT_EQ(pack1.get_id(), 6);
    std::cout << "TEST PASSED" << std::endl;
}

// Test sprawdzajacy konstruktor przyjmujacy indeks
TEST(PackageTest, konstruktor_2)
{
    ElementID id = 1;
    Package pack = Package(id);
    ASSERT_EQ(pack.get_id(), id);
}

// Test sprawdzajacy konstruktor przyjmujacy podwojna referencje Package
TEST(PackageTest, konstruktor_3)
{
    Package pack1 = Package(2);
    Package pack2 = std::move(pack1);
    ASSERT_EQ(pack2.get_id(), 2);
}

TEST(PackageQueueTest, test_lifo)
{
    PackageQueue pq(PackageQueueType::LIFO);

    pq.push(Package(1));
    pq.push(Package(2));
    pq.push(Package(3));
    Package p = pq.pop();

    ASSERT_EQ(p.get_id(), 3);
    std::cout << "TEST PASSED!" << std::endl;
}

TEST(PackageQueueTest, test_fifo)
{
    PackageQueue pq(PackageQueueType::FIFO);

    pq.push(Package(1));
    pq.push(Package(2));
    pq.push(Package(3));

    Package p = pq.pop();

    ASSERT_EQ(p.get_id(), 1);
    std::cout << "TEST PASSED!" << std::endl;
}