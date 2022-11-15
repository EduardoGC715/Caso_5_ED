# pragma once

template<typename K, typename T>
class iNode {
    private:
        K key;
        T* data;

    public:
        iNode(K pKey, T* pData = nullptr)
        : key(pKey), data(pData)
        {}

        K get_key() {
            return key;
        }

        T* get_data() {
            return data;
        }
};