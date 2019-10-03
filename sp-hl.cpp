#include <iostream>
#include <list>
#include <stdlib.h>
#include <time.h>
#include <chrono>
using namespace std;
using namespace std::chrono; 

using namespace std;
//using namespace std::chrono; 

typedef struct
{
	int u, v, cap, flow, re;
	 //stores index of reverse edge in adj[v] list
	}edge;

class graph
{
	int n;
	int s,t;
	

	list<edge> *adj; //pointer to an array of vertices as integers containg adjacency list of outgoing edges

public:
	graph(int n)
	{
		s=0; t=n-1;
		this->n=n;
		//this->m=m;
		adj= new list<edge>[n];	
	}

	void addEdge(int u, int v, int cap)
	{
		int p=adj[v].size();
		int q=adj[u].size();
		edge  a{u, v, cap, 0,p }; 
		edge  b{v, u, 0, 0, q}; 
		
		adj[u].push_back(a);
	//	re.u=e.v; re.v=e.u; re.cap=0; re.flow=0;
		adj[v].push_back(b);
	}
	bool isMember(int u, int v)
	{
		list<edge>::iterator i;
		for(i=adj[u].begin(); i != adj[u].end(); i++)
		{
			edge &e1=*i;
				if(e1.v==v) 
				{
					return true;
				}
				else return false;
		}
		return false;
	}

	/*void printGraph()
	{
		for(int i=0; i<n; i++)
		{
			cout << "vertex " << i << ": ";
			list<edge>::iterator<edge> it;
			for( it=adj[i].begin(); it!=adj[i].end(); ++it) /////////////////////check the error of ++
			{
				cout << it->v << ", cap- "<< it->cap<< endl;
			}

			cout << endl;
		}
	}*/

	int maxflow()
	{
		int f=0;
		float t[100];
		edge **visited = new edge*[n];
		
		do{
		
		//cout<<"1" <<endl;
		list<int> q;
		q.push_back(0);


//cout<<"3" <<endl;
		for(int i=0; i<n; i++)
		{	visited[i]= new edge;
			visited[i]->u=-1;
		}

		visited[0]->u=n;

		int flag=0;
		list<edge>::iterator i;
		//cout<<"4" <<endl;
		while(!q.empty() && flag==0)
		{
			int curr= q.front();
			q.pop_front();

			//cout<<"curr" << curr<<endl;
			for(i=adj[curr].begin(); i != adj[curr].end(); i++)
			{
				edge &e1= *i;

//cout<<"e1.flow" <<e1.flow<<endl;

				if((visited[e1.v]->u==-1) && (e1.cap>0))
				{
					//cout<<"6" <<endl;
					visited[e1.v] = &e1;
					//cout<<"7" <<endl;
					q.push_back(e1.v);
//cout<<"pushed"<<e1.v <<endl;

					if(e1.v==n-1){
						flag=1;
					 	break;  //sink found
					}
				}
			}
		}
	//	cout<<"3" <<endl;

		if(visited[n-1]->u!=-1)
		{
			int temp=visited[n-1]->cap;
			edge *e2;
			for( e2=visited[n-1]; e2->u!=n;e2=visited[e2->u])
			{
				//edge &e2= 
				if(temp>e2->cap-e2->flow)
					temp=e2->cap-e2->flow;
				// we founbd bottleneck capacity
//cout<<"4" <<endl;

			}
			//cout<<"value of bottleneck" << temp<<endl;
			//augment all the edges
			edge *e3;
			for(e3=visited[n-1]; e3->u!=n;e3=visited[e3->u])
			{
				//edge *E=&e2;
				//e3->flow=e3->flow+temp;
				e3->cap=e3->cap-temp;
				list<edge> :: iterator it;
				it=adj[e3->v].begin();
				for(int t=0; t<e3->re; t++)
				 it++;
				it->cap= it->cap+temp;
//cout<<"5" <<endl;

			}
			f=f+temp;
		}

	}while(visited[n-1]->u!=-1);

	return f;
	}
};

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

	//clock_t t, time_;
	//time_=clock();
	//time_=clock()-time_;
	//srand (time(NULL));
	cout << "Enter the number of vertices" <<endl;
	cin >> n;
	//n=rand();

	cout << "Enter the number of edges" <<endl;
	cin >> m;
	//m=rand()%(n*(n-1)/2);

	int u; int v;

//	int t=(n(n-1)/2);
//	m= m%t; //to make sure the input is compatible
	auto start1 = high_resolution_clock::now();
	// 	//g.dinicMaxFlow();
	 auto stop1 = high_resolution_clock::now();

	 auto duration = duration_cast<microseconds>(stop1 - start1);


	for(int j=0;j<1;j++)
	{



	graph g(n);


	int f=0;
	for(long int i=0; i<m; i++)
	{
	//cout << "1" << endl;
		do{
			f=0;
			u= rand()%(n-1);
			v= (rand()%(n-1))+1;
			bool res=g.isMember(u,v);
				if(res==true) f=1;
		
			
			//if(u[i]==n-1) u[i]=u[i]-1;
	
			// for(int j=0; j<i; j++)
			// {
			// 	if((u[j]==u[i] && v[j]==v[i]) || (u[j]==v[i] && v[j]==u[i])) 
			// 	{
				
			// 		f=1; break;
			// 	}
			// }

		}while((u==v) || f==1);

		cap= (rand()%100)+1;
		g.addEdge(u, v, cap);
	//	cout << "edge is btw - " <<u[i]<< ", "<< v[i] << "cap= "<< cap<< endl;	
		
	}

//	g.printGraph();


    auto start = high_resolution_clock::now();
	//t=clock();
	cout << "Maximum flow "<< g.maxflow()<<endl; 
	//t= clock()-t;
	//time_=time_+t;
		auto stop = high_resolution_clock::now();
		duration =  duration + duration_cast<microseconds>(stop - start);
		t[j]= (duration_cast<microseconds>(stop - start)).count();
}

	float dur = duration.count()/1;
	float d=0;
	for(int i=0; i<100; i++)
	{
		d=(dur-t[i]);
		//cout<<"d "<< (float)d/CLOCKS_PER_SEC<< endl;
		dev= d*d + dev;
	}

	dev= sqrt(dev/100);

		cout << "deviation time "<<dev<<endl;
		cout<<" average time"<< dur;
   
    return 0; 
}