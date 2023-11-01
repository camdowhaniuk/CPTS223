/*
 *  Separate chaining hashtable
 */

#ifndef __CHAINING_HASH_H
#define __CHAINING_HASH_H

// Standard library includes
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>

// Custom project includes
#include "Hash.h"

// Namespaces to include

//
// Separate chaining based hash table - derived from Hash
//
template<typename K, typename V>
class ChainingHash : public Hash<K,V> {
private:
    vector<list<pair<K, V>>> table;
    int numElements;
    int numBuckets;

public:
    ChainingHash(int n = 11) {
        numBuckets = n;
        numElements = 0;
        table.resize(numBuckets);
    }

    ~ChainingHash() {
        this->clear();
    }

    int size() {
        return numElements;
    }

    V operator[](const K& key) {
        int bucketIndex = hash(key) % numBuckets;
    
        for (const auto& entry : table[bucketIndex]) {
            if (entry.first == key) {
                return entry.second; // Key found, return the associated value
            }
        }

        throw out_of_range("Key not found");
    }

    bool insert(const std::pair<K, V>& pair) {
        int bucketIndex = hash(pair.first) % numBuckets;
    
        // Check if the key already exists in the bucket
        for (auto& entry : table[bucketIndex]) {
            if (entry.first == pair.first) {
                // Key already exists, update the value
                entry.second = pair.second;
                return true;
            }
        }

        // Key doesn't exist in the bucket, add a new key-value pair
        table[bucketIndex].push_back(pair);
        numElements++;

        // Check if rehashing is needed (load factor > 0.75)
        if (load_factor() > 0.75) {
            rehash();
        }

        return true;
    }

    void erase(const K& key) {
        int bucketIndex = hash(key) % numBuckets;

        for (auto it = table[bucketIndex].begin(); it != table[bucketIndex].end(); ++it) {
            if (it->first == key) {
                table[bucketIndex].erase(it); // Remove the key-value pair
                numElements--;
                return;
            }
        }
    }

    void clear() {
        for (auto& bucket : table) {
            bucket.clear();
        }
        numElements = 0;
    }

    int bucket_count() {
        return numBuckets;
    }

    float load_factor() {
        return static_cast<float>(numElements) / numBuckets;
    }

private:
    int findNextPrime(int n)
    {
        while (!isPrime(n))
        {
            n++;
        }
        return n;
    }


    int isPrime(int n)
    {
        for (int i = 2; i <= sqrt(n); i++)
        {
            if (n % i == 0)
            {
                return false;
            }
        }

        return true;
    }

    int hash(const K& key) {
        return std::hash<K>{}(key);       
    }

    void rehash() {
        int newBucketCount = findNextPrime(2 * numBuckets);
        vector<list<pair<K, V>>> newTable(newBucketCount);

        for (int i = 0; i < numBuckets; i++) {
            for (const auto& entry : table[i]) {
                int newBucketIndex = hash(entry.first) % newBucketCount;
                newTable[newBucketIndex].push_back(entry);
            }
        }

        numBuckets = newBucketCount;
        table = std::move(newTable);
    }

};

#endif //__CHAINING_HASH_H
