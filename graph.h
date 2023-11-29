/*
*  autor: Benjamin Valdes Aguirre
*  fecha: Diciembre 2020
*  programa: act 4.1 Implementacion Grafos
*  desc: estos programas son solciones parciales a algunos de
*  las actividades planteadas en el curso TC1031
*
*
*  Extiende este archivo para completar tu soución.
*/

#ifndef Graph_H_
#define Graph_H_

#include <string>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <algorithm>

using namespace std;


class Graph {
private:
		int edgesList;
		int edgesMat;
		int nodes;
    vector<int> *adjList;
		int *adjMatrix;
		//vector<Type> *vect = new vector<Type>

public:
		void loadGraphMat(string, int, int);
		Graph(int);
		Graph();
		void addEdgeAdjMatrix(int, int);
		string printAdjMat();
		string printAdjMat_clean();
		string printAdjList();
		bool contains(list<int>, int);
		void sortAdjList();
		string DFS(int, int);
		string BFS(int, int);
		void loadGraphList(string, int, int);
};


void Graph::loadGraphMat(string name, int a, int b){
	adjMatrix = new int [a*b];
	nodes = a;
	for (int i = 0; i < a*b; i++)
		adjMatrix[i] = 0;
		string line;
		ifstream lee (name);
		int u, v;
		if (lee.is_open()){
			while (getline(lee, line)){
				u = stoi(line.substr(1,1));
				v = stoi(line.substr(4,1));
				addEdgeAdjMatrix(u,v);
			}
			lee.close(); // Closes the file
		} else {
			cout << "Unable to open file";
		}
}

Graph::Graph() {
	edgesList = edgesMat = 0;
}

Graph::Graph(int n) {
	nodes = n;
	adjList = new vector<int>[nodes];
	adjMatrix = new int [nodes*nodes];
	for (int i = 0; i < nodes*nodes; i++)
		adjMatrix[i] = 0;
	edgesList = edgesMat = 0;
}

void Graph::addEdgeAdjMatrix(int u, int v){
	adjMatrix[u*nodes+v] = 1;
	adjMatrix[v*nodes+u] = 1;
	edgesMat++;
}

string Graph::printAdjList(){
	  stringstream aux;
		for (int i = 0; i < nodes; i++){
	        aux << "vertex "
	             << i << " :";
	        for (int j = 0; j < adjList[i].size(); j ++){
							 aux << " " << adjList[i][j];
					}
	        aux << " ";
    }
		return aux.str();

}

string Graph::printAdjMat(){
	stringstream aux;
	for (int i = 0; i < nodes; i++){
	   for (int j = 0; j < nodes; j++){
			 aux << adjMatrix[i*nodes+j] << " ";
		 }
  }
	return aux.str();
}

string Graph::printAdjMat_clean(){
	stringstream aux;
	aux << "\n nodes \t|";
	for (int i = 0; i < nodes; i++){
			aux << "\t" << i ;
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
			aux << "__________";
	}
	aux << "\n";
	for (int i = 0; i < nodes; i++){
		 aux << i << "\t|";
	   for (int j = 0; j < nodes; j++){
			 aux << "\t" << adjMatrix[i*nodes+j];
		 }
	   aux << "\n";
  }
	return aux.str();
}

void Graph::loadGraphList(string name, int a, int b){
	nodes = a;
	adjList = new vector<int>[nodes];
	edgesList = 0;
	string line;
	ifstream lee (name);
	int u, v;
	if (lee.is_open()){
		while (getline(lee, line)){
			u = stoi(line.substr(1,1));
			v = stoi(line.substr(4,1));
			adjList[u].push_back(v);
			adjList[v].push_back(u);
			edgesList++;
		}
		lee.close(); // Closes the file
	} else {
		cout << "Unable to open file";
	}
}

bool Graph::contains(list<int> visited, int node){
	list<int>::iterator it;
	it = find(visited.begin(), visited.end(), node);
	if (it != visited.end())
		return true;
	else
		return false;
}


void Graph::sortAdjList(){
	for (int i = 0; i < nodes; i++){
		sort(adjList[i].begin(), adjList[i].end());
	}
}

string Graph::DFS(int s, int d){
	stringstream aux;
	stack<int> stack;
	list<int> visited;
	stack.push(s);
	int current;
	while (!stack.empty()){
		current = stack.top();
		stack.pop();
		if (!contains(visited, current)){
			visited.push_back(current);
			aux << current << " ";
			if (current == d)
				break;
			for (int i = adjList[current].size()-1; i >= 0; i--){
				if (!contains(visited, adjList[current][i]))
					stack.push(adjList[current][i]);
			}
		}
	}
	if (current != d)
		aux << "no path";
	else {
		aux << "\npath: ";
		for (list<int>::iterator it = visited.begin(); it != visited.end(); it++){
			aux << *it << " ";
		}
	}
	return aux.str();
}

string Graph::BFS(int s, int d){
	stringstream aux;
	queue<int> queue;
	list<int> visited;
	queue.push(s);
	int current;
	while (!queue.empty()){
		current = queue.front();
		queue.pop();
		if (!contains(visited, current)){
			visited.push_back(current);
			aux << current << " ";
			if (current == d)
				break;
			for (int i = 0; i < adjList[current].size(); i++){
				if (!contains(visited, adjList[current][i]))
					queue.push(adjList[current][i]);
			}
		}
	}
	if (current != d)
		aux << "no path";
	else {
		aux << "\npath: ";
		for (list<int>::iterator it = visited.begin(); it != visited.end(); it++){
			aux << *it << " ";
		}
	}
	return aux.str();
}



#endif /* Graph_H_ */
