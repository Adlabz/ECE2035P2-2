/*
 Student Name: Aditya Jituri
 Date: 3/25/19

=======================
ECE 2035 Project 2-1:
=======================
This file provides definition for the structs and functions declared in the
header file. It also contains helper functions that are not accessible from
outside of the file.

FOR FULL CREDIT, BE SURE TO TRY MULTIPLE TEST CASES and DOCUMENT YOUR CODE.

===================================
Naming conventions in this file:
===================================
1. All struct names use camel case where the first letter is capitalized.
  e.g. "HashTable", or "HashTableEntry"

2. Variable names with a preceding underscore "_" will not be called directly.
  e.g. "_HashTable", "_HashTableEntry"

  Recall that in C, we have to type "struct" together with the name of the struct
  in order to initialize a new variable. To avoid this, in hash_table.h
  we use typedef to provide new "nicknames" for "struct _HashTable" and
  "struct _HashTableEntry". As a result, we can create new struct variables
  by just using:
    - "HashTable myNewTable;"
     or
    - "HashTableEntry myNewHashTableEntry;"

  The preceding underscore "_" simply provides a distinction between the names
  of the actual struct defition and the "nicknames" that we use to initialize
  new structs.
  [See Hidden Definitions section for more information.]

3. Functions, their local variables and arguments are named with camel case, where
  the first letter is lower-case.
  e.g. "createHashTable" is a function. One of its arguments is "numBuckets".
       It also has a local variable called "newTable".

4. The name of a struct member is divided by using underscores "_". This serves
  as a distinction between function local variables and struct members.
  e.g. "num_buckets" is a member of "HashTable".

*/

/****************************************************************************
* Include the Public Interface
*
* By including the public interface at the top of the file, the compiler can
* enforce that the function declarations in the the header are not in
* conflict with the definitions in the file. This is not a guarantee of
* correctness, but it is better than nothing!
***************************************************************************/
#include "hash_table.h"
#include "globals.h"


/****************************************************************************
* Include other private dependencies
*
* These other modules are used in the implementation of the hash table module,
* but are not required by users of the hash table.
***************************************************************************/
#include <stdlib.h>   // For malloc and free
#include <stdio.h>    // For printf


/****************************************************************************
* Hidden Definitions
*
* These definitions are not available outside of this file. However, because
* the are forward declared in hash_table.h, the type names are
* available everywhere and user code can hold pointers to these structs.
***************************************************************************/
/**
 * This structure represents an a hash table.
 * Use "HashTable" instead when you are creating a new variable. [See top comments]
 */
struct _HashTable {
  /** The array of pointers to the head of a singly linked list, whose nodes
      are HashTableEntry objects */
  HashTableEntry** buckets;

  /** The hash function pointer */
  HashFunction hash;

  /** The number of buckets in the hash table */
  unsigned int num_buckets;
};

/**
 * This structure represents a hash table entry.
 * Use "HashTableEntry" instead when you are creating a new variable. [See top comments]
 */
struct _HashTableEntry {
  /** The key for the hash table entry */
  unsigned int key;

  /** The value associated with this hash table entry */
  void* value;

  /**
  * A pointer pointing to the next hash table entry
  * NULL means there is no next entry (i.e. this is the tail)
  */
  HashTableEntry* next;
};


/****************************************************************************
* Private Functions
*
* These functions are not available outside of this file, since they are not
* declared in hash_table.h.
***************************************************************************/
/**
* createHashTableEntry
*
* Helper function that creates a hash table entry by allocating memory for it on
* the heap. It initializes the entry with key and value, initialize pointer to
* the next entry as NULL, and return the pointer to this hash table entry.
*
* @param key The key corresponds to the hash table entry
* @param value The value stored in the hash table entry
* @return The pointer to the hash table entry
*/
static HashTableEntry* createHashTableEntry(unsigned int key, void* value) {
    // allocate space for the new entry on heap
    HashTableEntry* newEntry;
    if (!(newEntry = (HashTableEntry*)malloc(sizeof(HashTableEntry)))) {
        exit(1);
    }
    // set components of new entry
    newEntry->key = key;
    newEntry->value = value;
    newEntry->next = NULL;
    // return the newly created entry
    return newEntry;
}

/**
* findItem
*
* Helper function that checks whether there exists the hash table entry that
* contains a specific key.
*
* @param hashTable The pointer to the hash table.
* @param key The key corresponds to the hash table entry
* @return The pointer to the hash table entry, or NULL if key does not exist
*/
static HashTableEntry* findItem(HashTable* hashTable, unsigned int key) {
    pc.printf("fhtest0\r\n");
    // get the hash value of the key to use as index for buckets
    pc.printf("fhtest1\r\n");
    int hashValue = hashTable->hash(key);
    pc.printf("fhtest2\r\n");
    // get head of linked list that the entry would be in if it exists
    HashTableEntry * llHead = hashTable->buckets[hashValue];
    pc.printf("fhtest3\r\n");
    // standard linked list find as shown in class
    while (llHead) {
        pc.printf("fhtest4\r\n");
        // if the current node has the key we're looking for, return it
        if (llHead->key == key) {
            return llHead;
        }
        pc.printf("fhtest5\r\n");
        // otherwise go to the next node
        llHead = llHead->next;
        pc.printf("fhtest6\r\n");
    }
    pc.printf("fhtest7\r\n");
    // if we reach the end of the linked list without returning, return NULL
    return NULL;
}

/****************************************************************************
* Public Interface Functions
*
* These functions implement the public interface as specified in the header
* file, and make use of the private functions and hidden definitions in the
* above sections.
****************************************************************************/
// The createHashTable is provided for you as a starting point.
HashTable* createHashTable(HashFunction hashFunction, unsigned int numBuckets) {
  // The hash table has to contain at least one bucket. Exit gracefully if
  // this condition is not met.
  if (numBuckets==0) {
    printf("Hash table has to contain at least 1 bucket...\n");
    exit(1);
  }

  // Allocate memory for the new HashTable struct on heap.
  HashTable* newTable = (HashTable*)malloc(sizeof(HashTable));

  // Initialize the components of the new HashTable struct.
  newTable->hash = hashFunction;
  newTable->num_buckets = numBuckets;
  if(!(newTable->buckets
            = (HashTableEntry**)malloc(numBuckets*sizeof(HashTableEntry*)))) {
    exit(1);
  }
  // ^ I think Dr. Schimmel said it was bad practice not to check if malloc
  // returned something so I changed these lines to reflect that

  // As the new buckets contain indeterminant values, init each bucket as NULL.
  unsigned int i;
  for (i=0; i<numBuckets; ++i) {
    newTable->buckets[i] = NULL;
  }

  // Return the new HashTable struct.
  return newTable;
}

/**
 * destroyHashTable
 *
 * frees all allocated space (table, buckets, entries, values)
 *
 * @param hashTable hashTable being destroyed
 */
void destroyHashTable(HashTable* hashTable) {
    // go through each bucket
    for (int i = 0; i < hashTable->num_buckets; i++) {
        HashTableEntry * thisNode = hashTable->buckets[i];
        // delete each node
        while (thisNode) {
            // keep the next node because the current node will be deleted
            HashTableEntry * nextNode = thisNode->next;
            // free data at value pointer
            free(thisNode->value);
            thisNode->value = NULL;
            thisNode->key = NULL;
            thisNode->next = NULL;
            free(thisNode);
            thisNode = NULL;
            // set thisNode to the stored nextNode
            thisNode = nextNode;
        }
    }
    //free buckets
    free(hashTable->buckets);
    hashTable->buckets = NULL;
    hashTable->num_buckets = NULL;
    // DO NOT free(hashTable->hash) because it may belong to other hashTables
    hashTable->hash = NULL;
    // last, free the hashTable itself (address is passed by value so
    // setting it to NULL does nothing productive)
    free(hashTable);
}
/**
 * insertItem
 *
 * inserts item into hashTable. Modifies value if key already exists
 *
 * @param hashTable hashTable
 * @param key       key
 * @param value     pointer to value
 * @return pointer to old value if overwritten or NULL
 */
void* insertItem(HashTable* hashTable, unsigned int key, void* value) {
    pc.printf("htest0\r\n");
    HashTableEntry* thisNode;
    pc.printf("htest1\r\n");
    if (thisNode = findItem(hashTable, key)) {
        pc.printf("htest2\r\n");
        void* pointer = thisNode->value;
        thisNode->value = value;
        return pointer;
    }
    pc.printf("htest3\r\n");
    // get the hash value of the key to use as index for buckets
    int hashValue = hashTable->hash(key);
    pc.printf("htest4\r\n");
    // get head of linked list that the entry should go into
    HashTableEntry * llHead = hashTable->buckets[hashValue];
    pc.printf("htest5\r\n");
    // make new entry and set next as appropriate
    HashTableEntry * entry = createHashTableEntry(key, value);
    pc.printf("htest6\r\n");
    entry->next = llHead;
    pc.printf("htest7\r\n");
    hashTable->buckets[hashValue] = entry;
    pc.printf("htest8\r\n");
    // return NULL since nothing was overwritten
    return NULL;
}
/**
 * getItem
 *
 * gets value of item with given key. Returns NULL if key not present
 *
 * @param hashTable hashTable
 * @param key       key
 * @return pointer to value or NULL if entry does not exist
 */
void* getItem(HashTable* hashTable, unsigned int key) {
    HashTableEntry* thisNode;
    if (thisNode = findItem(hashTable, key)) {
        return (thisNode->value);
    }
    return NULL;
}
/**
 * removeItem
 *
 * remove and return value of entry in hashTable with given key
 *
 * @param hashTable hashTable
 * @param key        key
 * @return pointer to value or NULL if entry does not exist
 */
void* removeItem(HashTable* hashTable, unsigned int key) {
    // get the hash value of the key to use as index for buckets
    int hashValue = hashTable->hash(key);
    // get head of linked list that the entry would be in if it exists
    // and a trailing node for deletion
    HashTableEntry * prev = hashTable->buckets[hashValue];
    HashTableEntry * curr = hashTable->buckets[hashValue];
    if(curr){
    //edge case where key is at start of linked list
        if (curr->key == key) {
            // point head to next node
            hashTable->buckets[hashValue] = curr->next;
            // save pointer to value and free current node
            void* pointer = curr->value;
            curr->key= NULL;
            curr->next=NULL;
            curr->value=NULL;
            free(curr);
            return pointer;
        }
        curr = curr->next;
    }
    // standard linked list find as shown in class
    while (curr) {
        // if the current node has the key we're looking for, return it
        if (curr->key == key) {
            // update trailing node's next to current node's next to delete it
            prev->next = curr->next;
            // save pointer while deleting the current entry
            void* pointer = curr->value;
            // overwrite data so it cannot be re-read
            // value cannot be overwritten because we don't know what it is
            curr->key= NULL;
            curr->next=NULL;
            curr->value=NULL;
            free(curr);
            return pointer;
        }
        // otherwise go to the next node
        prev = curr;
        curr = curr->next;
    }
    // if we reach the end of the linked list without returning, return NULL
    return NULL;
}
/**
 * deleteItem
 *
 * remove without returning & 'free' value
 *
 * @param HashTable hashTable
 * @param key       key
 */
void deleteItem(HashTable* hashTable, unsigned int key) {
    // remove with freeing of value as well
    void* pointer = removeItem(hashTable, key);
    // free value (may or may not work since we did not allocate this data)
    free(pointer);
}
