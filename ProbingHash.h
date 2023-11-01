#ifndef __PROBING_HASH_H
#define __PROBING_HASH_H

#include <vector>
#include <stdexcept>

#include "Hash.h"

// Can be used for tracking lazy deletion for each element in your table
enum EntryState {
    EMPTY = 0,
    VALID = 1,
    DELETED = 2
};

template<typename K, typename V>
class ProbingHash : public Hash<K,V> { // derived from Hash
private:
    // Needs a table and a size.
    // Table should be a vector of std::pairs for lazy deletion
    vector<pair<K, V>> table;
    vector<EntryState> state; // Tracks the state of each element (EMPTY, VALID, DELETED)
    int numElements;
    int numBuckets;

public:
    ProbingHash(int n = 11) {
        numBuckets = n;
        numElements = 0;
        table.resize(numBuckets);
        state.resize(numBuckets, EMPTY);
    }

    ~ProbingHash() {
        this->clear();
    }

    int size() {
        return numElements;
    }

    V operator[](const K& key) {
        int initialIndex = hash(key) % numBuckets;
        int currentIndex = initialIndex;
        int probeCount = 0;

        while (state[currentIndex] != EMPTY && probeCount < numBuckets) {
            if (state[currentIndex] == VALID && table[currentIndex].first == key) {
                return table[currentIndex].second; // Key found, return the associated value
            }

            // Linear probing: move to the next index
            currentIndex = (initialIndex + probeCount) % numBuckets;
            probeCount++;
        }

        throw std::out_of_range("Key not found");
    }

    bool insert(const std::pair<K, V>& pair) {
        if (load_factor() > 0.75) {
            rehash();
        }

        int initialIndex = hash(pair.first) % numBuckets;
        int currentIndex = initialIndex;
        int probeCount = 0;

        while (probeCount < numBuckets) {
            if (state[currentIndex] == EMPTY || state[currentIndex] == DELETED) {
                table[currentIndex] = pair;
                state[currentIndex] = VALID;
                numElements++;
                return true;
            }

            if (state[currentIndex] == VALID && table[currentIndex].first == pair.first) {
                // Key already exists, update the value
                table[currentIndex].second = pair.second;
                return true;
            }

            // Linear probing: move to the next index
            currentIndex = (initialIndex + probeCount) % numBuckets;
            probeCount++;
        }

        // Unable to insert, the hash table is full
        return false;
    }

    void erase(const K& key) {
        int initialIndex = hash(key) % numBuckets;
        int currentIndex = initialIndex;
        int probeCount = 0;

        while (probeCount < numBuckets) {
            if (state[currentIndex] == EMPTY) {
                // Key not found
                return;
            }

            if (state[currentIndex] == VALID && table[currentIndex].first == key) {
                // Key found, mark as deleted
                state[currentIndex] = DELETED;
                numElements--;
                return;
            }

            // Linear probing: move to the next index
            currentIndex = (initialIndex + probeCount) % numBuckets;
            probeCount++;
        }
    }

    void clear() {
        table.clear();
        state.clear();
        numElements = 0;
        numBuckets = 11; // Reset the number of buckets
        table.resize(numBuckets);
        state.resize(numBuckets, EMPTY);
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
        vector<pair<K, V>> newTable(newBucketCount);
        vector<EntryState> newState(newBucketCount, EMPTY);

        for (int i = 0; i < numBuckets; i++) {
            if (state[i] == VALID) {
                int initialIndex = hash(table[i].first) % newBucketCount;
                int currentIndex = initialIndex;
                int probeCount = 0;

                while (probeCount < newBucketCount) {
                    if (newState[currentIndex] == EMPTY) {
                        newTable[currentIndex] = table[i];
                        newState[currentIndex] = VALID;
                        break;
                    }

                    // Linear probing: move to the next index
                    currentIndex = (initialIndex + probeCount) % newBucketCount;
                    probeCount++;
                }
            }
        }

        numBuckets = newBucketCount;
        table = std::move(newTable);
        state = std::move(newState);
    }
    
};

#endif //__PROBING_HASH_H
