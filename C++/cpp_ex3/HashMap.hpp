//
// Created by arik1 on 16/09/2019.
//

#ifndef EX_3_HASHMAP_HPP
#define EX_3_HASHMAP_HPP

#include <vector>
#include <algorithm>
#include <stdexcept>
#include <iostream>

const int DEAFULT_FIRST_CAPACITY = 16;
const int EMPTY_SIZE = 0;
const double DEAFULT_LOWER_FACTOR = 0.25;
const double DEAFULT_UPPER_FACTOR = 0.75;

/**
 * class represent hash map
 * @tparam KeyT key parameter
 * @tparam ValueT value parameter
 */
template <typename KeyT, typename ValueT>

class HashMap
{
    using bucket = std::vector<std::pair<KeyT, ValueT>>;
public:
    /**
     * constructor
     */
    HashMap() : _size(EMPTY_SIZE), _capacity(DEAFULT_FIRST_CAPACITY), _lowerFactor(DEAFULT_LOWER_FACTOR), _upperFactor(DEAFULT_UPPER_FACTOR), _table(new bucket[_capacity])
    {
    }
    /**
     * constructor
     * @param lowerFactor
     * @param upperFactor
     */
    HashMap(double lowerFactor, double upperFactor) : _size(EMPTY_SIZE), _capacity(DEAFULT_FIRST_CAPACITY), _lowerFactor(lowerFactor), _upperFactor(upperFactor), _table(new bucket[_capacity])
    {
    }
    /**
     * constructor
     * @param keys - vector of keys
     * @param vals - vector of vals
     */
    HashMap(const std::vector<KeyT>& keys, const std::vector<ValueT>& vals) : _size(EMPTY_SIZE), _capacity(DEAFULT_FIRST_CAPACITY), _lowerFactor(DEAFULT_LOWER_FACTOR), _upperFactor(DEAFULT_UPPER_FACTOR), _table(new bucket[_capacity])
    {
        if (keys.size() != vals.size())
        {
            throw std::invalid_argument("bad vec argument");
        }
        else
        {
            for (int i = 0; i < keys.size(); ++i)
            {
                insert(keys[i], vals[i]);
            }
        }
    }
    /**
     * copy constructor
     * @param other
     */
    HashMap(const HashMap &other) : _size(other._size), _capacity(other._capacity), _lowerFactor(other._lowerFactor), _upperFactor(other._upperFactor), _table(new bucket[_capacity])
    {
        if(this != &other)
        {
            for (int i = 0; i < _capacity; ++i)
            {
                _table[i] = other._table[i];
            }
        }
    }
    /**
     * move constructor
     * @param other
     */
    HashMap(const HashMap && other) noexcept : _size(other._size), _capacity(other._capacity), _lowerFactor(other._lowerFactor), _upperFactor(other._upperFactor)
    {
        _table = other._table;
        other._table = nullptr;
        other._capacity = 0;
        other._upperFactor = 0;
        other._lowerFactor = 0;
    }

    /**
     * = operator
     * @param other
     * @return
     */
    HashMap& operator=(HashMap &other)
    {
        if(this != &other)
        {
            _capacity = other._capacity;
            _size = other._size;
            _lowerFactor = other._lowerFactor;
            _upperFactor = other._upperFactor;
            delete[] _table;
            _table = new bucket[_capacity];
            for (int i = 0; i < _capacity; ++i)
            {
                _table[i] = other._table[i];
            }
        }
        return *this;
    }

    /**
     *  = move operator
     * @param other
     * @return
     */
    HashMap& operator=(HashMap && other)
    {
        if (this != &other)
        {
            delete[] _table;
            _table = other._table;
            _capacity = other._capacity;
            _size = other._size;
            _lowerFactor = other._lowerFactor;
            _upperFactor = other._upperFactor;
            other._table = nullptr;
            other._capacity = 0;
            other._upperFactor = 0;
            other._lowerFactor = 0;
        }
        return *this;
    }

    /**
     * destructor
     */
    ~HashMap()
    {
        delete [] _table;
    }

    /**
     *
     * @return the size of the map
     */
    int size() const
    {
        return _size;
    }

    /**
     *
     * @return the capacity of the map
     */
    int capacity() const
    {
        return _capacity;
    }

    /**
     *
     * @return the load factor
     */
    double getLoadFactor() const
    {
        return (double)_size / (double)_capacity;
    }

    /**
     *
     * @return true if the map is empty
     */
    bool empty() const
    {
        return !_size;
    }

    /**
     * inserts a pair to the map
     * @param key
     * @param value
     * @return true if succed
     */
    bool insert(const KeyT& key, const ValueT& value)
    {
        if (this->containsKey(key))
        {
            return false;
        }
        else
        {
            _size++;
            int place = _hashCode(key);
            std::pair<KeyT, ValueT> myPair(key, value);
            _table[place].push_back(myPair);
            if (this->getLoadFactor() > _upperFactor)
            {
                int newCapacity = _capacity * 2;
                resizeHash(newCapacity);
            }
        }
        return true;
    }

    /**
     * resize the hash map
     * @param newCapacity the new capacity we want
     */
    void resizeHash(int newCapacity)
    {
        if (newCapacity < 1)
        {
            return;
        }
        bucket *temp;
        int oldCapacity = _capacity;
        _capacity = newCapacity;
        temp = new bucket[_capacity];
        for (int i = 0 ; i < oldCapacity ; i++)
        {
            for (std::pair<KeyT, ValueT>& myPair: _table[i])
            {
                temp[_hashCode(myPair.first)].push_back(myPair);
            }
        }
        delete [] _table;
        _table = temp;
        temp = nullptr;
    }

    /**
     *
     * @param key
     * @return true if the table contain this key
     */
    bool containsKey(const KeyT& key) const
    {
        int place = _hashCode(key);
        for (auto i = _table[place].begin(); i < _table[place].end(); ++i)
        {
            if ((*i).first == key)
            {
                return true;
            }
        }
        return false;
    }

    /**
     *
     * @param key
     * @return the value of this key
     */
    ValueT& at(const KeyT& key) const
    {
        if (!containsKey(key))
        {
            throw std::invalid_argument("bad key argument");
        }
        else
        {
            int place = _hashCode(key);
            for (auto i = _table[place].begin(); i < _table[place].end(); ++i)
            {
                if ((*i).first == key)
                {
                    return (*i).second;
                }
            }
        }
    }

    /**
     * erase pair from the table
     * @param key
     * @return
     */
    bool erase(const KeyT& key)
    {
        if (!this->containsKey(key))
        {
            return false;
        }
        else
        {
            _size--;
            int place = _hashCode(key);
            for (auto i = _table[place].begin(); i != _table[place].end(); ++i)
            {
                if ((*i).first == key)
                {
                    _table[place].erase(i);
                    break;
                }
            }
            if (this->getLoadFactor() < _lowerFactor)
            {
                int newCapacity = _capacity / 2;
                resizeHash(newCapacity);
            }
        }

    }

    /**
     *
     * @param key
     * @return this keys bucket size
     */
    int bucketSize(KeyT key) const
    {
        if (!this->containsKey(key))
        {
            return 0;
        }
        int place = _hashCode(key);
        return (int)(_table[place].size());
    }

    /**
     * clear our table
     */
    void clear()
    {
        delete [] _table;
        _table = new bucket[_capacity];
        _size = 0;
    }

    /**
     * [] operator
     * @param key
     * @return
     */
    ValueT& operator[](const KeyT& key) noexcept
    {
        if (!containsKey(key))
        {
            ValueT val;
            insert(key, val);
            return at(key);
        } else
        {
            int place = _hashCode(key);
            for (auto i = _table[place].begin(); i != _table[place].end(); ++i)
            {
                if ((*i).first == key)
                {
                    return (*i).second;
                }
            }
        }
    }

    /**
     * const [] operator
     * @param key
     * @return
     */
    ValueT operator[](KeyT key) const
    {
        if (!containsKey(key))
        {
            return ;
        } else
        {
            int place = _hashCode(key);
            for (auto i = _table[place].begin(); i != _table[place].end(); ++i)
            {
                if (*i.first == key)
                {
                    return *i.second;
                }
            }
        }
    }

    /**
     * == operator
     * @param other
     * @return
     */
    bool operator==(const HashMap& other)
    {
        if(_capacity != other._capacity || _size != other._size || _lowerFactor != other._lowerFactor || _upperFactor != other._upperFactor)
        {
            return false;
        }
        else
        {
            for(int i = 0; i < _capacity; i++)
            {
                if(_table[i] != other._table[i])
                {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * != operator
     * @param other
     * @return
     */
    bool operator!=(const HashMap& other)
    {
        return !(*this == other);
    }

    /**
     * iterator class
     */
    class const_iterator
    {
    private:
        /**
         * the hash map
         */
        const HashMap<KeyT, ValueT>& _map;
        /**
         * the bucket index
         */
        int _bucketIndex;
        /**
         * the index inside the vector
         */
        int _inVecIndex;

    public:
        /**
         * constructor
         * @param map
         * @param end true if end false if begin
         */
        const_iterator(const HashMap& map, bool end) : _map(map)
        {
            if(end)
            {
                _inVecIndex = 0;
                _bucketIndex = _map._capacity;
            }
            else
            {
                _bucketIndex = 0;
                _inVecIndex = 0;
                while (_map._table[_bucketIndex].size() == 0 && _bucketIndex < _map._capacity)
                {
                    _bucketIndex++;
                }
            }
        }

        /**
         * copy constructor
         * @param other
         */
        const_iterator(const const_iterator & other) : _map(other._map)
        {
            _bucketIndex = other._bucketIndex;
            _inVecIndex = other._inVecIndex;
        }


        /**
         * operator override
         * @return
         */
        const const_iterator &operator++()
        {
            if(_inVecIndex < (int)(_map._table[_bucketIndex].size()) - 1)
            {
                _inVecIndex ++;
            }
            else
            {
                _inVecIndex = 0;
                _bucketIndex ++;
                while (_map._table[_bucketIndex].size() == 0 && _bucketIndex < _map._capacity)
                {
                    _bucketIndex++;
                }
            }
            return *this;
        }

        /**
         * operator override
         * @return
         */
        const HashMap::const_iterator operator++(int)
        {
            const_iterator copy(*this);
            operator++();
            return copy;
        }
        /**
         * operator override
         * @return
         */
        bool operator==(const const_iterator & other) const
        {
            return &(_map._table[_bucketIndex][_inVecIndex]) ==
                   &(other._map._table[other._bucketIndex][other._inVecIndex]);
        }
        /**
         * operator override
         * @return
         */
        bool operator!=(const const_iterator & other) const
        {
            return !(*this == other);
        }
        /**
         * operator override
         * @return
         */
        const std::pair<KeyT, ValueT> operator*() const
        {
            return _map._table[_bucketIndex][_inVecIndex];
        }
        /**
         * operator override
         * @return
         */
        const std::pair<KeyT, ValueT> *operator->() const
        {
            return &_map._table[_bucketIndex][_inVecIndex];
        }
        friend class HashMap;

    };

    /**
     *
     * @return  iterator to start
     */
    const_iterator begin() const
    {
        return cbegin();
    }
    /**
     *
     * @return  iterator to end
     */
    const_iterator end() const
    {
        return cend();
    }
    /**
     *
     * @return  iterator to start
     */
    const_iterator cbegin() const
    {
        return const_iterator(*this, false);
    }
    /**
     *
     * @return  iterator to end
     */
    const_iterator cend() const
    {
        return const_iterator(*this, true);
    }

private:
    /**
     * size and capacity
     */
    int _size, _capacity;
    /**
     * lower and upper load factors
     */
    double _lowerFactor, _upperFactor;
    /**
     * our hash map table
     */
    bucket *_table;
    /**
     *
     * @param key
     * @return the hash code of a key
     */
    int _hashCode(const KeyT key) const
    {
        int a = (int)(std::hash<KeyT>()(key))&(_capacity - 1);
        return a;
    }
};

#endif //EX_3_HASHMAP_HPP
