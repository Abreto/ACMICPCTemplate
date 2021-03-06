struct edges {
  int to,next;
  bool cut,visit;
  int from;
} edge[MAXN-1<<1];
int head[MAXN],low[MAXN],dfn[MAXN],L;
bool visit[MAXN],cut[MAXN];
void init(int n) {
  L=0;
  memset(head,-1,4*n);
  memset(cut,0,4*n);
  memset(visit,0,4*n);
}
void add_edge(int u,int v) {
  edge[L].from=u;
  edge[L].cut=edge[L].visit=0;
  edge[L].to=v;
  edge[L].next=head[u];
  head[u]=L++;
}
int idx;
void dfs(int u,int fu) {
  visit[u]=1;
  low[u]=dfn[u]=idx++;
  int tot=0;
  for (int i=head[u]; i!=-1; i=edge[i].next) {
    int v=edge[i].to;
    if (edge[i].visit)
      continue;
    edge[i].visit=edge[i^1].visit=1;
    if (visit[v]) {
      low[u]=dfn[v]>low[u]?low[u]:dfn[v];
      continue;
    }
    dfs(v,u);
    edge[i].cut=edge[i^1].cut=low[v]>dfn[u] || edge[i].cut;
    if (u!=fu) cut[u]=low[v]>=dfn[u]?1:cut[u];
    low[u]=low[v]>low[u]?low[u]:low[v];
    tot++;
  }
  if (u==fu && tot>1) cut[u]=1;
}
int main() {
  int t;
  scanf("%d",&t);
  while (t--) {
    int n,m;
    scanf("%d%d",&n,&m);
    init(n);
    for (int i=0; i<m; i++) {
      int u,v;
      scanf("%d%d",&u,&v);
      add_edge(--u,--v);
      add_edge(v,u);
    }
    for (int i=0; i<n; i++)
      if (!visit[i]) {
        idx=0;
        dfs(i,i);
      }
  }
  return 0;
}

