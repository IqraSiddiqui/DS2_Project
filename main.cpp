#include"veb.cpp"

int main() {
	int nodes, edges, src, t, d;
	ifstream indata; // indata is like cin
   int num; // variable for input value
indata.open("testData.txt"); // opens the file
	nodes=5000;
	edges=5000;
	//nodes=9;
	//edges=14;
	src=0;

	vector< pair<int, int> > graph[nodes+1];
	vector<int> dist(nodes+1, INT_MAX);
	unordered_map<int, list<int> > distList;

	indata >> num;
	
   while ( !indata.eof() ) {
	   int i=0;
	   int a,b,w;
	   while(i<3){
		if(i==0)
			a=num;
		else if(i==1)
			b=num;
		else
			w=num;
		i=i+1;
		indata >> num; // sets EOF flag if no value found
	   }

		graph[a].push_back(make_pair(b, w));
		graph[b].push_back(make_pair(a, w));
   }
   indata.close();

	dist[src] = 0;
	distList[0].push_back(src);

	veb *root = new veb;
	root = create(root, 100);
	insert(root, 0, 10);

	d = 0;

	while(d != -1) {

		while(!distList[d].empty()) {
			int u = distList[d].front();
			distList[d].pop_front();

			for(int i = 0; i < graph[u].size(); i++) {
				pair<int, int> info = graph[u][i];

				int v = info.first;

				int w = info.second;

				if(dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					insert(root, dist[v], 8);
					distList[dist[v]].push_back(v);
				}
			}
		}

		d = successor(root, d);
	}
	
	int destination=0;
	int n=dist[2];
	for(int i = 0; i < dist.size() - 1; i++) {
		if (dist[i]<n && n!=0 && dist[i]!=0){
			destination=i;
			n=dist[i];
		}	
	}
	cout << "\nNearest Destination from Source: "<<src<<" is : "<<destination<<endl;
	return 0;
   }