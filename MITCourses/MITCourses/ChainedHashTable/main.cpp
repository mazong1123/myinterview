#include <iostream>
#include "ChainedHashTable.h"

int main()
{
    ChainedHashTable ht;
    ht.set("key1", "value1");
    ht.set("key2", "value2");
    ht.set("key3", "value3");
    ht.set("key4", "value4");
    ht.set("key5", "value5");
    ht.set("key6", "value6");
    ht.set("key7", "value7");

    std::string v = ht.get("key2");

    ht.remove("key2");

    ht.set("key3", "value5");

    return 0;
}