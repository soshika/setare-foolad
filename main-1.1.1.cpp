#include <bits/stdc++.h>

using namespace std;

#define clr(a, val)  memset(a, val, sizeof a)

typedef pair<int, int> pii;

const int MAX = 100;

int width; 
int rod_size ;
int throwing_space_lower, throwing_space_upper;  

vector <pii> rods;
set <vector<int>> areas;

bool is_square(int x, int y) {
  return x == y;
}

int area(int x, int y) {
  if (is_square(x, y)) {
    return 4 * x;
  }
  return 2 * (x + y);
}

void show(int pos, vector <int> a) {
  cout << "state when index is : " << pos << endl;
  for(int i = 0 ; i < a.size() ; ++i) {
    cout << a[i] << ' ' ;
  }
  cout << "\n------------------------------------\n";
}

void BT(int pos, vector <int> pick) {
  areas.insert(pick);
  if(pos == rod_size) {
    return ;
  }
  int count = width / area(rods[pos].first, rods[pos].second);
  for(int j = 0 ; j <= count ; ++j) {
    for(int k = 0 ; k <= j ; ++k) {
      int ar = area(rods[pos].first, rods[pos].second)-2;
      pick.push_back(ar);
    }
    BT(pos+1, pick);
    for(int k = 0 ; k <= j ; ++k) {
      pick.pop_back();
    }  
  }
}

int main() {
  
  cin >> width;
  cin >> throwing_space_lower >> throwing_space_upper ;

  cin >> rod_size ;
  for(int i = 0 ; i < rod_size ; ++i) {
    int x, y ; cin >> x >> y;
    rods.push_back(make_pair(x, y));
  }

  vector <int> a ;
  BT(0, a);

  vector <vector<int> > best ;
  for (auto i : areas){
      vector <int> state = i;
      int sum = 0 ;
      for(int j = 0 ; j < state.size() ; ++j) {
        sum += state[j];
      }
      if(width - sum > throwing_space_upper or width - sum < throwing_space_lower) continue;
      best.push_back(state);
  }

  cout << "Answer is : \n";
  for(int i = 0 ; i < best.size() ; ++i){
    cout << i+1 << ' ' ;
    for(int j = 0 ; j < best[i].size() ; ++j) {
      cout << best[i][j] << ' ';
    }
    cout << "\n-----------------------------\n";
  }

  return 0;
}