#include "processor.h"



processor::processor(int A1, int A2, int B1, int B2, rover& turtle, FrontCheck& check) {
	this->A1 = A1;
	this->A2 = A2;
	this->B1 = B1;
	this->B2 = B2;
	this->turtle = turtle;
  this->check = check;
}

processor::processor() {
    A1 = 0;
    A2 = 0;
    B1 = 0;
    B2 = 0;
}

/*void processor::route() {
  ofstream fr("rover.txt");
  ofstream a("alpha.txt");
  ofstream b("beta.txt");
  ofstream h("height.txt");
  int s = 0;
  int i = 63;
  for (int j = 64; j < 127; j++){
    fr << double(i * 10) / 128 << " " << double(j * 10) / 128 << " " << double(turtle.swamp.Pixel[i][j] * 10) / 128 << endl;
    a << s << " " << ((double(turtle.swamp.Pixel[i + 1][j] * 10) / 128) - (double(turtle.swamp.Pixel[i - 1][j] * 10) / 128)) / (double(5) / 32) << endl;
    b << s << " " << ((double(turtle.swamp.Pixel[i][j + 1] * 10) / 128) - (double(turtle.swamp.Pixel[i][j - 1] * 10) / 128)) / (double(5) / 32) << endl;
    h << s << " " << double(turtle.swamp.Pixel[i][j] * 10) / 128 << endl;
    s++;
  }
  std::cout << double(turtle.swamp.Pixel[40][64] * 10) / 128 << std::endl;

  std::cout << check.Function(40, 64, 1, 0) << std::endl;
}*/



void processor::route() {
	ofstream fr("rover.txt");
    int i, j, k, l, m;
    int n = 128 * 128;
    int s = A1 * 127 + A2;
    int t = B1 * 127 + B2;
    vector<vector<int>> adj(n);
    vector<int> dist(n, n);
    vector<int> p(n, -1);
    dist[s] = 0;
    queue<int> q;
    q.push(s);
    for (i = 0; i < 128; i++) {
        for (j = 0; j < 128; j++) {
            for (k = i - 1; k < i + 2; k++) {
                for (l = j - 1; l < j + 2; l++) {
                    if (k > 0 && k < 128 && l > 0 && l < 128 && !(k == i && l == j)) {
                        if (turtle.sensor(i, j, k, l) && turtle.angles(i, j, k, l)) {
                            m = 127 * i + j;
                            adj[m].push_back(127 * k + l);
                        }
                    }
                }
            }
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : adj[v]) {
            if (dist[u] > dist[v] + 1) {
                p[u] = v;
                dist[u] = dist[v] + 1;
                q.push(u);
            }
        }
    }
    if (dist[t] == n) {
        cout << "Не удалось построить маршрут от точки А до точки В" << endl;
    }
    vector<int> path;
    while (t != -1) {
        path.push_back(t);
        t = p[t];
    }
    for (i = path.size() - 1; i > -1; i--) {
        
        k = path[i] / 127;
        l = path[i] % 127;
        fr << double(k * 10) / 128 << " " << double(l * 10) / 128 << " " << double(turtle.swamp.Pixel[k][l] * 10) / 128 << endl;
    }
}