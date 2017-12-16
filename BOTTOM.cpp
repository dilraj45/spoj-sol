#include <iostream>
#include <vector>
#include <list>
#include <set>

using namespace std;

struct setCmp {
	bool operator() (const pair<long int, long int> &a, const pair<long int, long int> &b) {
		return b.second < a.second;
	}
};

struct cmp {
	bool operator() (const long int &a, const long int&b) {
		return a < b;
	}
};

struct Graph {
	vector <list<long int>> edges;
	long int num;

	Graph (long int num) {
		this->num = num;
		edges.resize(num);
		for (auto l : edges)
			l.clear();
	}

	void addEdge (long int u, long int v) {
		edges[u].push_back (v);
	}

	void graph_transpose (Graph &graph) {
		for (long int u; u < edges.size(); u++)
			for (auto v: edges[u])
				graph.addEdge (v, u);
	}
};
 
void dfs_util (Graph &graph, long int root, long int &time, vector <bool> &visited, set <pair <long int, long int>, setCmp> &finish_time) {
	visited[root] = true;
	for (auto child: graph.edges [root]) {
		if (!visited[child])
			dfs_util (graph, child, time, visited, finish_time);
	}
	time++;
	finish_time.insert (make_pair (root, time));
}

void dfs (Graph &graph, vector <bool> &visited, set <pair <long int , long int>, setCmp> &finish_time) {
	long int time = 0;
	for (long int i = 0; i < graph.num; i++)
		if (!visited[i])
			dfs_util (graph, i, time, visited, finish_time);
}

void sink_nodes (Graph &graph) {
	vector <bool> visited (graph.num, false);
	set <pair<long int, long int>, setCmp> finish_time, tmp;
	dfs (graph, visited, finish_time);
	Graph transpose (graph.num);
	graph.graph_transpose(transpose);
	fill (visited.begin(), visited.end(), false);
	long int temp;
	set <long int, cmp> ans;
	for (auto entry: finish_time) {
		tmp.clear();
		if (!visited [entry.first]) {
			dfs_util (transpose, entry.first, temp, visited, tmp);
		}
		
		set <long int> vertices_scc;
		for (auto vertice: tmp)
			vertices_scc.insert (vertice.first);
		bool flag = false;
		for (auto u : vertices_scc)
			for (auto v : graph.edges[u]) {
				if (vertices_scc.find (v) == vertices_scc.end())
					{flag = true;}	
			}
		if (!flag)
			ans.insert (vertices_scc.begin(), vertices_scc.end());
	}

	for (auto i: ans)
		cout << i + 1 << " ";
	cout << endl;
}


int main() {
	long int edges, vertices, u, v;
	while (true) {
		cin >> vertices;
		if (vertices == 0)
			return 0;
		cin >> edges;
		Graph graph (vertices);
		for (long int i = 0; i < edges; i++) {
			cin >> u >> v;
			graph.addEdge (u - 1, v - 1);
		}
		sink_nodes(graph);
	}
}