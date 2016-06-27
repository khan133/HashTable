#include "HashTableVoid.h"
#include <stdio.h>
#include <stdlib.h>
// Obtain the hash code of a key
int HashTableVoid::hash(const char * key)
{
  int sum = 0;
  int i = 0;
  while (i < strlen(key)) {
  sum +=  key[i];
  i++; 
  }
  return sum % TableSize; 
}

// Constructor for hash table. Initializes hash table
HashTableVoid::HashTableVoid()
{
_buckets = new HashTableVoidEntry*[TableSize];
int i = 0;
while (i < TableSize) {
	_buckets[i] = NULL; 
	i++; 
}
return; 
}

bool HashTableVoid::insertItem( const char * key, void * data)
{
  int num = hash(key);
  HashTableVoidEntry * curr = _buckets[num];
  while (curr != NULL) {
	if (strcmp(curr -> _key, key) == 0) 
	{
		curr -> _data = data;
		return true; 
	}
	curr = curr -> _next;
  }

  HashTableVoidEntry *temp = new HashTableVoidEntry();
  temp -> _key = strdup(key);
  temp -> _data = data;
  temp -> _next = _buckets[num];
  _buckets[num] = temp;
  return false; 
}

// Find a key in the dictionary and place in "data" the corresponding record
// Returns false if key is does not exist
bool HashTableVoid::find( const char * key, void ** data)
{
  int num = hash(key);
  HashTableVoidEntry * curr = _buckets[num];
  int count = 0; 
  while (curr != NULL) {
  	if (strcmp(curr -> _key, key) == 0) {
		*data = curr -> _data; 
		return true; 
	}
	else 
	count++;
  curr = curr -> _next; 
  }
  if (count != 0)
  return false; 
   
}

// Removes an element in the hash table. Return false if key does not exist.
bool HashTableVoid::removeElement(const char * key)
{
  int num = hash(key);
  int count = 0;
  HashTableVoidEntry * curr = _buckets[num];
  HashTableVoidEntry * temp = curr; 
  while (curr != NULL) {
  	if (strcmp(key, curr -> _key) == 0) {
		if (count == 0) {
			_buckets[num] = NULL; 
			return true; 
		}
		if (count != 0) {
			temp -> _next = curr -> _next; 
			return true; 
		}
	}
	temp = curr; 
	curr = curr -> _next;
	count++; 
  }
  return false; 
}

