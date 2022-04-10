#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct process{
	int id, arvtime, bsttime, cpttime, tat, wt;
};
vector<process> inputNProcess(int n){
	vector<process> pro(n);
	for(int i=0;i<n;i++){
		pro[i].id=i;
		cout<<"enter process "<<i+1<<"'s arrival time"<<endl;
		cin>>pro[i].arvtime;
		cout<<"enter process "<<i+1<<"'s burst time"<<endl;
		cin>>pro[i].bsttime;
	}
	return pro;
}
process findFirstInReadyQueue(vector<process> pro, int time){
	int minbt=1000;
	int index=-1;
	process res;
	for(int i=0;i<pro.size();i++){
		if(pro[i].arvtime<=time){
			if(pro[i].bsttime<minbt){
				minbt=pro[i].bsttime;
				index=i;
			}
		}
	}
	if(index!=-1){
		res=pro[index]; 
		res.cpttime=time+res.bsttime;
		res.tat=res.cpttime-pro[index].arvtime;
		cout<<"At time "<<time<<", Process "<<index+1<<" starts to run. It's completion time is "<<res.cpttime<<", Turn Around Time is "<<res.tat;
		res.wt=res.tat-res.bsttime;
		cout<<", and Waiting Time is "<<res.wt<<"."<<endl;
	}else{
		res=findFirstInReadyQueue(pro, time+1);
	}
	return res;
}

vector<process> runningOrder(vector<process> pro){
	int s=pro.size();
	cout<<s<<endl;
	vector<process> runpro(s);
	int time=0;
	for(int j=0;j<s;j++){
		runpro[j]=findFirstInReadyQueue(pro,time);
		time=runpro[j].cpttime;
		int index=runpro[j].id;
		pro[index].arvtime=1000;	
	}
	return runpro;
}

int main() {
	vector<process> pro=inputNProcess(4);
	vector<process> runpro=runningOrder(pro);
	float sumtat=0;
	float sumwt=0;
	int j=0;
	for(int i=0;i<4;i++){
		sumtat=sumtat+runpro[i].tat;
		sumwt=sumwt+runpro[i].wt;
	}
	float avgtat=sumtat/4;
	float avgwt=sumwt/4;
	cout<<"So, the average Turn Around Time is "<<avgtat<<"."<<endl;
	cout<<"The average Waiting Time is "<<avgwt<<"."<<endl;
	return 0;
}
