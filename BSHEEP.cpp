// Problem link: http://www.spoj.com/problems/BSHEEP/

#include <stdlib.h>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <list>
using namespace std;

struct Point {
  long int x, y, index;
} points[100005];

Point p0;

long int nextToTop(list<long int> &S) {
  long int p = S.back();
  S.pop_back();
  long int res = S.back();
  S.push_back(p);
  return res;
}

void swap(Point &p1, Point &p2) {
  Point temp = p1;
  p1 = p2;
  p2 = temp;
}

long int distSq(Point p1, Point p2) {
  return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}
int orientation(Point p, Point q, Point r) {
  long int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

  if (val == 0) return 0;    // colinear
  return (val > 0) ? 1 : 2;  // clock or counterclock wise
}

int compare(const void *vp1, const void *vp2) {
  Point *p1 = (Point *)vp1;
  Point *p2 = (Point *)vp2;

  int o = orientation(p0, *p1, *p2);
  if ((*p1).x == (*p2).x && (*p1).y == (*p2).y){
      return (*p2).index >= (*p1).index? 1 : -1;
  }
  if (o == 0) {
    return (distSq(p0, *p2) >= distSq(p0, *p1)) ? -1 : 1;
  }
  return (o == 2) ? -1 : 1;
}

void convexHull(int n) {
  long int ymin = points[0].y, min = 0;
  for (long int i = 1; i < n; i++) {
    long int y = points[i].y;

    if ((y < ymin) || (ymin == y && points[i].x < points[min].x) || 
      (ymin == y && points[i].x == points[min].x && points[min].index < points[i].index)) {
      ymin = points[i].y, min = i;
    }
  }

  swap(points[0], points[min]);
  p0 = points[0];
  qsort(&points[1], n - 1, sizeof(Point), compare);

  // removing duplicate points
  long int len = 0;
  for (long int i = 0; i < n; i++) {
    while (i < n - 1 && points[i].x == points[i+1].x && points[i].y == points[i+1].y) i++;
    points[len] = points[i];
    len++;
  }

  long int m = 1;
  for (long int i = 1; i < len; i++) {
    while (i < len - 1 && orientation(p0, points[i], points[i + 1]) == 0) i++;

    points[m] = points[i];
    m++;
  }

  if (m == 1) {
    cout << "0.00" << endl;
    cout << 1 << endl << endl;
    return;
  } else if (m == 2) {
    cout << fixed << setprecision(2) << 2 * sqrt(distSq(points[0], points[1])) << endl;
    cout << points[0].index + 1 << " " << points[1].index  + 1 << endl << endl;
    return;
  }

  list<long int> S;
  S.clear();
  S.push_back(0);
  S.push_back(1);
  S.push_back(2);

  for (long int i = 3; i < m; i++) {
    while (orientation(points[nextToTop(S)], points[S.back()], points[i]) != 2)
      S.pop_back();
    if (i != S.back())
      S.push_back(i);
  }

  double distance = sqrt(distSq(points[S.front()], points[S.back()]));
  for (auto itr = S.begin(), ptr = S.begin(); ++ptr != S.end(); itr++)
    distance += sqrt(distSq(points[*itr], points[*ptr]));

  cout << fixed << setprecision(2) << distance << endl;
  for (auto ritr = S.begin(); ritr != S.end(); ritr++)
    cout << points[*ritr].index + 1 << " ";

  cout << "\n\n";
}

// Driver program to test above functions
int main() {
  int test;
  long int num;
  cin >> test;
  while (test--) {
    cin >> num;
    for (long int i = 0; i < num; i++) {
      cin >> points[i].x;
      cin >> points[i].y;
      points[i].index = i;
    }
    convexHull(num);
  }
  return 0;
}
