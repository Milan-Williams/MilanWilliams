/* Milan Williams
 Course project 
 Due Date: Dec 8th 2024
 Estimated completion time: 5 days 
 */



// Included for the use of input and also output 
#include <iostream>
// Included for the use of vector data structures 
#include <vector>
// Included this so I could string data types 
#include <string>
// Included this to add queue 
#include <queue>
// I used this so I could use INT_MAX which is useful for infinity 
#include <climits>

using namespace std;
// The matrix i used can represent things like the distance as well as cost or even adjacency relationships  
// Function to print a matrix with a label
// Also the matrix is a 2D vector which will print and essentially label what that matrix will be  
void printMatrix(const vector<vector<int> > &matrix, const string &label) {
    // This is what will print the label of the matrix 
    cout << label << ":\n";
    // This loop is what will loop through each row of the matrix 
    for (size_t i = 0; i < matrix.size(); i++) {
     // This is what will loop through each element of the row    
        for (size_t j = 0; j < matrix[i].size(); j++) {
            // And this is what will essentially print out the value 
            cout << matrix[i][j] << "\t";
        }
        // also included a start to a new line after each row is printed 
        cout << endl;
    }
}

// Function to perform DFS to find all paths from src to dest
// The purpose of this function is really to find all of the possible paths between both of the nodes 
// So src is essentially the current node that is being visited 
// and dest is what the target destination node 
// graph is simply just the adjacency matrix 
// visited just keeps track if a node has been visited 
// currentPath is what is going to store the current path 
// and allPaths is going to store the valid paths that are found 
void dfs(int src, int dest, const vector<vector<int> > &graph, vector<bool> &visited,
         vector<int> &currentPath, vector<vector<int> > &allPaths) {
    // This will mark the current node that it is visited 
    visited[src] = true;
    // this will be what adds the current node to what the current path is 
    currentPath.push_back(src);
// this is essentially the base case that is if the current node is the destination 
    if (src == dest) {
      // this is just going to save the current path to allPaths   
        allPaths.push_back(currentPath);
    } else {
        // This is my Recursive case, and essentially it's just going to explore all the neighboring nodes to the current node  
        for (size_t i = 0; i < graph[src].size(); i++) {
            // this is what will check if there is a direct connection 
            if (graph[src][i] && !visited[i]) {
                // and this right here will recurse from the neighbor 
                dfs(i, dest, graph, visited, currentPath, allPaths);
            }
        }
    }
    // . This is what will mark the current node as "unvisited" 
    visited[src] = false;
    currentPath.pop_back();
}
//This is my function that i used to try and find the "shortest path"
// Function to perform Dijkstra's algorithm to find the shortest path in a matrix (using distance)
//so graph is basically the adjacency matrix that is representing the distance
// and src is going to start the node from the shortest path 
// and in return a vector with the shortest distances 
vector<int> dijkstra(const vector<vector<int> > &graph, int src) {
    // This is what will get the number of nodes 
    int n = graph.size();
    // Then this will initialize the distance 
    vector<int> dist(n, INT_MAX);
    // This id the distance from the source back to itself  
    vector<bool> visited(n, false);
    // and finally this is what will track if the node has been essentially processed 
    dist[src] = 0;
// This is what will essentially use the algorithm and it's for n-1 
    for (int count = 0; count < n - 1; count++) {
        // used this for the variable to store whatever the next node is with the shortest distance 
        int u = -1;
        // Find the unvisited node with the smallest distance
        for (int i = 0; i < n; i++) {
            if (!visited[i] && (u == -1 || dist[i] < dist[u])) {
                // This is what will update my u with my index 
                u = i;
            }
        }
        // Here will mark the node that is selected as "visited"
        visited[u] = true;

        // Update distances for adjacent nodes
        // or as i like to call them neighboring nodes
        for (int v = 0; v < n; v++) {
            // these are the conditions so there must essentially be an edge or in other words a non zero value 
            if (graph[u][v] && !visited[v] && dist[u] != INT_MAX &&
                dist[u] + graph[u][v] < dist[v]) {
                // this is what will update the distance only if a shorter path is actually found  
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    // and this is what is going to return my vector with the shortest distance(s) 
    return dist;
}

// Function to perform Dijkstra's algorithm to find the lowest cost path (using cost)
// here I use graph which is adjacency matrix that is represent the cost essentially between the nodes 
// src here is what the starting node for all the calculations 
// and i will return a vector with the minimum cost 
vector<int> dijkstraCost(const vector<vector<int> > &graph, int src) {
    // this will get the number of nodes in the graph
    int n = graph.size();
    // this is what will initialize the cost 
    vector<int> cost(n, INT_MAX);
    // this is what the amount or cost to reach and my source is zero 
    vector<bool> visited(n, false); // will track if the node has in fact been processed  
    cost[src] = 0;
// this is what is going to perform my algorithm and all the n-1 iterations 
    for (int count = 0; count < n - 1; count++) {
        // this is my variable that is going to store node that has the smallest cost  
        int u = -1;
        // Find the unvisited node with the smallest cost
        for (int i = 0; i < n; i++) {
            if (!visited[i] && (u == -1 || cost[i] < cost[u])) {
                // this again will update u with my index 
                u = i;
            }
        }
// and this is what will show the node essentially as visited already 
        visited[u] = true;

        // Update costs for adjacent nodes
        for (int v = 0; v < n; v++) {
            // these are what the conditions are like before must be and edge non zero 
            if (graph[u][v] && !visited[v] && cost[u] != INT_MAX &&
                cost[u] + graph[u][v] < cost[v]) {
                // this is what will update the cost only if there is a cheaper cost that is actually found 
                cost[v] = cost[u] + graph[u][v];
            }
        }
    }
// and finally a vector will be returned that has the least cost 
    return cost;
}

// Main function
int main() {
    // This is my main function in other words this is my entry point that will start my program 
    // It  will set up the adjacency matrixs
    // this is what i used to define 
    vector<string> cities;
    // this is what added the city of Riverside 
    cities.push_back("Riverside");
    // this is what added the city of Perris 
    cities.push_back("Perris");
    // This is what added the city of Moreno Valley 
    cities.push_back("Moreno Valley");
    // and this is what added the city of Hemet 
    cities.push_back("Hemet");
    // All the cities will be added to a list 

    // Distance matrix with distances between cities
    // i chose to go with a 4 by 4 matrix for the 4 cities 
    vector<vector<int> > distanceMatrix(4, vector<int>(4, 0));
    // Distance from riverside is back to riverside is 0
    // the distance from the city to riverside to the city of Perris is 24
    // The distance from the city of riverside to the city of Moreno valley is 16 
    // The distance from the city of riverside to the city of Hemet is 33
    distanceMatrix[0][0] = 0;  distanceMatrix[0][1] = 24; distanceMatrix[0][2] = 16; distanceMatrix[0][3] = 33;
    // the distance from the city of Perris to the city of Riverside is 24
    // the distance from the city of perris to the city of perris or itself is 0
    // the distance from the city of Perris to the city of Moreno Valley is 18
    // and the distance from the city of Perris to the city of Hemet is 30
    distanceMatrix[1][0] = 24; distanceMatrix[1][1] = 0;  distanceMatrix[1][2] = 18; distanceMatrix[1][3] = 30;
    // the distance from the city of Moreno Valley to the city of Riverside is 16
    // the distance from the city of Moreno Valley to the city of Perris is 18
    // the distance from the city of Moreno Valley to the city of Moreno Valley is 0
    // and the distance from the city of moreno valley to the city of Hemet is 26
    distanceMatrix[2][0] = 16; distanceMatrix[2][1] = 18; distanceMatrix[2][2] = 0;  distanceMatrix[2][3] = 26;
    // the distance from the city of Hemet to the city of Riverside is 33
    // the distance from the city of Hemet to the city of Perris is 30
    // the distance from the city of Hemet to the city of Moreno alley is 26 
    // and last but not least the distance from the city of Hemet to itslef is 0
    distanceMatrix[3][0] = 33; distanceMatrix[3][1] = 30; distanceMatrix[3][2] = 26; distanceMatrix[3][3] = 0;

    // Cost matrix with travel costs between cities (can be arbitrary for this example)
    vector<vector<int> > costMatrix(4, vector<int>(4, 0));
    // the cost of going from the city of Riverside back to the city of Riverside is 0
    // the cost of going from the city of Riverside to the city of Perris is 8
    // the cost of going from the city of Riverside to the city of Moreno Valley is 8
    // the cost of going from the city of Riverside to the city of Hemet is 15 
    costMatrix[0][0] = 0;  costMatrix[0][1] = 10; costMatrix[0][2] = 8;  costMatrix[0][3] = 15;
    // the cost of going from the city of Perris to the city of Riverside is 10
    // the cost of going from the city of Perris back to the city itslef is of course 0
    // the cost of going from the city of Perris to the city of Moreno Valley is 12 
    // the cost of going to the city of Perris to the city of Hemet is 20
    costMatrix[1][0] = 10; costMatrix[1][1] = 0;  costMatrix[1][2] = 12; costMatrix[1][3] = 20;
    // the cost going from Moreno Valley to the city of Riverside is 8
    // the cost going from Moreno Valley to the city of Perris is 12
    // the cost going from the city Moreno Valley to the city Moreno Valley itself its 0
    // and that cost of going from Moreno Valley to the city of Hemet is 18
    costMatrix[2][0] = 8;  costMatrix[2][1] = 12; costMatrix[2][2] = 0;  costMatrix[2][3] = 18;
    // the cost of going from the city of Hemet to the city of Riverside is h15 
    // the cost of going from the city of Hemet to the city of Perris is 20
    // the cost of going from the city of Hemet to the city of Moreno Valley is 18
    // the cost of going from the city of Hemet to the city Hemet itself of couse again will be 0
    costMatrix[3][0] = 15; costMatrix[3][1] = 20; costMatrix[3][2] = 18; costMatrix[3][3] = 0;

    // Print both matrices
    // both being the distance and the cost matrix's 
    // print the distance 
    printMatrix(distanceMatrix, "Distance Matrix");
    // print the cost matrix 
    printMatrix(costMatrix, "Cost Matrix");

    // the starting city 
    int startCity = 0; // Riverside
    // the ending city 
    int endCity = 3;   // Hemet

    // Calculate shortest path using distance matrix
    // will calculate the shortest distance 
    vector<int> shortestPaths = dijkstra(distanceMatrix, startCity);
    // this is what is going to label the output 
    cout << "\nShortest Distances from " << cities[startCity] << ":\n";
    // this will loop thorugh all of the distances 
    for (size_t i = 0; i < shortestPaths.size(); i++) {
        // this will print all of the distances 
        cout << "To " << cities[i] << ": " << shortestPaths[i] << " miles" << endl;
    }

    // Calculate lowest cost path using cost matrix
    // first line calcualtes the lowest cost 
    vector<int> lowestCostPaths = dijkstraCost(costMatrix, startCity);
    // this line is going to label the output 
    cout << "\nLowest Cost from " << cities[startCity] << ":\n";
    // this is going to loop through all of the cost 
    for (size_t i = 0; i < lowestCostPaths.size(); i++) {
        // and this last line is going to print out all of the cost 
        cout << "To " << cities[i] << ": $" << lowestCostPaths[i] << endl;
    }

    // Finding all paths from Riverside (index 0) to Hemet (index 3)
    // this will initialize the vectors that have been visited 
    vector<bool> visited(4, false);
    // this is a the temperary vector that will just store what current path is being explored 
    vector<int> currentPath;
    // this is my vector that is going to store all of the valid paths 
    vector<vector<int> > allPaths;
    // Then this is just going DFS 
    dfs(startCity, endCity, distanceMatrix, visited, currentPath, allPaths);

    // Output all paths
    // this is going to print all of the possible paths from the start to the end 
    cout << "\nAll possible paths from " << cities[startCity] << " to " << cities[endCity] << ":\n";
    // this is going to loop through all current paths 
    for (size_t i = 0; i < allPaths.size(); i++) {
        cout << "Path " << i + 1 << ": ";
        // this is going to loop through the all the cities that are in the current path 
        for (size_t j = 0; j < allPaths[i].size(); j++) {
            // this is going to print out the city name  
            cout << cities[allPaths[i][j]];
            // if not the last city there will be and arrow that is added 
            if (j != allPaths[i].size() - 1) {
                cout << " -> ";
            }
        }
        // this is the end of the current path's line
        cout << endl;
    }
     // and the return just indicates that the program terminated succesffully.
    return 0;
}
