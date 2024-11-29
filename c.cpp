#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;
};

struct Polygon {
    int numSides;
    vector<Point> vertices;
};

// Function to compare two points for lexicographical order
bool comparePoints(const Point& p1, const Point& p2) {
    return p1.x == p2.x ? p1.y < p2.y : p1.x < p2.x;
}

// Normalize the polygon: rotate so the smallest lexicographical point is first
vector<Point> normalizePolygon(const Polygon& p) {
    vector<Point> normalized(p.vertices.begin(), p.vertices.end());
    int minIdx = 0;
    for (int i = 1; i < p.numSides; ++i) {
        if (comparePoints(normalized[i], normalized[minIdx])) {
            minIdx = i;
        }
    }
    // Rotate the polygon to start from the lexicographically smallest point
    rotate(normalized.begin(), normalized.begin() + minIdx, normalized.end());
    return normalized;
}

// Function to check if two polygons are equal (ignoring rotation)
bool arePolygonsEqual(const Polygon& p1, const Polygon& p2) {
    if (p1.numSides != p2.numSides) return false;
    
    vector<Point> normP1 = normalizePolygon(p1);
    vector<Point> normP2 = normalizePolygon(p2);
    
    // Check if the polygons match considering rotation
    for (int i = 0; i < p1.numSides; ++i) {
        bool match = true;
        for (int j = 0; j < p1.numSides; ++j) {
            if (normP1[j] != normP2[(i + j) % p1.numSides]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    
    return false;
}

int main() {
    int n;
    cin >> n;
    
    vector<Polygon> earrings(n);
    
    // Input earrings
    for (int i = 0; i < n; ++i) {
        cin >> earrings[i].numSides;
        earrings[i].vertices.resize(earrings[i].numSides);
        for (int j = 0; j < earrings[i].numSides; ++j) {
            cin >> earrings[i].vertices[j].x >> earrings[i].vertices[j].y;
        }
    }
    
    // Compare every pair of earrings to find the matching pair
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (arePolygonsEqual(earrings[i], earrings[j])) {
                cout << i + 1 << " " << j + 1 << endl;  // Output indices (1-based)
                return 0;  // Only one matching pair is expected, exit early
            }
        }
    }
    
    return 0;
}
