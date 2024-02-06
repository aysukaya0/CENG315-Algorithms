#include "the7.h"

// do not add extra libraries here

void dijkstra(const std::vector<std::vector<std::pair<int, int>>>& network, std::vector<int>& distances, int src) {
    int size = network.size();
    std::vector<bool> visited(size, false);
    distances.assign(size, INT_MAX);
    distances[src] = 0;

    for (int i = 0; i < size - 1; ++i) {
        int min = INT_MAX;
        int min_index;

        for (int j = 0; j < size; ++j) {
            if (!visited[j] && distances[j] <= min) {
                min = distances[j];
                min_index = j;
            }
        }

        visited[min_index] = true;

        for (const std::pair<int,int>& neighbor : network[min_index]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!visited[v] && distances[min_index] != INT_MAX && distances[min_index] + weight < distances[v]) {
                distances[v] = distances[min_index] + weight;
            }
        }
    }
}

void find_SP(const std::vector<std::vector<std::pair<int, int>>>& network, std::vector<std::vector<int>>& sp) {
    int size = network.size();

    for (int i = 0; i < size; ++i) {
        std::vector<int> distances(size, INT_MAX);
        dijkstra(network, distances, i);

        for (int j = 0; j < size; ++j) {
            if (i == j) {
                sp[i][j] = 0;
            } else if (distances[j] != INT_MAX) {
                sp[i][j] = distances[j];
            } else {
                sp[i][j] = -1; // no path between i and j
            }
        }
    }
}

void get_infection_scores(const std::vector<std::vector<std::pair<int, int>>>& network,
                          std::vector<float>& infection_scores) {
    int size = network.size();
    infection_scores.clear();
    infection_scores.resize(size);

    std::vector<std::vector<int>> sp(size, std::vector<int>(size, 0));
    find_SP(network, sp);

    int max_dist = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (sp[i][j] > max_dist) {
                max_dist = sp[i][j];
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (sp[i][j] == -1) {
                sp[i][j] = max_dist + 1;
            }
        }
    }

    for (int i = 0; i < size; ++i) {
        double ais = 0;
        for (int j = 0; j < size; ++j) {
            if (i != j && sp[i][j] != -1) {
                ais += sp[i][j];
            }
        }
        ais /= (size - 1);
        infection_scores[i] = 1.0f / ais;
    }
}

