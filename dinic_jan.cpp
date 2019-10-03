#include <iostream>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <chrono>
using namespace std;
using namespace std::chrono; 


typedef struct
{
	int u, v, cap, flow, rev;				//definied a struct for edges with a parameter for its reverse edge 

	}edge;

class graph
{
	int n;
	int s,t;
	int *level;
	vector<edge*> *adj; //pointer to an array of vertices as integers containg adjacency vector of outgoing edges

public:



	graph(int n)
	{
		s=0; t=n-1;
		this->n=n;
		adj= new vector<edge*>[n];	
		
		level=new int[n];
	}
	void addEdge(int u,int v,int cap)
	{
		edge *a;
		a= new edge;
		a->u=u;
		a->v=v;
		a->flow=0;
		a->cap=cap;
		a->rev=adj[v].size();
		
		edge *b;
		b= new edge;
		b->u=v;
		b->v=u;
		b->flow=0;
		b->cap=0;
		b->rev=adj[u].size();
		adj[a->u].push_back(a);
		adj[b->u].push_back(b);

	}
	bool isMember(int u, int v)
	{
		vector<edge*>:: iterator i;
		for(i=adj[u].begin(); i != adj[u].end(); i++)
		{
			edge *e1;
				e1=*i;
				if(e1->v==v) 
				{
					return true;
				}
				else return false;
		}

	}

	void printGraph()
	{
		vector<edge*>:: iterator it;
		for(int i=0; i<n; i++)
		{
			cout << "vertex " << i << ": ";
			//list<edge>::iterator<edge> it;
			for(it=adj[i].begin(); it!=adj[i].end(); ++it) 
			{
				edge *e;
				e=*it;
				cout << e->v << ", cap- "<< e->cap<< endl;
			}

			cout << endl;
		}
	}

	bool BFS()
	{
		for(int i=0;i<n;i++)
			level[i]= -1;
		level[s]=0;
		list<int> q;
		q.push_back(s);
		vector<edge*>:: iterator i;
		while(!q.empty())
		{
			int curr= q.front();
			q.pop_front();
			for(i=adj[curr].begin(); i != adj[curr].end(); i++)
			{
				edge *e1;
				e1=*i;
				if((level[e1->v]==-1) && (e1->cap>e1->flow))
				{
					level[e1->v]= level[curr]+1;
					//cout<< level[e1->v]<<" level of "<< e1->v<<endl;
					q.push_back(e1->v);
				}
			}
		}
		if(level[n-1]==-1)
			return false;
		else return true;		
	};

	int sendFlow(int u, int flow)
	{

		//cout <<"path- "<< u<< endl;
		int curr_flow;
		if(u==t) return flow;
		vector<edge*>:: iterator i;
		for(i=adj[u].begin(); i != adj[u].end(); i++)
		{
			edge *e2;
			e2=*i;
			if (level[e2->v] == level[u]+1 && e2->flow < e2->cap)
			{
				if(flow<e2->cap-e2->flow)
					curr_flow=flow;
				else curr_flow=e2->cap-e2->flow;
				int temp_flow =sendFlow(e2->v, curr_flow);

				if(temp_flow > 0)
				{	//cout <<"check8"<< endl;
					e2->flow=e2->flow+temp_flow;
					adj[e2->v][e2->rev]->flow -= temp_flow; 
				//	cout <<"flow of "<< u<< "is "<<e2->flow << endl;

					return temp_flow;


				}
			}
		}
		return 0;
	}

	int dinicMaxFlow()
	{	
		//int INT_MAX;
	 	if(n==0) return -1;
	 	int total =0;
  
    // Augment the flow while there is path 
    // from source to sink 
    while (BFS() == true) 
    { 
        // store how many edges are visited 
        // from V { 0 to V } 
       // int *start = new int[V+1]; 
  
        // while flow is not zero in graph from S to D 
        while (int flow = sendFlow(0, INT_MAX))
        {
        	 // Add path flow to overall flow 
            total += flow;
            //cout<<flow<<endl; 

        }
    } 
  
    // return maximum flow 
    return total; 
	}


	};

	// int main() {
	// // { 
	// //     graph g(6); 

	// //     g.addEdge(0,1,10);

	// //     g.addEdge(0,2,10);

	// //     g.addEdge(1,2,2);
	// //     g.addEdge(1,4,8);
	// //     g.addEdge(1,3,4);
	// //     g.addEdge(2,4,9);

	// //     g.addEdge(4,3,6);

	
	// //     g.addEdge(3,5,10);

	  	
	// //     g.addEdge(4,5,10);
	// int n,m;

	// int cap;

	// srand (time(NULL));
	// cout << "Enter the number of vertices" <<endl;
	// cin >> n;

	// cout << "Enter the number of edges" <<endl;
	// cin >> m;

	// int u; int v;

	// clock_t t,time1;
	// //g.printGraph();
	// //auto start1 = high_resolution_clock::now();
	// 	//g.dinicMaxFlow();
	// //auto stop1 = high_resolution_clock::now();

	// //auto duration = duration_cast<microseconds>(stop1 - start1);


	// time1=clock();
	// time1=clock()-time1;

	// for(int i=0;i<50;i++)
	// {
	// 	graph g(n);


	// 	int f=0;
	// 	for(int i=0; i<m; i++)
	// 	{
	// 		do{
	// 			f=0;
	// 			u= rand()%n;
	// 			v= rand()%n;
	// 			bool res=g.isMember(u,v);
	// 			if(res==true) f=1;
		
	// 			// for(int j=0; j<i; j++)
	// 			// {
	// 			// 	if((u[j]==u[i] && v[j]==v[i])||(u[j]==v[i] && v[j]==u[i])) 
	// 			// 	{
	// 			// 		f=1; break;
	// 			// 	}
	// 			// }

	// 		}while((u==v) || f==1);

	// 		cap= (rand()%50)+1;
	// 		g.addEdge(u, v, cap);
	// 		//cout << "edge is btw - " <<u[i]<< ", "<< v[i] <<endl;	

	// 	}
	// 	t = clock();
	// 	//cout << "Maximum flow " << g.dinicMaxFlow()<<endl;
	// 	g.dinicMaxFlow();
	// 	t=clock()-t;
	// 	time1 = time1+t;
	// 	//cout<<"time "<<((float)t/CLOCKS_PER_SEC)<<endl;

	// }


	// //g.printGraph();

 //    //cout << "Maximum flow " << g.dinicMaxFlow(); 
 //   // cout<<" total time"<< duration.count()/100;
 // cout<<"time "<<((float)time1/100/CLOCKS_PER_SEC)<<endl;
    
 //    return 0; 
	// }



	int main() 
{ 
   //  graph g(6); 

   //  g.addEdge(0,1,10);

   //  g.addEdge(0,2,10);

   //  g.addEdge(1,2,2);

   //  g.addEdge(2,4,9);
  
   //  g.addEdge(1,4,8);
    
   //  g.addEdge(1,3,4);

   //  g.addEdge(4,3,6);

  	// g.addEdge(3,5,10);

   //  g.addEdge(4,5,10);

//	long int rand(void);
	long int n,m;

	long int cap;

	float t[1000];
	//clock_t t, time_;
	//time_=clock();
	//time_=clock()-time_;
	//srand (time(NULL));
	cout << "Enter the number of rows" <<endl;
	cin >> m;
	//n=rand();

	cout << "Enter the number of columns" <<endl;
	cin >> n;
	//m=rand()%(n*(n-1)/2);

	int u; int v;

//	int t=(n(n-1)/2);
//	m= m%t; //to make sure the input is compatible
	auto start1 = high_resolution_clock::now();
	// 	//g.dinicMaxFlow();
	 auto stop1 = high_resolution_clock::now();

	 auto duration = duration_cast<microseconds>(stop1 - start1);


	for(int k=0;k<10;k++)
	{


	graph g(m*n);

	for( int i=0;i<m;i++){
			for(int j=0;j<n-1;j++){
				cap= (rand()%100)+1;
				g.addEdge(i*n+j,i*n+j+1, cap);
				//cout<<"what why1"<<endl;
				cap= (rand()%100)+1;
				g.addEdge(i*n+j+1,i*n+j, cap);
			}
		}

	for( int i=0;i<n;i++){
		for(int j=0;j<m-1;j++){
			cap= (rand()%100)+1;
			//cout<<"what why2"<<endl;
			g.addEdge(i*m+j,i*m+j+1, cap);
			cap= (rand()%100)+1;
			g.addEdge(i*m+j+1,i*m+j, cap);
		}
	}
 //cout<<"what why"<<endl;








    auto start = high_resolution_clock::now();
	//t=clock();
	//cout << "Maximum flow "<< g.maxflow()<<endl; 
	g.dinicMaxFlow();
	//t= clock()-t;
	//time_=time_+t;
		auto stop = high_resolution_clock::now();
		duration =  duration + duration_cast<microseconds>(stop - start);
		t[k]= (duration_cast<microseconds>(stop - start)).count();
}

	float dur = duration.count()/10;
	// float d=0;
	// float dev=0;
	// for(int i=0; i<1000; i++)
	// {
	// 	d=(dur-t[i]);
	// 	//cout<<"d "<< d << endl;
	// 	dev= d*d + dev;
	// 	//cout<<"dev"<< dev << endl;
	// }

	// dev= sqrt(dev/1000);

	// 	cout << "deviation time "<<dev<<endl;
		cout<<" average time "<< dur;
   
    return 0; 
}