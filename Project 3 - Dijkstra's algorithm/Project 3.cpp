// Abigail McIntyre
// due 10/29/2021
// Dijkstra's algorithm

// how it works:
// Start vertex A
// Distance to A from A = 0
// Distance to all other vertices from A are unknown, therefore they are infinity 

// start by initializing all the nodes with the distances from the source node - initially infinity
// initialize the distance of the source node to zero because the distance to itself is zero

// 1.) get the nearest unvisited node
// 2.) mark the node as visited
// 3.) update adjacent node distance
// 4.) keep track of parent node


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

// =================================================================================================================================================================

void dijkstra(int startNode, int cost[100][100], int numCities, string cityNames[100]);
void displayDistances(int distance[], int parent[], int startNode, int numCities, string cityNames[100]);
int getMinimum(int distance[], bool visited[], int numCities);
void displayMatrix(int numCities, int cost[100][100], string cityNames[100]);

// =================================================================================================================================================================

int main()
{
    ifstream inFile;                                        // the file containing the adjacency matrix and city names
    string filePath;                                        // a string holding the file path to open
    string cityNames[100];                                  // an array of the city names in the file
    string cityName;                                        // used to hold each city name as it's read from the file and stored into the array
    string startName;                                       // the city name input from the user to use to find the shortest distances to
    int numCities;                                          // the number of cities in the matrix
    int startNode;                                          // the number for the starting node
    int lines = 0;                                          // to scan the number of lines in the file
    int cost[100][100];                                     // the cost matrix that holds the distances to and from each node

    // enter the node to start with
    cout << "Enter start node: ";
    cin >> startName;

    // get the file path from the user
    do
    {
        cout << "Enter file path: ";
        getline(cin, filePath);
        inFile.open(filePath);
    } while (!inFile.good());

    // if the file is ok
    if (inFile.good())
    {
        string token;

        // get the number of lines in the file
        while (!inFile.eof())
        {
            getline(inFile, token);
            lines++;
        }
    }

    // close the file to reset it to the top
    inFile.close();

    // the number of cities in the file
    numCities = (int)(ceil(lines / 2)) + 1;

    // open the file again
    inFile.open(filePath);

    // read the city names into an array and then initialize the starting node
    for (int r = 0; r < numCities; r++)
    {
        getline(inFile, cityName);
        cityNames[r] = cityName;

        if (cityNames[r] == startName)
            startNode = r;
    }

    // read the adjacency matrix into the cost array
    for (int i = 0; i < numCities; i++)
    {
        for (int j = i + 1; j < numCities; j++)
        {
            inFile >> cost[i][j];
            cost[j][i] = cost[i][j];                    // complete the adjacency matrix
        }
    }

    // close the file
    inFile.close();

    // display the adjacency matrix
    displayMatrix(numCities, cost, cityNames);

    // set all zeros to infinity
    for (int i = 0; i < numCities; i++)
    {
        for (int j = 0; j < numCities; j++)
        {
            if (cost[i][j] == 0)
                cost[i][j] = 999;
        }
    }

    // set the diagonal to 0
    for (int i = 0; i < numCities; i++)
    {
        cost[i][i] = 0;
    }

    // run the algorithm
    dijkstra(startNode, cost, numCities, cityNames);
}

// =================================================================================================================================================================

void displayMatrix(int numCities, int cost[100][100], string cityNames[100])
{
    cout << endl << endl << "\t\tAdjacency Matrix" << endl;

    // set the diagonal to 0
    for (int i = 0; i < numCities; i++)
    {
        cost[i][i] = 0;
    }

    // output the  names at the top
    for (int i = 0; i < numCities; i++)
    {
        cout << "\t" << setw(6) << cityNames[i];
    }

    cout << endl << endl;

    //Print the city name followed by the distances
    for (int i = 0; i < numCities; i++)
    {
        cout << setw(6) << cityNames[i];
        for (int j = 0; j < numCities; j++)
        {
            cout << setw(8) << cost[i][j];
        }
        cout << endl;
    }
}

// =================================================================================================================================================================

void dijkstra(int startNode, int cost[100][100], int numCities, string cityNames[100])
{
    int parent[100];                                                    // to keep track of the parent node - the index will represent the key for the vertex and the value will represent the parent
    int distance[100];                                                  // keeps track of the distance from the starting vertex to every other vertex in the graph
    bool visited[100] = { 0 };                                          // keeps track of whether a node has been visited or not
    int minNode;                                                        // the minimum distance

    // fill the distance array with a very large number
    for (int i = 0; i < numCities; i++)
        distance[i] = 9999;

    // set the distance from the start node to itself to 0
    distance[startNode] = 0;

    // set the parent of the start node to -1
    parent[startNode] = -1;

    // for all the cities except for 
    for (int i = 0; i < numCities - 1; i++)
    {
        // get the minimum node
        minNode = getMinimum(distance, visited, numCities);

        // mark it as visited
        visited[minNode] = true;

        for (int j = 0; j < numCities; j++)
        {
            // if the node hasn't been visited, the distance of the minimum node + the cost of getting there is less than the distance being checked, and the nodes are actually connected
            if (!visited[j] && (distance[minNode] + cost[minNode][j]) < distance[j] && cost[minNode][j] != 999)
            {
                // the index of the parent node is the key and the value is the parent node
                parent[j] = minNode;

                // set the distance of the minimum node connected to it to the shortest distance
                distance[j] = distance[minNode] + cost[minNode][j];
            }
        }
    }

    // display the minimum and shortest path stuff
    displayDistances(distance, parent, startNode, numCities, cityNames);
}

// =================================================================================================================================================================

void displayDistances(int distance[], int parent[], int startNode, int numCities, string cityNames[100])
{
    for (int i = 0; i < numCities; i++)
    {
        if (i != startNode)         // it won't display the distance to the start node
        {
            cout << endl << endl << "*********************************************************************" << endl << endl;

            cout << "The Distance from " << cityNames[startNode] << " to " << cityNames[i] << " is: " << distance[i] << endl << endl;

            int temp = parent[i];
            cout << cityNames[i] << " <-- ";

            while (temp != -1)
            {
                cout << cityNames[temp] << " <-- ";
                temp = parent[temp];
            }

        }

    }
    cout << endl << endl << "*********************************************************************" << endl << endl;
}

// =================================================================================================================================================================

int getMinimum(int distance[], bool visited[], int numCities)
{
    int minNode = 0;
    int minValue = 9999;

    // go through all the vertices
    for (int i = 0; i < numCities; i++)
    {
        // if the distance is less than the current minimum distance and the vertex hasn't been visited
        if (distance[i] < minValue && !visited[i])
        {
            minValue = distance[i];             // the minimum value is now the distance to that node
            minNode = i;                        // the minimum node is now that node
        }
    }
    return minNode;                             // return the minimum node
}

// =================================================================================================================================================================





