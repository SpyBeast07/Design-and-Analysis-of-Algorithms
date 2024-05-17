#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct point {
    int x, y;
};

float distance(struct point a, struct point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void closest_pair(struct point points[], int n) {
    float minimum_dist = distance(points[0], points[1]);
    struct point closest_pair[2] = {points[0], points[1]};

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            float current_dist = distance(points[i], points[j]);
            if (current_dist < minimum_dist) {
                minimum_dist = current_dist;
                closest_pair[0] = points[i];
                closest_pair[1] = points[j];
            }
        }
    }

    printf("Closest pair of points: (%d, %d) and (%d, %d)\n", closest_pair[0].x, closest_pair[0].y, closest_pair[1].x, closest_pair[1].y);
    printf("Minimum distance: %.2f\n", minimum_dist);
}

int main() {
    struct point points[] = {{1, 2}, {4, 6}, {7, 8}, {3, 5}, {9, 10}};
    int n = sizeof(points) / sizeof(points[0]);
    closest_pair(points, n);
    return 0;
}