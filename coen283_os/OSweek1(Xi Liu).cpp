#include <iostream>
#include <vector>
#include <string>
using namespace std;

constexpr int kDefaultEndTimeBeyondAllProcesses = 2147483647; 
//  Input structure which contains the ID and all times of a process. 
struct Process{
	string id;//The name of this process.
	int index;//The input order of this process in all processes. 
	int arrival_time; 
	int burst_time; 
	int completion_time;
	int turn_around_time; 
	int waiting_time;
};
//  Prompts users to input the number of processes to be scheduled and their IDs, Arrival Times, and Burst Time. 
vector<Process> InputNProcess(){
	int process_count;
	cout<<"Enter the total number of processes:"<<endl;
	cin>>process_count;
	vector<Process> processes(process_count);
	for(int i=0;i<process_count;i++){
		processes[i].index=i;
		cout<<"enter process "<<i+1<<"'s ID:"<<endl;
		cin>>processes[i].id;
		cout<<"enter process "<<i+1<<"'s arrival time:"<<endl;
		cin>>processes[i].arrival_time;
		cout<<"enter process "<<i+1<<"'s burst time:"<<endl;
		cin>>processes[i].burst_time;
	}
	return processes;
}
//  Finds the first process in the queue at a spesific time and start running it. 
//  Then, calculates and outputs its Completion Time, Turn Around Time and Waiting Time.
Process FindFirstInReadyQueue(const vector<Process>& processes, int time){
	int minbt=kDefaultEndTimeBeyondAllProcesses;
	int index=-1;
	Process res;
	for(int i=0;i<processes.size();i++){
		if(processes[i].arrival_time<=time){
			if(processes[i].burst_time<minbt){
				minbt=processes[i].burst_time;
				index=i;
			}
		}
	}
	if(index!=-1){
		res=processes[index]; 
		res.completion_time=time+res.burst_time;
		res.turn_around_time=res.completion_time-processes[index].arrival_time;
		cout<<"At time "<<time<<", Process "<<processes[index].id<<" starts to run. It's completion time is "<<res.completion_time<<", Turn Around Time is "<<res.turn_around_time;
		res.waiting_time=res.turn_around_time-res.burst_time;
		cout<<", and Waiting Time is "<<res.waiting_time<<"."<<endl;
	}else{
		//If there is no process ready to start running, add 1 unit to the time and search again.  
		res=FindFirstInReadyQueue(processes, time+1);
	}
	return res;
}

// Reorders all processes running-order based on their arrival_time and burst_time.
vector<Process> RunningOrder(vector<Process> processes){
	const int process_size=processes.size();
	vector<Process> ordered_processes(process_size);
	int time=0;
	for(int j=0;j<process_size;j++){
		ordered_processes[j]=FindFirstInReadyQueue(processes,time);
		time=ordered_processes[j].completion_time;
		const int index=ordered_processes[j].index;
		processes[index].arrival_time=kDefaultEndTimeBeyondAllProcesses;	
	}
	return ordered_processes;
}

int main() {
	vector<Process> processes=InputNProcess();
	if(processes.empty()){
		cout<<"No process received."<<endl;
		return -1;
	}
	vector<Process> ordered_processes=RunningOrder(std::move(processes));
	float sum_turn_around_time=0;
	float sum_waiting_time=0;
	for(int i=0;i<ordered_processes.size();i++){
		sum_turn_around_time=sum_turn_around_time+ordered_processes[i].turn_around_time;
		sum_waiting_time=sum_waiting_time+ordered_processes[i].waiting_time;
	}
	float avg_turn_around_time=sum_turn_around_time/ordered_processes.size();
	float avg_waiting_time=sum_waiting_time/ordered_processes.size();
	cout<<"So, the average Turn Around Time is "<<avg_turn_around_time<<"."<<endl;
	cout<<"The average Waiting Time is "<<avg_waiting_time<<"."<<endl;
	return 0;
}