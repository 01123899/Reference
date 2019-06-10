#include <bits/stdc++.h>
using namespace std;


/**
  Graph:
      representation of a graph unweighted
      with an adjacent list

  Considerations:
      1-based indexing
**/
class Graph{
private:
  int vertices;
  int edges;
  bool directed;
  vector< vector<int> > adj;

public:
  // 1-base indexing
  Graph(int vertices,bool directed = false){
    this->directed = directed;
    this->vertices = vertices;
    adj.assign(vertices + 1, vector<int>());
  }

  // 1-based indexing
  void add_edge(int u,int v){
    edges++;
    adj[u].push_back(v);
    if(directed == false)
      adj[v].push_back(u);
  }
  bool get_directed(){
    return directed;
  }
  int get_vertices(){
    return vertices;
  }
  int get_edges(){
    return edges;
  }
  
  friend bool find_cycles(Graph &);
  friend bool find_cycles(Graph &,int,vector<int>&,vector<int>&,bool );


  friend vector<int> topological_sort(Graph&);
  friend void topological_sort(Graph &,int,vector<int> &,vector<int> &);



  friend vector<pair<int,int>> bridges(Graph &g);
  friend void bridges(Graph &, int,vector<int> &,int &,vector<int> &,vector<int> &,
                      vector<int> &,vector<pair<int,int>> &);


  friend vector<int> articulation_points(Graph &);
  friend void  articulation_points(Graph &,int ,int,int &,vector<int> &,int &,vector<int> &,
                                  vector<int> &,vector<int> &,vector<bool> &);

};


// 1-based indexing
/* Find cycles in a directed or undirected graph
   O (vertices + edges)
*/
enum {UNDISCOVERED = -1,DISCOVERED = 1, PROCESSED = 2 };
bool find_cycles(Graph &g){
  vector<int> parent(g.vertices+1,-1);
  vector<int> state(g.vertices+1,UNDISCOVERED);
  bool cycle = false;
  for(int u=1;u<=g.vertices;u++){
    if(state[u] == UNDISCOVERED && cycle == false){
      parent[u] = u;
      cycle = cycle || find_cycles(g,u,parent,state,g.directed);
    }
  }
  return cycle;
}

bool find_cycles(Graph &g,int u,vector<int> &parent,vector<int> &state,bool is_directed){
  state[u] = DISCOVERED;
  bool cycle = false;
  for(auto &v: g.adj[u]){
    if(state[v] == UNDISCOVERED){
      parent[v] = u;
      cycle = cycle || find_cycles(g,v,parent,state,is_directed);
    }else if(is_directed){
      cycle = (state[v] == DISCOVERED) ? true : cycle;
    }else if(parent[u] != v){
      cycle = true;
    }
  }
  state[u] = PROCESSED;
  return cycle;
}






/**Topological sort
  The graph has to be a DAG (first check cycles)
  only return one Topological Sort
  O(vertices + edges)
*/
vector<int>  topological_sort(Graph &g){
  vector<int> Stack;
  vector<int> state(g.vertices+1,UNDISCOVERED);
  for(int u=1;u<=g.vertices;u++){
    if(state[u] == UNDISCOVERED){
      topological_sort(g,u,Stack,state);
    }
  }
  reverse(Stack.begin(),Stack.end());
  return Stack;
}

void topological_sort(Graph &g,int u, vector<int> &Stack,vector<int> &state){
  state[u] = DISCOVERED;
  for(auto &v: g.adj[u]){
    if(state[v] == UNDISCOVERED){
      topological_sort(g,v,Stack,state);
    }
  }
  Stack.push_back(u);
}




/*Articulation points
  Tarjan algorithm, undirected graphs
  O(vertices + edges)
**/
vector<int> articulation_points(Graph &g){
  vector<int> reach_ancestor(g.vertices + 1, 0);
  vector<int> parent(g.vertices + 1,0);
  vector<int> state(g.vertices + 1,UNDISCOVERED);
  vector<int> time_entry(g.vertices+1,0);
  vector<bool> art_points(g.vertices+1,false);

  int t = 1;
  for(int u = 1; u <= g.vertices; u++){
    if(state[u] ==  UNDISCOVERED){
      int children = 0;
      articulation_points(g,u,u,children,time_entry,t,reach_ancestor,parent,state,art_points);
    }
  }

  vector<int> ans;
  for(int u = 1;u<=g.vertices;u++){
    if(art_points[u] == true){
      ans.push_back(u);
    }
  }
  return ans;
}

void articulation_points(Graph &g, int u,int root,int &children,vector<int> &time_entry,int &t,
  vector<int> &reach_ancestor,vector<int> &parent,vector<int> &state,vector<bool> &art_points){
  state[u] = DISCOVERED;
  time_entry[u] = t++;
  reach_ancestor[u] = u;
  for(auto &v : g.adj[u]){
    if(state[v] == UNDISCOVERED){
      parent[v] = u;
      articulation_points(g,u,root,children,time_entry,t,reach_ancestor,parent,state,art_points);

      // spetial case
      if(u == root)
        children++;
      if(children > 1)
        art_points[u] = true;


      // try to reach a lower ancestor
      if(time_entry[reach_ancestor[u]] > time_entry[reach_ancestor[v]]){
        reach_ancestor[u] = reach_ancestor[v];
      }

      // check if u is an articulation point
      if(time_entry[reach_ancestor[v]]<=time_entry[u] && u != root){
        art_points[u] = true;
      }

    }else if(parent[u] != v){
      // the only way to reach an ancestor is with a back edge
      if(time_entry[v]<time_entry[reach_ancestor[u]]){
        reach_ancestor[u] = v;
      }
    }
  }
}









/*Bridges
  Tarjan algorithm, undirected graphs
  O(vertices + edges)
**/
vector<pair<int,int>> bridges(Graph &g){
  vector<int> reach_ancestor(g.vertices + 1, 0);
  vector<int> parent(g.vertices + 1,0);
  vector<int> state(g.vertices + 1,UNDISCOVERED);
  vector<int> time_entry(g.vertices+1,0);
  vector< pair<int,int> > ans;

  int t = 1;
  for(int u = 1; u <= g.vertices; u++){
    if(state[u] ==  UNDISCOVERED){
      bridges(g,u,time_entry,t,reach_ancestor,parent,state,ans);
    }
  }

  return ans;
}

void bridges(Graph &g, int u,vector<int> &time_entry,int &t,vector<int> &reach_ancestor,
                        vector<int> &parent,vector<int> &state,vector<pair<int,int>> &ans){
  state[u] = DISCOVERED;
  time_entry[u] = t++;
  reach_ancestor[u] = u;
  for(auto &v : g.adj[u]){
    if(state[v] == UNDISCOVERED){
      parent[v] = u;
      bridges(g,u,time_entry,t,reach_ancestor,parent,state,ans);

      // try to reach a lower ancestor
      if(time_entry[reach_ancestor[u]] > time_entry[reach_ancestor[v]]){
        reach_ancestor[u] = reach_ancestor[v];
      }

      // check if u,v is a bridge
      if(time_entry[reach_ancestor[v]] < time_entry[u]){
        ans.push_back(make_pair(u,v));
      }

    }else if(parent[u] != v){
      // the only way to reach an ancestor is with a back edge
      if(time_entry[v]<time_entry[reach_ancestor[u]]){
        reach_ancestor[u] = v;
      }
    }
  }
}


int main(){
  return 0;
}
