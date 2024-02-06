#include "the6.h"

// do not add extra libraries here

int find_structure(std::vector<std::vector<std::pair<int, int>>> &bond_energies, std::vector<std::vector<std::pair<int, int>>> &lowest_energy_structure) {
    int lowest_total_energy = 0;
    
    int V = bond_energies.size();
    std::vector<bool> visited(V, false);
    std::vector<int> min_weight(V, INT_MAX);
    std::vector<int> parent(V, -1);

    min_weight[0] = 0; 

    for (int i = 0; i < V - 1; ++i) {
        int min_vertex = -1;
        for (int v = 0; v < V; ++v) {
            if (!visited[v] && (min_vertex == -1 || min_weight[v] < min_weight[min_vertex])) {
                min_vertex = v;
            }
        }

        visited[min_vertex] = true;

        for (const auto &neighbor : bond_energies[min_vertex]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (!visited[v] && weight < min_weight[v]) {
                parent[v] = min_vertex;
                min_weight[v] = weight;
            }
        }
    }

    lowest_energy_structure.clear();
    lowest_energy_structure.resize(V);

    for (int i = 1; i < V; ++i) {
        lowest_total_energy += min_weight[i];
        lowest_energy_structure[i].emplace_back(parent[i], min_weight[i]);
        lowest_energy_structure[parent[i]].emplace_back(i, min_weight[i]);
    }

    return lowest_total_energy;
}

#include <vector>
#include <algorithm>

void dfs(int node, const std::vector<std::vector<std::pair<int,int>>>& molecule_structure, std::vector<bool>& visited, std::vector<int>& current_chain, std::vector<int>& max_chain) {
    visited[node] = true;
    current_chain.push_back(node);

    for (const auto& neighbor : molecule_structure[node]) {
        int next_node = neighbor.first;

        if (!visited[next_node]) {
            dfs(next_node, molecule_structure, visited, current_chain, max_chain);
        }
    }

    if (current_chain.size() > max_chain.size()) {
        max_chain = current_chain;
    }

    current_chain.pop_back();
    visited[node] = false;
}

int find_longest_chain(std::vector<std::vector<std::pair<int,int>>>& molecule_structure, std::vector<int>& chain) {
    int longest_chain_size = 0;
    int num_atoms = molecule_structure.size();

    std::vector<bool> visited(num_atoms, false);
    std::vector<int> current_chain, max_chain;

    for (int i = 0; i < num_atoms; ++i) {
        if (!visited[i]) {
            dfs(i, molecule_structure, visited, current_chain, max_chain);
        }
    }

    chain = max_chain;
    longest_chain_size = max_chain.size();
    return longest_chain_size;
}
