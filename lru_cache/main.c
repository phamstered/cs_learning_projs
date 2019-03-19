#include<stdio.h>
#include<stdlib.h>
#include "lru.h"

typedef struct Record{
    char* name;
    unsigned long mathGrade;
    unsigned long historyGrade;
} Record;

Record* generateRecord(char* key) 
{
    Record* rec = (Record*) malloc(sizeof(Record));
    rec->name = key;
    rec->mathGrade = rand() % 100;
    rec->historyGrade = rand() % 100;
    return rec;
}

char* randomKey(int s)
{
    //srand(seed * s);
    char ch[15] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm','n','o'};
    int number, r;
    char* a = malloc(sizeof(char)*10);
    int i;
    for(i=0; i<2; i++)
    {
        r = rand();
        number = r % 15;
        a[i] = ch[number]; 
    }
    a[i] = '\0';
    printf("number: %d, random: %d, key: %s \t", number, r, a);
    return a;
}

int main()
{
    int maxSize = 100;
    LRU_CACHE* lruc = initLRUCache(maxSize);
    for(int i=0; i<=1000; i++){
        Record* rec = (Record*) accessLRUCacheRecord(lruc, randomKey(i), (void*)generateRecord);
        printf("get value: %s, %lu \n", rec->name, rec->mathGrade);
    }
    printLRU_CACHE(lruc);
    return 0;    
}
