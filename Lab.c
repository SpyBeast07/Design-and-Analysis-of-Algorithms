#include <stdio.h>
#include <math.h>

float euclid(float x1, float y1, float x2, float y2){
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

int main() {
    int n = 4;
    scanf("%d", &n);
    float pts[n][2];
    // float pts[4][2] = {{1, 2}, {3, 4}, {5, 6}, {7, 8}};
    int i = 0;
    while (n--) {
        scanf("%f", &pts[i][0]);
        scanf("%f", &pts[i][1]);
        i++;
    }

    float min_dis = INFINITY;
    float closest_p1x = 0;
    float closest_p1y = 0;
    float closest_p2x = 0;
    float closest_p2y = 0;

    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            float distance = euclid(pts[i][0], pts[i][1], pts[j][0], pts[j][1]);
            if (distance < min_dis) {
                min_dis = distance;
                closest_p1x = pts[i][0];
                closest_p1y = pts[i][1];
                closest_p2x = pts[j][0];
                closest_p2y = pts[j][1];
            }
        }
    }

    printf("Closest distance: %.6f \nClosest pair: (%.6f, %.6f) (%.6f, %.6f) \n", min_dis, closest_p1x, closest_p1y, closest_p2x, closest_p2y);
}