/*----------------------------------------------
 * Project 6:
 * Class: CS 211, Fall 2020
 * By Nicholas Rachfal
 * ---------------------------------------------*/
#include "island.h"

class ArchipelagoExpedition
{
private:
    //  Data Members for the Archipelago Network 
    Island* expedition;
    int numIslands;

    // file data member 
    allFiles *fileList; 
public:

    // constructor to initialize the Data Members for your expedition
    ArchipelagoExpedition()
    {
        numIslands = 10;
        expedition = new Island[numIslands]();
        fileList = new allFiles(); 

    }
    
   

    bool bfs(int b, myQueue* islandQueue)
    {
        // while the island que is not empty
        while (islandQueue->getListLength() != 0)
        {
            // set a to be the island at the front of the island que
            int a = islandQueue->peak(); 

            // remove island at the front of the island que
            islandQueue->dequeue(); 

            // get the head of the current island adjecency list
            Node* temp = expedition[a-1].getAdjacent()->getHead(); 

            //  loop through the islands "temp" that can be reached from a in one ferry ride
            for (;temp != NULL; temp = temp->getNext())
            {
                // if island is unvisited 
                if (expedition[temp->getIsland()-1].getVisited() == -1)
                {
                    // set island to visisted
                    expedition[temp->getIsland()-1].setVisited(a); 

                    // if we have reached the island we are attempting to reach, return true
                    if (temp->getIsland() == b)
                    {
                        return true; 
                    }
                    // add the island to the island que
                    islandQueue->enqueue(temp->getIsland()); 
                }
            }
        }
        //otherwise we can not reach the island
        return false; 
    }

    MyList* breadthFirstSeach(int x, int y)
    {

        // set all islands to unvisited
        for (int i = 0; i < numIslands; i++)
        {
            expedition[i].setVisited(-1); 
        }
        // initialize island que
        myQueue* queueIsland = new myQueue(); 
        
        // add starting island to the end of the que
        queueIsland->enqueue(x); 

        // if the island cannot be reached, notify user
        if (bfs(y, queueIsland) == false)
        {
            printf("You can NOT get from island %d to island %d\n", x, y);
            queueIsland->deleteLists();
            return queueIsland; 
        } 
        // otherwise the island can be reached, notify user
        else
        {
            printf("You can get from island %d to island %d\n", x, y);
            
            // set the route to an empty list
            myStack* route = new myStack(); 
            
            // set the current island position to the island we want to reach
            int currIslandPosition = y; 

            // add the current island position to the front of the route
            route->push(y); 

            do
            {
                // set current island position to the previous island node value
                currIslandPosition = expedition[currIslandPosition-1].getVisited(); 

                // add current island position to the front of the route
                route->push(currIslandPosition); 

                // repeat until we get back to the original island 
            } while (currIslandPosition != x); 

            return route; 
        }

    }
       // not used in this project
    void depthFirstSearchHelper(int x, int y) {
        for (int i = 0; i < numIslands; i++) {
            expedition[i].setVisited(false);
        }

        if (dfs(x, y) == true)
            printf("You can get from island %d to island %d\n", x, y);
        else
            printf("You can NOT get from island %d to island %d\n", x, y);
    }

    // not used in this project
    bool dfs(int x, int y) {
        for (int i = 0; i < expedition[x - 1].getAdjacent()->getListLength(); i++) {
            int island = expedition[x - 1].getAdjacent()->getNthElem(i);
            if (island == y)
                return true;

            if (expedition[island - 1].getVisited() == false) {
                expedition[x - 1].setVisited(true);

                if (dfs(island, y) == true)
                    return true;
            }
        }
        return false;
    }

    void processCommandLoop(FILE* inFile)
    {
        char  buffer[300];
        char* input;

        input = fgets(buffer, 300, inFile);   // get a line of input

        while (input != NULL)
        {
            // process each line of input using the strtok functions 
            char* command;
            command = strtok(input, " \r\n\t");

            printf("*%s*\n", command);

            if (command == NULL)
                printf("Blank Line\n");

            else if (strcmp(command, "q") == 0)
                exit(1);

            else if (strcmp(command, "?") == 0)
                showCommands();

            else if (strcmp(command, "t") == 0)
                doTravel();

            else if (strcmp(command, "s") == 0)
                doShortestPath();

            else if (strcmp(command, "r") == 0)
                doResize();

            else if (strcmp(command, "i") == 0)
                doInsert();

            else if (strcmp(command, "d") == 0)
                doDelete();

            else if (strcmp(command, "l") == 0)
                doList();

            else if (strcmp(command, "f") == 0)
                doFile();

            else if (strcmp(command, "#") == 0)
                ;

            else
                printf("Command is not known: %s\n", command);

            input = fgets(buffer, 300, inFile);   // get the next line of input

        }
    }

    void showCommands()
    {
        printf("The commands for this project are:\n");
        printf("  q \n");
        printf("  ? \n");
        printf("  # \n");
        printf("  s <int1> <int2> \n");
        printf("  t <int1> <int2> \n");
        printf("  r <int> \n");
        printf("  i <int1> <int2> \n");
        printf("  d <int1> <int2> \n");
        printf("  l \n");
        printf("  f <filename> \n");
    }

    void doShortestPath() 
    {
        int val1 = 0;
        int val2 = 0;

        // get an integer value from the input
        char* next = strtok(NULL, " \r\n\t");


        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val1 = atoi(next);
        if (val1 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok(NULL, " \r\n\t");
        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val2 = atoi(next);
        if (val2 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }

        if (val1 > numIslands || val2 > numIslands)
        {
            printf("Invalid value for island\n"); 
            return; 
        }


        printf("Performing the shortest path Command from %d to %d\n",
            val1, val2); 
        
        // call search algorithm for specified islands val1 and val2
        MyList* route = breadthFirstSeach(val1, val2); 


        //  if a the list is not empty then a path was found
        if (route->getListLength() != 0)
        {
            printf("shortest path from %d to %d: ", val1, val2); 
            route->printListOrder(); 
            printf("\n"); 
        }
       

    }

    // not used in this project
    void doTravel()
    {
        int val1 = 0;
        int val2 = 0;

        // get an integer value from the input
        char* next = strtok(NULL, " \r\n\t");


        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val1 = atoi(next);
        if (val1 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok(NULL, " \r\n\t");
        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val2 = atoi(next);
        if (val2 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }


        printf("Performing the Travel Command from %d to %d\n",
            val1, val2);
        depthFirstSearchHelper(val1, val2);
    }

    void doResize()
    {
        int val1 = 0;
        // get an integer value from the input
        char* next = strtok(NULL, " \r\n\t");
        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val1 = atoi(next);

        printf("Performing the Resize Command with %d\n", val1);
 
        // loop through our island array, get the adjacency lists, and delete them
        for (int i = 0; i < numIslands; i++)
        {
            expedition[i].getAdjacent()->deleteLists(); 
        }
        // delete the island array itself
        delete expedition;
        
        // update island size
        numIslands = val1; 

        // allocate memory the new size
        expedition = new Island[numIslands]; 
    }

    void doInsert()
    {
        int val1 = 0;
        int val2 = 0;

        // get an integer value from the input
        char* next = strtok(NULL, " \r\n\t");
        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val1 = atoi(next);
        if (val1 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok(NULL, " \r\n\t");
        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val2 = atoi(next);
        if (val2 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }

        // input validation: make sure the islands are in bounnds of our island array
        if (val1 <= numIslands && val2 <= numIslands) {
            printf("Performing the Insert Command for %d\n", val1);
            expedition[val1 - 1].getAdjacent()->insert(val2);
        }
        else
            printf("Invalid value for island\n");
    }

    void doDelete()
    {
        int val1 = 0;
        int val2 = 0;

        // get an integer value from the input
        char* next = strtok(NULL, " \r\n\t");
        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val1 = atoi(next);
        if (val1 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }

        // get another integer value from the input
        next = strtok(NULL, " \r\n\t");
        if (next == NULL)
        {
            printf("Integer value expected\n");
            return;
        }
        val2 = atoi(next);
        if (val2 == 0 && strcmp(next, "0") != 0)
        {
            printf("Integer value expected\n");
            return;
        }

        // input validation: make sure the islands are in bounnds of our island array
        if (val1 > numIslands || val2 > numIslands)
        {
            printf("Invalid value for island\n"); 
            return;
        }
        // if the input is valid, remove the node from the island's adjacency list
        else
        {

            printf("Performing the Delete Command for %d\n", val1);
            expedition[val1 - 1].getAdjacent()->remove(val2);
        }
    }

    void doList()
    {
        // print the list of all islands

        printf("Displaying the adjacency list:\n");
        for (int i = 0; i < numIslands; i++) {
            printf("%d -->  ", i + 1);
            expedition[i].getAdjacent()->printList();
            printf("\n");
        }
    }

    void doFile()
    {
        // get a filename from the input
        char* fname = strtok(NULL, " \r\n\t");
        if (fname == NULL)
        {
            printf("Filename expected\n");
            return;
        }

        printf("Performing the File command with file: %s\n", fname);

        // next steps:  (if any step fails: print an error message and return ) 
        //  1. verify the file name is not currently in use
        //  2. open the file using fopen creating a new instance of FILE*
        //  add file to dynamic array
        //  3. recursively call processCommandLoop() with this new instance of FILE* as the parameter
        //  4. close the file when processCommandLoop() returns
        //  5. Remove the file name from the array
        if (fileList->isFileOpen(fname) == true)
        {
            printf("File is already in use\n"); 
            return;
        }

        FILE* file = fopen(fname, "r");

        fileList->addFile(fname); 
        
        processCommandLoop(file);
        fclose(file);

        fileList->deleteFile(fname); 

       
    }
};

int main(int argc, char** argv)
{
    // set up the variable inFile to read from standard input
    FILE* inFile = stdin;

    // set up the data needed for the island adjcency list
    ArchipelagoExpedition islandData;

    // call the method that reads and parses the input
    islandData.showCommands();
    printf("\nEnter commands at blank line\n");
    printf("    (No prompts are given because of f command)\n");
    islandData.processCommandLoop(inFile);

    printf("Goodbye\n");

    return 1;
}
