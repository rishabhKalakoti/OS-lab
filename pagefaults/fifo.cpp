#include<bits/stdc++.h>
using namespace std;
#define MAX_PAGES 10
int main()
{
	// fifo
	int i,flag;
	int c;
	int size=0;
	vector<int>Q;
	int hit=0;
	int miss=0;
	while(1)
	{
		cout<<"Enter the required page number. Enter -1 to exit."<<endl;
		cin>>c;
		if(c==-1)
		{
			cout<<"Terminating the program..."<<endl;
			break;
		}
		flag=0;
		for(i=0;i<Q.size();i++)
		{
			if(Q[i]==c)
			{
				flag=1;
				hit++;
				cout<<"Hit."<<endl;
				break;
			}
		}
		if(flag==0)
		{
			miss++;
			cout<<"Miss."<<endl;
			if(Q.size()>=MAX_PAGES)
			{
				cout<<"Removed "<<Q[0]<<" from queue."<<endl;
				Q.erase(Q.begin());
			}
			cout<<"Added "<< c <<" to queue."<<endl;
			Q.push_back(c);
		}
		cout<<"Queue: ";
		for(i=0;i<Q.size();i++)
		{
			cout<<Q[i]<<" ";
		}
		cout<<endl;
	}
	cout<<"Hit ratio is "<<(hit*1.0)/(hit+miss)<<"."<<endl;
	return 0;
}
