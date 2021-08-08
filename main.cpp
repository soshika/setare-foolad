#include <bits/stdc++.h>

using namespace std;

#define clr(a, val)  memset(a, val, sizeof a)

typedef pair<int, int> pii;

const int MAX = 100;

int width; 
int throwing_space;  
int rod_sizes ;
vector <pii> rods;

bool is_square(int x, int y) {
  return x != y;
}

int area(int x, int y) {
  if (is_square(x, y)) {
    return 4 * x;
  }
  return 2 * (x + y);
}

pii calculate() {

  int len = rods.size();
  for(int i = 0 ; i < len ; ++i) {
    cout << rods[i].first << ' ' << rods[i].second << endl;
  }
  cout << "-------------------------------\n";
  int ret = 0;
  int best = 0;
  for(int i = 0 ; i < 1 << len ; ++i) {
    int temp = 0;
    for(int j = 0 ; j < len ; ++j) {
      if(i & (1 << j)) {
        temp += area(rods[j].first, rods[j].second);
        temp -= 4;
      }
    }
    if(temp <= width) {
      if(ret < temp) {
        ret = temp;
        best = i;
      }
    }
  }
  cout << "answer is :        " << ret << ' ' << best << endl;
  return make_pair(ret, best);
}

void delete_exclusive(vector <pii> exclusive) {
  vector <pii> real ;
  for(int i = 0 ; i < rods.size() ; ++i){
    int ind = -1;
    for(int j = 0 ; j < exclusive.size() ; ++j) {
      if(rods[i] == exclusive[j]) {
        ind = j ;
        break;
      }
    }
    if(ind == -1) {
      real.push_back(rods[i]);
    }
  }
  rods = real;
}

void delete_inclusive(vector <pii> inclusive) {
  vector <pii> real;
  for(int i = 0 ; i < rods.size() ; ++i) {
    int ind = -1;
    for(int j = 0 ; j < inclusive.size() ; ++j) {
      if(rods[i] == inclusive[j]) {
        ind = j;
        break;
      }
    }
    if(ind == -1){
      real.push_back(rods[i]);
    }
  }
  rods = real;
}

int main() {
  cin >> width;
  cin >> throwing_space;

  // first we should imagine we have width = width - throwing_space
  width -= throwing_space;

  cin >> rod_sizes ;
  for(int i = 0 ; i < rod_sizes ; ++i) {
    int x, y ; 
    cin >> x >> y;
    rods.push_back(make_pair(x, y));
  }

  vector <pii> inclusive_rods ;
  vector <pii> exclusive_rods ;

  int inclusive, exclusive;
  cin >> inclusive ;
  for(int i = 0 ; i < inclusive ; ++i) {
    int x, y ; cin >> x >> y;
    inclusive_rods.push_back(make_pair(x, y));
  }

  cin >> exclusive ;
  for(int i = 0 ; i < exclusive ; ++i) {
    int x, y ; cin >> x >> y ;
    exclusive_rods.push_back(make_pair(x, y));
  }

  delete_exclusive(exclusive_rods);
  delete_inclusive(inclusive_rods);

  vector<pii> best_rods ;

  int sum = 0;
  for(int i = 0 ; i < inclusive_rods.size() ; ++i) {
    sum += area(inclusive_rods[i].first, inclusive_rods[i].second) - 4;
  }

  width -= sum;

  pii ans = calculate();
  ans.first += sum;
  for(int i = 0 ; i < inclusive_rods.size() ; ++i) {
    ans.second = ans.second | (1 << (i+rods.size()));
  }

  cout << "output" << endl;
  cout << "answer is : " << ans.first << endl;
  for(int i = 0 ; i < inclusive_rods.size() ; ++i) {
    cout << inclusive_rods[i].first << ' ' << inclusive_rods[i].second << endl;
  }

  for(int i = 0 ; i < rods.size() ; ++i) {
    if(ans.second & (1 << i)) {
      cout << rods[i].first << ' ' << rods[i].second << endl;
    }
  }
  
  return 0;
}
