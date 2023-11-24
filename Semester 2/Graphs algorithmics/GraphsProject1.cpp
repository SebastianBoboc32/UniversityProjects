#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <functional>
#include <random>
class Graph {
private:
    int capacity,number_of_vertices;
    std :: map<int, std :: vector<int> > in_bound;
    std :: map<int, std :: vector<int> > out_bound;
    std::vector< std::pair<int,std::pair<int, int> > > edges;
    std :: vector<int> in_degree;
    std::vector<int> out_degree;
    std :: string file_name_in;
    std :: string file_name_out;
    std::vector<bool> removed_vertices;
    std::vector<int>vertices;

public:
    std::vector<bool>viz;
    std::vector<std::vector<int> > components;
    int number_of_edges;
    Graph(int capacity, int number_of_vertices, std::string file_name_in,
        std::string file_name_out) {
        this->viz = std::vector<bool>(number_of_vertices, 0);
        this->capacity = capacity;
        this->number_of_vertices = number_of_vertices;
        this->in_degree = std::vector<int>(this->number_of_vertices, 0);
        this->out_degree = std::vector<int>(this->number_of_vertices, 0);
        this->file_name_in = file_name_in;
        this->file_name_out = file_name_out;
        this->number_of_edges = 0;
        this->components = std::vector<std::vector<int>>();
        this->removed_vertices = std::vector<bool>(number_of_vertices, false);
    }
    void add_vertex() {

        auto it = std::find(this->removed_vertices.begin(), this->removed_vertices.end(), true);

        if (it != this->removed_vertices.end()) {
            int index = std::distance(this->removed_vertices.begin(), it);
            this->removed_vertices[index] = false;
            this->in_degree[index] = 0;
            this->out_degree[index] = 0;
        }
        else {
            this->number_of_vertices++;
            this->in_degree.push_back(0);
            this->out_degree.push_back(0);
            this->in_bound[this->number_of_vertices - 1] = std::vector<int>();
            this->out_bound[this->number_of_vertices - 1] = std::vector<int>();
            this->removed_vertices.push_back(false);
            this->viz.push_back(false);
        }
    }
    void add_edge(int x, int y, int c) {
        bool added = false;
        for (int i = 0; i < this->number_of_edges; ++i)
            if (this->edges[i].second.first == x && this->edges[i].second.second == y)
                added = true;
        if (added == true)
            return;
        if (!added) {
            this->edges.push_back(std::make_pair(c, std::make_pair(x, y)));
            this->in_bound[y].push_back(x);
            this->out_bound[x].push_back(y);
            ++this->in_degree[y];
            this->number_of_edges++;
            ++this->out_degree[x];
        }
    }
    void remove_vertex(int v) {
            if (v >= this->number_of_vertices) {
                throw std::runtime_error("Invalid vertex index");
            }

            
            this->removed_vertices[v] = true;

            
            for (int x : this->in_bound[v]) {
                this->out_bound[x].erase(std::remove(this->out_bound[x].begin(), this->out_bound[x].end(), v), this->out_bound[x].end());
                --this->out_degree[x];
            }

          
            for (int y : this->out_bound[v]) {
                this->in_bound[y].erase(std::remove(this->in_bound[y].begin(), this->in_bound[y].end(), v), this->in_bound[y].end());
                --this->in_degree[y];
            }

            
            this->in_bound[v].clear();
            this->out_bound[v].clear();
        }
    void remove_edge(int x, int y, int c) {
        std::remove(this->in_bound[y].begin(), this->in_bound[y].end(), x);
        std::remove(this->out_bound[x].begin(), this->out_bound[x].end(), y);
        --this->in_degree[y];
        --this->out_degree[x];
        std::remove(this->edges.begin(), this->edges.end(), std::make_pair(c, std :: make_pair(x, y)));
        this->number_of_edges--;
    }
    int get_capacity() {
        return this->number_of_vertices;
    }

    Graph(const Graph& g) {
        capacity = g.capacity;
        number_of_vertices = g.number_of_vertices;
        in_degree = g.in_degree;
        out_degree = g.out_degree;
        file_name_in = g.file_name_in;
        file_name_out = g.file_name_out;
        in_bound = g.in_bound;
        edges = g.edges;
        out_bound = g.out_bound;
        viz = g.viz;
        components = g.components;
    }

    int get_nr_of_edges() {
        return this->edges.size();
    }

    std::vector<std::vector<std::pair<int, int>>> convertToAdjacencyList() const {
        std::vector<std::vector<std::pair<int, int>>> adjacencyList(number_of_vertices);

        for (const auto& edge : edges) {
            int u = edge.second.first;
            int v = edge.second.second;
            int cost = edge.first;

            adjacencyList[u].emplace_back(v, cost);
            adjacencyList[v].emplace_back(u, cost);
        }

        return adjacencyList;
    }

    void read_graph() {
        std ::ifstream read(this->file_name_in);
        int n, m, cost, vrt_1, vrt_2;
        read >> n >> m;
        for (int i = 0; i < m; ++i) {
            read  >> vrt_1 >> vrt_2 >> cost;
            this->add_edge(vrt_1, vrt_2, cost);
        }
    }
    bool verify_if_edge(int x, int y) {
        for (int i = 0; i < this->in_bound[y].size(); ++i)
            if (this->in_bound[y][i] == x)
                return true;
        return false;
    }
    int get_in_degree(int v) {
        return this->in_degree[v];
    }
    int get_out_degree(int v) {
        return this->out_degree[v];
    }

    void print_vertices() {
        std::ofstream out(this->file_name_out);
        for (int i = 0; i < this->capacity; ++i)
            out << i << " ";
        out << "\n";
        out.close();
    }

    void print_in_bound_vertices(int v) {
        std::ofstream out(this->file_name_out);
        for (int i = 0; i < this->in_bound[v].size(); ++i)
            out << this->in_bound[v][i] << " ";
        out << "\n";
        out.close();
    }

    void print_out_bound_vertices(int v) {
        std::ofstream out(this->file_name_out);
        for (int i = 0; i < this->out_bound[v].size(); ++i)
            out << this->out_bound[v][i] << " ";
            out << "\n";
        
        out.close();
    }

    void modify_cost(int a,int b,int new_cost) {
        for (int i = 0; i < this->edges.size(); ++i)
            if (this->edges[i].second == std::make_pair(a, b))
                this->edges[i].first = new_cost;
    }

    int get_cost(int a, int b) {
        for (int i = 0; i < this->edges.size(); ++i)
            if (this->edges[i].second == std::make_pair(a, b))
                return this->edges[i].first;
    }

    void print_all_edges() {
        for (int i = 0; i < this->edges.size(); ++i)
            std::cout << this->edges[i].second.first << " " << this->edges[i].second.second << " " << this->edges[i].first << "\n";
    }

    void output_graph() {
        std::ofstream out(this->file_name_out);
        for (int i = 0; i < this->edges.size(); ++i) {
            out << "Edge: ";
            out << this->edges[i].second.first << "->" << this->edges[i].second.second;
            out << " with cost: " << this->edges[i].first << '\n';
        }
        out.close();
    }

    Graph& operator = (const Graph &g) {
        this->capacity = g.capacity;
        this->number_of_vertices = g.number_of_vertices;
        this->in_degree = g.in_degree;
        this->out_degree = g.out_degree;
        this->file_name_in = g.file_name_in;
        this->file_name_out = g.file_name_out;
        this->in_bound = g.in_bound;
        this->edges = g.edges;
        this->out_bound = g.out_bound;
        return *this;
    }
    
    int nr_vert() {
        return this->number_of_vertices;
    }

    Graph create_undirected() {
        Graph g1(2 * this->number_of_edges,this->number_of_vertices, this->file_name_in, this->file_name_out);
        for (int i = 0; i < this->number_of_edges; ++i) {
            int c, x, y;
            std::pair<int, std::pair<int, int> > edge;
            edge = this->edges[i];
            c = edge.first;
            x = edge.second.first;
            y = edge.second.second;
            g1.add_edge(y, x, c);
            g1.add_edge(x, y, c);
        }  
        return g1;
    }
    void DFS(int root,int k) {
        this->components[k].push_back(root);
        viz[root] = true;
        for (int i = 0; i < this->out_bound[root].size(); ++i)
            if(!viz[out_bound[root][i]])
                DFS(this->out_bound[root][i],k); 
    }
    void find_connected_components() {
        int k = 0;
        for (int i = 0; i < this->number_of_vertices; ++i) {
            if (!viz[i]) {
                this->components.push_back(std::vector<int>());
                DFS(i, k);
                k++;
            }
        }
    }
    std::vector<int> fordAlgorithm(int start_vertex, int end_vertex) {
        int num_vertices = number_of_vertices;
        std::vector<int> dist(num_vertices, std::numeric_limits<int>::max());
        std::vector<int> pred(num_vertices, -1);
        dist[start_vertex] = 0;

        
        for (int i = 1; i < num_vertices - 1; ++i) {
            for (const auto& edge : edges) {
                int u = edge.second.first;
                int v = edge.second.second;
                int cost = edge.first;

                if (dist[u] != std::numeric_limits<int>::max() && dist[u] + cost < dist[v]) {
                    dist[v] = dist[u] + cost;
                    pred[v] = u;
                }
            }
        }

        for (const auto& edge : edges) {
            int u = edge.second.first;
            int v = edge.second.second;
            int cost = edge.first;

            if (dist[u] != std::numeric_limits<int>::max() && dist[u] + cost < dist[v]) {
                std::cout<<"Graph contains negative cost cycles";
            }
        }

        std::vector<int> walk;
        int current_vertex = end_vertex;

        while (current_vertex != -1) {
            walk.push_back(current_vertex);
            current_vertex = pred[current_vertex];
        }

        std::reverse(walk.begin(), walk.end());
        
        return walk;
    }
    typedef std::pair<int, int> Edge; // pair of (cost, vertex)

    std::vector<std::pair<int, int>> primAlgorithm(int start_vertex, const std::vector<std::vector<Edge>>& graph) {
        int number_of_vertices = graph.size();
        std::vector<bool> visited(number_of_vertices, false);
        std::vector<std::pair<int, int>> mst(number_of_vertices, std::make_pair(INT_MAX, -1)); // Minimum Spanning Tree
        std::priority_queue<Edge, std::vector<Edge>, std::greater<Edge>> pq;

        // Start with the given start_vertex
        mst[start_vertex] = std::make_pair(0, -1); // (cost, predecessor)
        pq.push(std::make_pair(0, start_vertex));

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            if (visited[u])
                continue;

            visited[u] = true;

            // Iterate through all the outgoing edges from u
            for (const auto& edge : graph[u]) {
                int v = edge.second;
                int cost = edge.first;

                if (!visited[v] && cost < mst[v].first) {
                    mst[v] = std::make_pair(cost, u); // Update cost and predecessor of v
                    pq.push(std::make_pair(cost, v));
                }
            }
        }

        // Remove the start_vertex entry from the MST
        mst[start_vertex] = std::make_pair(INT_MAX, -1);

        return mst;
    }
};

void clear_input_stream() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Graph create_random_graph(int num_vertices, int num_edges) {
    Graph g(num_vertices, num_vertices, "input.txt", "output.txt");

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, num_vertices - 1);
    std::uniform_int_distribution<> dis_cost(1, 100);


    while (g.number_of_edges < num_edges) {
        int u = dis(gen);
        int v = dis(gen);
        int cost = dis_cost(gen);
        if (u != v && !g.verify_if_edge(u, v)) {
            g.add_edge(u, v, cost);
        }
    }

    return g;
}



void user_interface() {

    std::cout << "Select the number of edges: \n";
    int numb_edge, numb_vert;
    std::cin >> numb_edge;
    clear_input_stream();
    std::cout << "Select the number of vertices: \n";
    std::cin >> numb_vert;
    clear_input_stream();
    Graph graph(numb_edge, numb_vert, "input.txt", "output.txt");

    while (true) {
        std::cout << "Choose an option:" << std::endl;
        std::cout << "1. Get the number of vertices" << std::endl;
        std::cout << "2. Parse (iterate) the set of vertices" << std::endl;
        std::cout << "3. Check if there is an edge between two vertices" << std::endl;
        std::cout << "4. Get the in-degree and out-degree of a specified vertex" << std::endl;
        std::cout << "5. Parse the set of outbound edges of a specified vertex" << std::endl;
        std::cout << "6. Parse the set of inbound edges of a specified vertex" << std::endl;
        std::cout << "7. Retrieve or modify the information attached to a specified edge" << std::endl;
        std::cout << "8. Add or remove an edge" << std::endl;
        std::cout << "9. Add or remove a vertex" << std::endl;
        std::cout << "10. Copy the graph" << std::endl;
        std::cout << "11. Read the graph from a text file" << std::endl;
        std::cout << "12. Write the graph to a text file" << std::endl;
        std::cout << "13. Create a random graph with a specified number of vertices and edges" << std::endl;
        std::cout << "14.Find the connected components of the undirected version of this graph using depth-first search\n";
        std::cout << "15.Use ford's algortihm\n";
        std::cout << "16.Use prim's algorithm\n";
        std::cout << "0. Exit" << std::endl;


        int option;
        std::cin >> option;
        clear_input_stream();
        switch (option) {
        case 1: {
            int num_vertices = graph.get_capacity();
            std::cout << "The number of vertices is: " << num_vertices << std::endl;
            break;
        }
        case 2: {
            graph.print_vertices();
            std::cout << "Vertices printed to the output file." << std::endl;
            break;
        }
        case 3: {
            int x, y;
            std::cout << "Enter the two vertices: ";
            std::cin >> x >> y;
            if (graph.verify_if_edge(x, y)) {
                std::cout << "There is an edge between " << x << " and " << y << std::endl;
            }
            else {
                std::cout << "There is no edge between " << x << " and " << y << std::endl;
            }
            break;
        }
        case 4: {
            int v;
            std::cout << "Enter the vertex: ";
            std::cin >> v;
            std::cout << "In-degree: " << graph.get_in_degree(v) << std::endl;
            std::cout << "Out-degree: " << graph.get_out_degree(v) << std::endl;
            break;
        }
        case 5: {
            int v;
            std::cout << "Enter the vertex: ";
            std::cin >> v;
            graph.print_out_bound_vertices(v);
            std::cout << "Outbound edges of vertex " << v << " printed to the output file." << std::endl;
            break;
        }
        case 6: {
            int v;
            std::cout << "Enter the vertex: ";
            std::cin >> v;
            graph.print_in_bound_vertices(v);
            std::cout << "Inbound edges of vertex " << v << " printed to the output file." << std::endl;
            break;
        }
        case 7: {
            int a, b;
            std::cout << "Enter the edge (from_vertex, to_vertex): ";
            std::cin >> a >> b;
            int cost = graph.get_cost(a, b);
            std::cout << "Current cost: " << cost << std::endl;

            int new_cost;
            std::cout << "Enter new cost (-1 to keep the current cost): ";
            std::cin >> new_cost;
            if (new_cost != -1) {
                graph.modify_cost(a, b, new_cost);
                std::cout << "Cost updated." << std::endl;
            }
            break;
        }
        case 8: {
            std::cout << "Choose an option:" << std::endl;
            std::cout << "1. Add an edge" << std::endl;
            std::cout << "2. Remove an edge" << std::endl;
            int choice;
            std::cin >> choice;
            int x, y, c;
            std::cout << "Enter the edge (from_vertex, to_vertex): ";
            std::cin >> x >> y;
            if (choice == 1) {
                std::cout << "Enter the cost: ";
                std::cin >> c;
                graph.add_edge(x, y, c);
                std::cout << "Edge added." << std::endl;
            }
            else if (choice == 2) {
                std::cout << "Enter the cost: ";
                std::cin >> c;
                graph.remove_edge(x, y, c);
                std::cout << "Edge removed." << std::endl;
            }
            break;
        }
        case 9: {
            int opt, vertex;
            std::cout << "Choose an option:\n";
            std::cout << "1. Add a vertex\n";
            std::cout << "2. Remove a vertex\n";
            std::cin >> opt;

            switch (opt) {
            case 1:
                graph.add_vertex();
                std::cout << "A new vertex has been added." << std::endl;
                break;
            case 2:
                std::cout << "Enter the index of the vertex to remove: ";
                std::cin >> vertex;

                try {
                    graph.remove_vertex(vertex);
                    std::cout << "The vertex has been removed." << std::endl;
                }
                catch (const std::runtime_error& e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }

                break;
            default:
                std::cout << "Invalid option." << std::endl;
                break;
            }

            break;
        }
        case 10: {
            Graph graph_copy = graph;
            graph_copy.output_graph();
            std::cout << "Graph copied successfully." << std::endl;
            break;
        }
        case 11: {
            graph.read_graph();
            graph.print_all_edges();
            std::cout << "Graph read from the input file successfully." << std::endl;
            break;
        }
        case 12: {
            graph.output_graph();
            std::cout << "Graph written to the output file successfully." << std::endl;
            break;
        }
        case 13: {
            graph = create_random_graph(numb_vert, numb_edge);
            std::cout << "Random graph created successfully." << std::endl;
            graph.print_all_edges();
            break;
        }
        case 14: {
            Graph undirected_graph = graph.create_undirected();
            undirected_graph.find_connected_components();
            std::cout << "Connected components of the undirected graph:" << std::endl;
            for (int i = 0; i < undirected_graph.components.size(); ++i) {
                if (undirected_graph.components[i].empty()) {
                    continue;
                }
                std::cout << "Component " << i + 1 << ": ";
                for (int j = 0; j < undirected_graph.components[i].size(); ++j) {
                    std::cout << undirected_graph.components[i][j] << " ";
                }
                std::cout << std::endl;
            }
            
           
            break;
        }
        case 0: {
            return;
        }
        case 15: {
            int source, destination;
            std::cout << "Enter the source vertex: ";
            std::cin >> source;
            std::cout << "Enter the destination vertex: ";
            std::cin >> destination;
            std::vector<int> shortest_path = graph.fordAlgorithm(source, destination);
            std::cout << "Shortest path from " << source << " to " << destination << ": ";
            for (int i = 0; i < shortest_path.size(); ++i) {
                std::cout << shortest_path[i] << " ";
            }
            std::cout << std::endl;
            break;
        }
        case 16: {
            int start_vertex;
            std::cout << "Enter the starting vertex for Prim's algorithm: ";
            std::cin >> start_vertex;
            std::vector<std::vector<std::pair<int, int>>> adjacencyList = graph.convertToAdjacencyList();
            Graph undirected = graph.create_undirected();
            undirected.print_all_edges();
            
            std::vector<std::pair<int, int>> mst = undirected.primAlgorithm(start_vertex, adjacencyList);

            std::cout << "Minimum Spanning Tree (MST) using Prim's algorithm:" << std::endl;
            for (int i = 0; i < mst.size(); ++i) {
                if (i == start_vertex)
                    continue;

                int cost = mst[i].first;
                int predecessor = mst[i].second;

                std::cout << "Vertex: " << i << ", Cost: " << cost << ", Predecessor: " << predecessor << std::endl;
            }
            
            break;
        }
        default: {
            std::cout << "Invalid option. Please try again." << std::endl;
            break;
        }
        }
    }
}

int main()
{
    user_interface();
    _CrtDumpMemoryLeaks();
    return 0;
}


