# Algorithms and data structures 2 - Lab 2

Write a program to implement the data structure of the hash table, which will allow you to very quickly search for data in a set of structures of your version.
1. Implement a function to generate a random large number that will be a unique key identifier of the data in the hash table.
2. Implement a hash table by the chain method:
    1. Create a Data structure to store different types of data according to the variant, it will be used as values for the hash table. 
       Implement random data generation for structure fields in an empty Data () constructor.
       The structure of the iPhone has the following fields: color, model number, the presence of a charger included. 
       Create a store where you can quickly find an iPhone
    2. Create a HashNode structure to store the key and value
    3. Create a LinkedList structure with support for adding elements
    4. Create a HashTable structure that will contain an array of connected bucketsArray lists of static size M = 10000 and implement the main functions in it.
       All functions must work according to O (1):
        - hash (key) finding the hash function from the key
        - insert (key, value) adding value under the corresponding key (replacement in case of existence of a key)
        - find (key) finding the value under the corresponding key, the function returns a pointer to the found element or NULL
        - erase (key) to delete the value under the corresponding key
        - size () find the number of elements in the hash table
3. Optimize the hash table by adding a dynamic resize of the bucketsArray array depending on loadFactor (maximum possible table load):
    1. Set the initial size of the array bucketsArray small, for example m = 8, 
       if you exceed the value of loadFactor dynamically increase the size (for example 2 times)
    2. Temporarily select the initial value of loadFactor to be 8.5
4. Perform the test using the testHashTable () function. Select the optimal loadFactor value. 
   Check the correctness and speed of work, comparing with the finished library solution STL unordered_map.
   
Optional extra tasks:
1. Implement another hash table where the string type is used as keys
2. Implement another hash table using the open addressing method
