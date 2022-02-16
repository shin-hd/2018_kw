#include "Manager.h"
#include "Sort.h"
#include <sstream>
#include <string>
#include <cstring>
#include <iterator>
using namespace std;

Manager::~Manager()
{
    if (fout.is_open())
        fout.close();

    if (ferr.is_open())
        ferr.close();
}

void Manager::Run(const char* filepath)
{
    fout.open(RESULT_LOG_PATH);
    ferr.open(ERROR_LOG_PATH);

    // TODO: implement

	ifstream fin;
	fin.open(filepath);
	istringstream commandStream;
	
	if (!fin.is_open()) {
		fout << "====== " << "SYSTEM" << " ======" << endl;
		PrintErrorString(CommandFileNotExist);
		fout << "====================" << endl << endl;

		fout << "====================" << endl;
		PrintError(CommandFileNotExist);
		fout << "====================" << endl << endl;
		return;
	}

	char cmd[30] = "";
	char str[30] = "";
	char str2[30] = "";
	char buf[128] = "";

	Result errorType;

	while (fin.getline(buf, 64)) {
		commandStream.clear();
		commandStream.str(buf);
		commandStream >> cmd;

		str[0] = '\0';
		str2[0] = '\0';

		if (strcmp(cmd, "LOAD") == 0) {
			commandStream >> str;
			
			fout << "====== " << cmd << " ======" << endl;
			if (strcmp(str, "") != 0)
				errorType = Load(str);
			else
				errorType = LoadFileNotExist;
			PrintErrorString(errorType);
			fout << "====================" << endl << endl;

			fout << "====================" << endl;
			PrintError(errorType);
			fout << "====================" << endl << endl;
		}
		else if (strcmp(cmd, "PRINT") == 0) {
			fout << "====== " << cmd << " ======" << endl;
			errorType = Print();
			PrintErrorString(errorType);
			fout << "====================" << endl << endl;

			fout << "====================" << endl;
			PrintError(errorType);
			fout << "====================" << endl << endl;
		}
		else if (strcmp(cmd, "DFS") == 0) {
			commandStream >> str;
			commandStream >> str2;

			fout << "====== " << cmd << " ======" << endl;
			if (strcmp(str, "") != 0 || strcmp(str2, "") != 0)
				errorType = FindPathDfs(atoi(str), atoi(str2));
			else errorType = VertexKeyNotExist;
			PrintErrorString(errorType);
			fout << "====================" << endl << endl;
			
			fout << "====================" << endl;
			PrintError(errorType);
			fout << "====================" << endl << endl;
		}
		else if (strcmp(cmd, "DIJKSTRA") == 0) {
			commandStream >> str;
			commandStream >> str2;

			fout << "====== " << cmd << " ======" << endl;
			if (strcmp(str, "") != 0 || strcmp(str2, "") != 0)
				errorType = FindShortestPathDijkstraUsingSet(atoi(str), atoi(str2));
			else errorType = VertexKeyNotExist;
			PrintErrorString(errorType);
			fout << "====================" << endl << endl;

			fout << "====================" << endl;
			PrintError(errorType);
			fout << "====================" << endl << endl;
		}
		else if (strcmp(cmd, "DIJKSTRAMIN") == 0) {
			commandStream >> str;
			commandStream >> str2;
			
			fout << "====== " << cmd << " ======" << endl;
			if (strcmp(str, "") != 0 || strcmp(str2, "") != 0)
				errorType = FindShortestPathDijkstraUsingMinHeap(atoi(str), atoi(str2));
			else errorType = VertexKeyNotExist;
			PrintErrorString(errorType);
			fout << "====================" << endl << endl;

			fout << "====================" << endl;
			PrintError(errorType);
			fout << "====================" << endl << endl;
		}
		else if (strcmp(cmd, "BELLMANFORD") == 0) {
			commandStream >> str;
			commandStream >> str2;
			
			fout << "====== " << cmd << " ======" << endl;
			if (strcmp(str, "") != 0 || strcmp(str2, "") != 0)
				errorType = FindShortestPathBellmanFord(atoi(str), atoi(str2));
			else errorType = VertexKeyNotExist;
			PrintErrorString(errorType);
			fout << "====================" << endl << endl;

			fout << "====================" << endl;
			PrintError(errorType);
			fout << "====================" << endl << endl;
		}
		else if (strcmp(cmd, "FLOYD") == 0) {
			fout << "====== " << cmd << " ======" << endl;
			errorType = FindShortestPathFloyd();
			PrintErrorString(errorType);
			fout << "====================" << endl << endl;

			fout << "====================" << endl;
			PrintError(errorType);
			fout << "====================" << endl << endl;
		}
		else {
			fout << "====== " << cmd << " ======" << endl;
			PrintErrorString(NonDefinedCommand);
			fout << "====================" << endl << endl;

			fout << "====================" << endl;
			PrintError(NonDefinedCommand);
			fout << "====================" << endl << endl;
		}
	}
	m_graph.Clear();
}
void Manager::PrintError(Result result)
{
	fout << "Error code: " << result << std::endl;
}

void Manager::PrintErrorString(Result result) {
	if (result == 101)
		fout << "LoadFileNotExist" << endl;
	else if(result == 202)
		fout << "GraphNotExist" << endl;
	else if (result == 200)
		fout << "VertexKeyNotExist" << endl;
	else if (result == 201)
		fout << "InvalidVertexKey" << endl;
	else if (result == 203)
		fout << "InvalidAlgorithm" << endl;
	else if (result == 204)
		fout << "NegativeCycleDetected" << endl;
	else if(result == 100)
		fout << "CommandFileNotExist" << endl;
	else if(result == 300)
		fout << "NonDefinedCommand" << endl;
}

/// <summary>
/// make a graph
/// </summary>
///
/// <param name="filepath">
/// the filepath to read to make the graph
/// </param>
///
/// <returns>
/// Result::Success if load is successful.
/// Result::LoadFileNotExist if file is not exist.
/// </returns>
Result Manager::Load(const char* filepath)
{
    // TODO: implement
	
	ifstream fin(filepath);
	if (!fin.is_open())
		return LoadFileNotExist;

	string line;
	istringstream lineStream;
	getline(fin, line);
	
	int size = atoi(line.c_str());
	for (int i = 0; i < size; i++) { // add vertex
		getline(fin, line);
		lineStream.clear();
		lineStream.str(line);

		m_graph.AddVertex(i);
		for (int j = 0; j < size; j++) { // add edge
			char edge[10];
			lineStream >> edge;
			if(strcmp(edge, "0") != 0 && strcmp(edge, "") != 0)
				m_graph.AddEdge(i, j, atoi(edge));
		}
	}
	fout << "Success" << endl;
	return Success;
}
/// <summary>
/// print out the graph as matrix form
/// </summary>
///
/// <returns>
/// Result::Success if the printing is successful
/// Result::GraphNotExist if there is no graph
/// </returns>
Result Manager::Print()
{
    // TODO: implement

	try {
		m_graph.Print(fout);
		return Success;
	}
	catch (...) {
		return GraphNotExist;
	}
}
/// <summary>
/// find the path from startVertexKey to endVertexKey with DFS (stack)
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindPathDfs(int startVertexKey, int endVertexKey)
{
    // TODO: implement

	try {
		vector<int> shortestPath = m_graph.FindPathDfs(startVertexKey, endVertexKey);
		PrintShortestPath(shortestPath);
		return Success;
	}
	catch (int errorType) {
		if (errorType == 1)
			return InvalidVertexKey;
		else if (errorType == 2)
			return GraphNotExist;
		else if (errorType == 3)
			return InvalidAlgorithm;
		else // undefined error type
			return Success;
	}
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using std::set
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingSet(int startVertexKey, int endVertexKey)
{
    // TODO: implement

	try {
		vector<int> shortestPath = m_graph.FindShortestPathDijkstraUsingSet(startVertexKey, endVertexKey);
		PrintShortestPath(shortestPath);
		return Success;
	}
	catch (int errorType) {
		if (errorType == 1)
			return InvalidVertexKey;
		else if (errorType == 2)
			return GraphNotExist;
		else if (errorType == 3)
			return InvalidAlgorithm;
		else // undefined error type
			return Success;
	}
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Dijkstra using MinHeap
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::InvalidAlgorithm if an exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathDijkstraUsingMinHeap(int startVertexKey, int endVertexKey)
{
    // TODO: implement

	try {
		vector<int> shortestPath = m_graph.FindShortestPathDijkstraUsingMinHeap(startVertexKey, endVertexKey);
		PrintShortestPath(shortestPath);
		return Success;
	}
	catch (int errorType) {
		if (errorType == 1)
			return InvalidVertexKey;
		else if (errorType == 2)
			return GraphNotExist;
		else if (errorType == 3)
			return InvalidAlgorithm;
		else // undefined error type
			return Success;
	}
}
/// <summary>
/// find the shortest path from startVertexKey to endVertexKey with Bellman-Ford
/// </summary>
///
/// <param name="startVertexKey">
/// the start vertex key
/// </param>
/// <param name="endVertexKey">
/// the end vertex key
/// </param>
///
/// <returns>
/// Result::InvalidVertexKey or Result::GraphNotExist or Result::NegativeCycleDetected if exception has occurred.
/// Result::Success otherwise.
/// </returns>
Result Manager::FindShortestPathBellmanFord(int startVertexKey, int endVertexKey)
{
    // TODO: implement
	
	try {
		vector<int> shortestPath = m_graph.FindShortestPathBellmanFord(startVertexKey, endVertexKey);
		PrintShortestPath(shortestPath);
		return Success;
	}
	catch (int errorType) {
		if (errorType == 1)
			return InvalidVertexKey;
		else if (errorType == 2)
			return GraphNotExist;
		else if (errorType == 4)
			return NegativeCycleDetected;
		else // undefined error type
			return Success;
	}
}

Result Manager::FindShortestPathFloyd() {
	try {
		vector<vector<int>> Floyd = m_graph.FindShortestPathFloyd();
		for (int i = 0; i < m_graph.Size(); i++) {
			for (int j = 0; j < m_graph.Size(); j++) {
				if (Floyd[i][j] >= 10000000)
					fout << "0 ";
				else
					fout << Floyd[i][j] << " ";
			}
			fout << endl;
		}
		return Success;
	}
	catch (int errorType) {
		if (errorType == 2)
			return GraphNotExist;
		else if (errorType == 4)
			return NegativeCycleDetected;
		else // undefined error type
			return Success;
	}
}

void Manager::PrintShortestPath(vector<int> shortestPath) {
	int weight = shortestPath.back();	// back of shortestPath is path lenth
	shortestPath.pop_back();

	vector<int>::reverse_iterator rPathIt;
	vector<int>::iterator pathIt;

	fout << "shortest path:";
	for (rPathIt = shortestPath.rbegin(); rPathIt != shortestPath.rend(); rPathIt++) {
		fout << " " << *rPathIt;
	}
	
	quickSort(shortestPath, 0, shortestPath.size());		// sort
	fout << endl << "sorted nodes:";
	for (pathIt = shortestPath.begin(); pathIt != shortestPath.end(); pathIt++) {
		fout << " " << *pathIt;
	}

	fout << endl << "path lenth: " << weight << endl;
}
