
#ifndef __LRU_H__
#define __LRU_H__

typedef struct Node{
    void* val;
    const char* key;
    struct Node* pre;
    struct Node* next;
} Node;

typedef struct LRU_CAHCE{
    int maxSize;
    int curSize;
    Node** ht;
    Node* head;
    Node* tail;
}LRU_CACHE;

LRU_CACHE* initLRUCache(int maxSize);
unsigned long hashString(const char* str);
void* accessLRUCacheRecord(LRU_CACHE* lruc, const char* key, void* (*callback)(char*));
void moveLRUCacheNode(LRU_CACHE* lruc, Node* node);
void addLRUCacheRecord(const LRU_CACHE* lruc, const char* key, void* val);
void insertHeadNode(LRU_CACHE* lruc, Node* node);
void removeTailNode(LRU_CACHE* lruc);
void printLRU_CACHE(LRU_CACHE* lruc);
#endif
