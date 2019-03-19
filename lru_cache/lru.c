#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "lru.h"

#define MAX_BUCKETS 10000
#define MULTIPLER 5318
int MISCOUNT = 0;
int HITCOUNT = 0;

LRU_CACHE* initLRUCache(int maxSize)
{
    LRU_CACHE* lruc = (LRU_CACHE*)malloc(sizeof(LRU_CACHE));
    lruc->maxSize = maxSize;
    lruc->curSize = 0;
    lruc->ht = (Node**) malloc(sizeof(Node*) * MAX_BUCKETS);
    lruc->head = NULL;
    lruc->tail = NULL;
    return lruc;
}

// simple hash function
unsigned long hashString(const char* str)
{
    unsigned int hash = 0;
    while(*str)
    {
        hash = hash * MULTIPLER + *str++;
    }
    return hash % MAX_BUCKETS;
}

// 
void* accessLRUCacheRecord(LRU_CACHE* lruc, const char* key, void* (*callback)())
{
    int index = hashString(key);
    void* value =NULL;
    Node* hashNode = lruc->ht[index];
    if(hashNode != NULL)
    {
        // cache hitting
        printf("Cache Hitting! \n");
        HITCOUNT += 1;
        value = hashNode->val; 
        // move the recent accessed node to head
        moveLRUCacheNode(lruc, hashNode); 
    }
    else
    {
        // cache missing
        printf("Cache Missing! \n");
        MISCOUNT += 1;
        // call the callback function to get value of the key 
        value = callback(key);
        // create a new HashNode and add to LRU_CACHE
        Node* newHashNode = (Node*) malloc(sizeof(Node));
        newHashNode->key = key;
        newHashNode->val = value; 
        // if cache is full, then remove the tail node 
        if(lruc->curSize >0 && lruc->curSize >= lruc->maxSize)
        {
            // update hashTable
            lruc->ht[hashString(lruc->tail->key)] = NULL;
            removeTailNode(lruc);
        }
        // add newHashNode to head
        insertHeadNode(lruc, newHashNode);
        // update hashTable
        lruc->ht[index] = newHashNode;
        lruc->curSize+=1;
    }
    return value;
}

// move node to the head 
void moveLRUCacheNode(LRU_CACHE* lruc, Node* node)
{
    if(node != lruc->head && node != lruc->tail)
    {
        // move the middle node
        if(node->next!=NULL)      
            node->next->pre = node->pre;
        if(node->pre!=NULL)
            node->pre->next = node->next;
        node->pre=NULL;
        node->next=NULL;
        // insert the extacted node to head
        insertHeadNode(lruc, node);
    }
    if(node == lruc->tail)
    {
       // move tail node to head 
       lruc->tail = node->pre;
       lruc->tail->next = NULL;
       node->pre=NULL;
       node->next=NULL;
       insertHeadNode(lruc, node);
    }
    if(node == lruc->head)
    {
        // do nothing
    }
}

// insert node at header
void insertHeadNode(LRU_CACHE* lruc, Node* node)
{
    printf("insert node %s at head \n", node->key);
    if(lruc->head==NULL)
    {
        lruc->head = node;
        lruc->tail = lruc->head;
    }
    else
    {
        node->next = lruc->head;
        lruc->head->pre = node;
        lruc->head = node;
    }
}

void removeTailNode(LRU_CACHE* lruc)
{
    printf("remove node %s at tail \n", lruc->tail->key);
    if(lruc->tail != NULL)
    {
        Node* tmp = lruc->tail;
        lruc->tail = lruc->tail->pre;
        if(lruc->tail!=NULL)
            lruc->tail->next = NULL;
        free(tmp);
        lruc->curSize -= 1;
    }
}

void printLRU_CACHE(LRU_CACHE* lruc)
{
    Node* cur = lruc->head;
    printf("starting to traverse Chain\n");
    while(cur!=NULL ){
        printf("key: %s\n", cur->key);
        cur=cur->next;
    }
    printf("Hitting: %d, Missing: %d \n", HITCOUNT, MISCOUNT);
}

