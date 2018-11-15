#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "Debug.h"
#include "symbol.h"

/** @file symbol.c
 *  @brief You will modify this file and implement the symbol.h interface
 *  @details Your implementation of the functions defined in symbol.h.
 *  You may add other functions if you find it helpful. Added functions
 *  should be declared <b>static</b> to indicate they are only used
 *  within this file.
 * <p>
 * @author <b> Luke Burford</b> goes here
 */

/** size of LC3 memory */
#define LC3_MEMORY_SIZE  (1 << 16)

/** Provide prototype for strdup() */
char *strdup(const char *s);

/** Defines the data structure used to store nodes in the hash table */
typedef struct node {
  struct node* next;     /**< linked list of symbols at same index */
  int          hash;     /**< hash value - makes searching faster  */
  symbol_t     symbol;   /**< the data the user is interested in   */
} node_t;

/** Defines the data structure for the symbol table */
struct sym_table {
  int      size;        /**< size of hash table          */
  node_t** hash_table;  /**< array of node_t pointers    */
  char**   addr_table;  /**< array of character pointers */
};

/** djb hash - found at http://www.cse.yorku.ca/~oz/hash.html
 * tolower() call to make case insensitive.
 */

static int symbol_hash (const char* name) {
  unsigned char* str  = (unsigned char*) name;
  unsigned long  hash = 5381;
  int c;

  while ((c = *str++))
    hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */

  c = hash & 0x7FFFFFFF; /* keep 31 bits - avoid negative values */

  return c;
}


sym_table_t* symbol_init (int table_size) {
  debug("symbol_init was called with table_size = %d", table_size);
  /* malloc the entire struct of symbol table */
  sym_table_t* pst = malloc(sizeof(sym_table_t));
  /* set the size member in pst to the parameter table_size */
  pst->size = table_size;
  /* calloc the array of pointers of node */
  node_t *pNode[pst->size];
  pst->hash_table = pNode;
  pst->hash_table = calloc(pst->size, sizeof(node_t*));
  /* calloc the array of pointers of char */
  char *pAddr[LC3_MEMORY_SIZE];
  pst->addr_table = pAddr;
  pst->addr_table = calloc(LC3_MEMORY_SIZE, sizeof(char*));
  return pst;
}

void symbol_add_unique (sym_table_t* symTab, const char* name, int addr) {
    /* create nameCopy in order to preserve the name parameter constant */
    char *nameCopy = strdup(name);
    int hashVal = symbol_hash(name);
    debug("Symbol name: %s into hash value: %i",name, hashVal);
    /* get the index for the has table */
    int index = hashVal % symTab->size;
    debug("index from hashVal: %d",index);
    /* create a new node struct and init its memebers */
    node_t* node = malloc(sizeof(node_t));
	if(symTab->hash_table[index] != NULL) {
		debug("non null pointer: %s at index: %i", symTab->hash_table[index]->symbol.name, index);
		node->next = symTab->hash_table[index]; //sets the new node as the head of the hash table
	}else {
		debug("null pointer at index: %i next = NULL",index);
		node->next = NULL;
	}		
    node->hash = hashVal;
    /* create new symbol struct to store the nameCopy and addr of the symbol */
    symbol_t symbol;
    symbol.name = nameCopy;
    symbol.addr = addr;
    node->symbol = symbol; //make the symbol struct into the node symbol member
    symTab->hash_table[index] = node;
    while(symTab->addr_table[addr] != NULL)
        addr++;
    symTab->addr_table[addr] = nameCopy;
}

char* symbol_find_by_addr (sym_table_t* symTab, int addr) {
    /* takes the index of the addr in the sym table
		and returns the name at that index (has the posobility to be Null) */
  return symTab->addr_table[addr];
}

void symbol_iterate (sym_table_t* symTab, iterate_fnc_t fnc, void* data) {
    for(int i=0; i<symTab->size;i++) {
        debug("currently at index: %i",i);
        if(symTab->hash_table[i] != NULL) {
            node_t* current = symTab->hash_table[i];
            while(current != NULL) {
                (*fnc)(&current->symbol, data);
                current = current->next;
            }
        }
    }
}

struct node* symbol_search (sym_table_t* symTab, const char* name, int* ptrToHash, int* ptrToIndex) {
  /** Finds the hash of the symbol as well as the index for that symbol 
	  corrosponding to the hash value and table size */
  *ptrToHash = symbol_hash(name);
  *ptrToIndex = *ptrToHash % symTab->size;
  debug("Symbol to search %s, hash value of: %i, index is: %i",name,*ptrToHash,*ptrToIndex);
  /** begin iterating through nodes at the current hash table index, search for hash value matches */
  node_t* current = symTab->hash_table[*ptrToIndex];
  while(current != NULL) {
	  if(*ptrToHash == current->hash) {
		  /** Hash values match now do a case insensitive string comparison between the symbols */
		  debug("Found match In: %i == table: %i",*ptrToHash,current->hash);
		  if(strcasecmp(name, current->symbol.name)) {
			  debug("'%s' equals '%s'... Break out of list traverse",name, current->symbol.name);
			  return current;
		  }  
	  }
	  current = current->next;
  }
  return NULL;
}

int symbol_add (sym_table_t* symTab, const char* name, int addr) {
	/** Test to see if the symbol being added already exists using symbol_search */
	 int index; int hash;
	if(symbol_search(symTab, name, &hash, &index) != NULL) {
		debug("-- ERROR: duplicate symbol --");
		return 0;
	}
	symbol_add_unique(symTab, name, addr);
	debug("Symbol added with symbol_add_unique function");
  return 1;
}


symbol_t* symbol_find_by_name (sym_table_t* symTab, const char* name) {
	symbol_t* symbol;
	int index;
	int hash;
	if(symbol_search(symTab, name, &hash, &index) == NULL)
		return NULL;
	node_t* current = symTab->hash_table[index];
	while(current != NULL) {
		if(hash == current->hash)
			symbol = &current->symbol;
		current = current->next;
		}
  return symbol;
}

void symbol_reset(sym_table_t* symTab) {
	/** Free all nodes in the hash table */
	for(int i=0; i<symTab->size;i++) {
        debug("currently at index: %i",i);
        if(symTab->hash_table[i] != NULL) {
            node_t* current = symTab->hash_table[i];
            while(current != NULL) {
				debug("Non-null node at index: %i", i);
                node_t* placeHolder = current->next;
                free(current->symbol.name);
				free(current);
                current = placeHolder;
            }
        }
    }
	free(symTab->hash_table);
	free(symTab->addr_table);
	symTab->addr_table = calloc(LC3_MEMORY_SIZE, sizeof(char*));
	symTab->hash_table= calloc(symTab->size, sizeof(node_t*));
}

void symbol_term (sym_table_t* symTab) {
	symbol_reset(symTab);
	free(symTab->hash_table);
	free(symTab->addr_table);
	free(symTab);
}
