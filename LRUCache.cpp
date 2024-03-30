/*
 * Design a data structure that follows the constraints of a Least Recently Used (LRU) cache.

Implement the LRUCache class:

LRUCache(int capacity) Initialize the LRU cache with positive size capacity.
Implement 2 APIs,

int get(int key)
Return the value of the key if the key exists, otherwise return -1.


void put(int key, int value)
Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. If the number of keys exceeds the capacity from this operation, evict the least recently used key.


The functions get and put must each run in O(1) average time complexity.
*/

#include <iostream>
#include <unordered_map>

class Node{
public:
    Node(int k, int v): key(k), val(v) {
        next = nullptr;
    }

    int key;
    int val;
    Node* prev;
    Node* next;
};

class LRUCache {
    public:
        LRUCache(int capacity): cap_(capacity) {
            head_ = new Node(-1):
            tail_ = new Node(-1);
            head_->next = head_->prev = tail_;
            tail_->next = tail_->prev = head_;
        }

        ~LRUCache() {
            release(head_);

        }

        int get(int key) {
            auto iter = index_.find(key);
            if (iter == index_.end()) {
                return -1;
            }

            auto* node = iter->second;
            attach(head_, detach(node));
            return node->val;
        }

        void put(int key, int value) {
            auto iter = index_.find(key);
            if (iter != index_.end()) {
                iter->second->val = value;
                attach(head_, detach(iter->second));
                return;
            }

            Node* node = new Node(key, value);
            index_[key] = attach(head_, node);

            if (index_.size() > cap_) {
                auto to_del = detach(tail_->prev);
                index_.erase(to_del->key);
                delete to_del;
            }
        }

    private:
        void release(head_) {
            // release all the memory
        }

        Node* detach(Node* node) {
            node->next->prev = node->prev;
            node->prev->next = node->next;
            return node;
        }

        void attach(Node* head, Node* node) {
            node->next = head->next;
            node->prev = head;

            head->next->prev = node;
            head->next = node;
        }


    private:
        int cap_;
        Node* head_;
        Node* tail_;
        std::unordered_map<int, Node> index_;

};


