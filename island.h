#pragma once
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>

class Node {
private:
    int island; // used to store island number
    Node* next; // used to create additional nodes

public:
    //Constructor to initialize an island list node
    Node(int val) {
        island = val;
        next = NULL;
    }
    // constructor to initialize an island list node and the next node
    Node(int val, Node* nxt) {
        island = val;
        next = nxt;
    }
    // returns island value
    int getIsland() {
        return island ;
    }
    // returns our next node
    Node* getNext() {
        return next;
    }
    // sets island value
    void setIsland(int val) {
        island = val;
    }
    // sets next node
    void setNext(Node* nxt) {
        next = nxt;
    }

};

class MyList {
private:
    Node* head; //used to manipulate our adjacency lists

public:

    // constructor to initialize the head of the list
    MyList() {
        head = NULL;
    }
   
    // insert function that checks for existing islands and adds to adjacency list
    void insert(int val) {

        Node* temp = new Node(val, NULL);
        Node* curr = head;
        Node* prev = NULL;

        while (curr != NULL) {
            if (curr->getIsland() == val) {
                printf("Ferry ride already added!\n");
                return;
            }
            prev = curr;
            curr = curr->getNext();
        }
        if (prev == NULL) {
            head = temp;
        }
        else {
            prev->setNext(temp);
        }

    }
    // deletes the island adjacency list
    void deleteLists()
    {
        Node* temp = head;
        Node* next = NULL;
        while (temp != NULL)
        {
            next = temp->getNext();
            delete (temp);
            temp = next;
        }
        head = NULL; 
    }
    // remove node from adjacency list
    void remove(int v1) {

    
        Node* curr = head;
        Node* prev = NULL;
        while (curr != NULL && curr->getIsland() != v1) {
            prev = curr;
            curr = curr->getNext();
        }
        if (curr == NULL) {
            printf("Ferry ride does not exist\n");
            return;
        }
        //if node to delete is at head of list
        if (prev == NULL) {
            prev = curr->getNext();
            delete curr;
            head = prev;
        }

        else {
            prev->setNext(curr->getNext());
            delete curr;
        }
    }
    // returns the length of the list
    int getListLength() 
    {
        int total = 0;
        Node* tmp = head;

        while (tmp != NULL) {
            total++;
            tmp = tmp->getNext();
        }

        return total;
    }
    // sets the head of the list
    void setHead(Node *hd)
    {
        head = hd; 
    }
    // returns the head of the list
    Node *getHead()
    {
        if (head == NULL)
        {
            return NULL; 
        }
        return head; 
    }

    int getNthElem(int n) {
        int curr = 0;
        Node* temp = head;
        while (temp != NULL && curr != n) {
            curr++;
            temp = temp->getNext();
        }

        if (temp == NULL)
            return -999;

        else {
            return temp->getIsland();
        }
    }

    void printList() {
        Node* temp = head;
        while (temp != NULL) {
            printf("%d  ", temp->getIsland());
            temp = temp->getNext();
        }
       
    }
    void printListOrder() {
        Node* temp = head;
        while (temp != NULL) {
            
            printf("%d", temp->getIsland());

            if (temp->getNext() != NULL)
            {
                printf(" - "); 
            }
            temp = temp->getNext();
        }

    }

};
class file_Node
{
private:
    char* fileName;  // used to store file name
    file_Node* next; 

public: 
    //constructor to initialize file node
    file_Node(char* file)
    {
        fileName = file; 
        next = NULL; 
    }
    //returns the file name
    char* getFile()
    {
        return fileName; 
    }
    // sets the file name
    void setNextFile(file_Node* file)
    {
        next = file; 
    }
    // return next file node
    file_Node* getNextFile()
    {
        return next; 
    }
};

class allFiles
{
private:
    file_Node* head; // used to manipulate file list

public: 
    //constructor to initalize the list
    allFiles()
    {
        head = NULL;
    }
    // adds file to fileList
    void addFile(char* file)
    {
        file_Node* newNode = new file_Node(file); 

        if (head == NULL)
        {
            head = newNode; 
            return; 
        }

        file_Node* temp = head; 

        while (temp->getNextFile() != NULL)
        {
            temp = temp->getNextFile(); 
        }
        temp->setNextFile(newNode);
    }
    
    // delete file from file list
    void deleteFile(char* file)
    {
        file_Node* curr = head;
        file_Node* prev = NULL;
        while (curr != NULL && curr->getFile() != file) {
            prev = curr;
            curr = curr->getNextFile();
        }
        if (curr == NULL) {
            printf("File does not exist\n");
            return;
        }
        //if node to delete is at head of list
        if (prev == NULL) {
            prev = curr->getNextFile();
            delete curr;
            head = prev;
        }

        else {
            prev->setNextFile(curr->getNextFile());
            delete curr;
        }
    }
    // checks if file is already in use
    bool isFileOpen(char* file)
    {

        if (head == NULL)
        {
            return false; 
        }

        file_Node* temp = head;

        while (temp != NULL)
        {
            if (strcmp(temp->getFile(), file) == 0) {
                return true;
            }
            temp = temp->getNextFile(); 
        }
        return false; 
    }
    
};

class myQueue : public MyList
{

public: 
    // use myList constructor
    myQueue() : MyList ()
    {
    }
    // add island to the end of the queue list
    void enqueue(int val)
    {
        Node* newNode = new Node(val); 
        Node* temp = getHead(); 

        if (temp == NULL)
        {
            setHead(newNode); 
            return; 
        }
        
        while (temp->getNext() != NULL)
        {
            temp = temp->getNext(); 
        }
        temp->setNext(newNode); 
    }

    // delete island from the queue
    void dequeue()
    {
        Node* temp = getHead(); 
        if (temp == NULL)
        {
            printf("List is already empty.");    
        }
        else
        {
            setHead(temp->getNext()); 
        }
    }

    // returns the next island in the queue
    int peak()
    {
        Node* temp = getHead(); 
        if (temp == NULL)
        {
            return -1;
        }
        else
        {
            return temp->getIsland(); 
        }
    }
};

class myStack : public MyList
{
public:
    // use myList constructor
    myStack(): MyList()
    {

    }
    // add island onto the stack
    void push(int val)
    {
        Node* newNode = new Node(val); 
        Node* temp = getHead(); 

        if (temp == NULL)
        {
            setHead(newNode); 
            return;
        }

        newNode->setNext(temp); 
        setHead(newNode); 
    }
    // remove the island at the top of the stack
    void pop()
    {
        Node* temp = getHead(); 
        if (temp == NULL)
        {
            printf("List is already empty"); 
        }
        else
        {
            setHead(temp->getNext()); 
        }
    }
    // returns the island at the top of the stack
    int top()
    {
        Node* temp = getHead(); 
        if (temp == NULL)
        {
            return -1; 
        }
        else
        {
            return temp->getIsland(); 
        }
    }
};

class Island {
private:
    MyList* adjacent; // used to access adjacency lists
    int visited; // keeps track of visited islands

public:
    // constructor to initalize adjacency lists & visited status
    Island() {
        adjacent = new MyList;
        visited = -1;
    }
    // returns our adjacency list
    MyList* getAdjacent() {
        return adjacent;
    }
    // returns the visiting status of island
    int getVisited() {
        return visited;
    }
    // sets the visiting status to corresponding island
    void setVisited(int status) {
        visited = status;
    }

};

