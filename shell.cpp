#include <Windows.h>
#include <iostream>
#include <string.h>
#include <time.h>
using namespace std;

int main(){
	
	
	string token1;
	string token2;
	string fileAddress = "C:\\WINDOWS\\system32\\";
	string activeProcesses[1024];
	int activeProcessesIndex = 0;
	string allProcesses[1024];
	int allProcessesIndex = 0;
	//DWORD *processesInfo = new DWORD[4096];
	DWORD processesInfo[1024];
	int processInfoIndex = 0;
	time_t startTime[1024];
	int startTimeIndex = 0;
	time_t endTime[1024];
	int endTimeIndex = 0;
	
	int terminatedCount = 0;
	
    while (1){
		cout << endl << "Murtaza Kazmi's Shell" <<endl;
		cout << "Helps manage processes in Windows" <<endl;
		cout << "Use at your own risk ;-)" <<endl;
		cout  << endl << "Help: "<<endl;
		cout << "run 'process_name' (runs a process with that name. Currently set to Notepad)"<<endl;
		cout << "kill 'process_name' (kills all processes with that name - again, type Notepad or change source code"<<endl;
		cout << "lst (lists all running processes)"<<endl;
		cout << "list All (lists all processes)"<<endl << endl;
		
		
		
		fileAddress = "C:\\WINDOWS\\system32\\";
		HANDLE hProcess;
		HANDLE hThread;
		STARTUPINFO startUpInfo;
		PROCESS_INFORMATION processInformation;
		DWORD dwProcessId = 0;
		DWORD dwThreadId =0;
		ZeroMemory(&startUpInfo, sizeof(startUpInfo));
		ZeroMemory(&processInformation,sizeof(processInformation));
		
        cout << "shell> ";
        cin >> token1;
		if (token1.compare("exit") == 0) break;
		else if (token1.compare("lst") == 0){
			int ind = 0;
			int difference = activeProcessesIndex - terminatedCount;
			for (int i = 0; i < 500 ; i++){
				if(i <= difference and i != 0){
				int elapsedTime = endTime[difference-i] - startTime[difference-i];
				cout << ind << " " << activeProcesses[difference-i] << " " << processesInfo[difference-i]<< startTime[difference-i] << " " << endTime[difference-i] << " " << elapsedTime<<endl;
				ind += 1;
				}
			}
		}
		else if (token1.compare("print") == 0){
			cin >> token2;
			cout << token2 << endl;
		}
		else if (token1.compare("run") == 0){
			cin >> token2;
			
			if(token2 != "Notepad"){
				cout << "Invalid application name. Please reenter." << endl;
				continue;
			}
			activeProcesses[activeProcessesIndex] = "Notepad";
			activeProcessesIndex += 1;
			allProcesses[allProcessesIndex] = "Notepad";
			allProcessesIndex += 1;
			startTime[startTimeIndex] = time(0)*1000;
			startTimeIndex += 1;
			endTime[startTimeIndex] = 0;
			token2 += ".exe";
			fileAddress += token2;
			BOOL createProcess = CreateProcessA(
							"C:\\WINDOWS\\system32\\Notepad.exe",
							NULL,
							NULL,
							NULL,
							FALSE,
							0,
							NULL,
							NULL,
							&startUpInfo,
							&processInformation);
			if(!createProcess){
				cout<<"Failed";
			}
			else {
				processesInfo[processInfoIndex] = processInformation.dwProcessId;
				processInfoIndex += 1;
				cout << "Process created."<<endl;
			}
			//system("PAUSE");
		}
		else if (token1.compare("kill") == 0){
			cin >> token2;
			int count = 0;
			for (int i = 0; i < 500 ; i++){
					if(token2.compare(activeProcesses[i]) == 0){
						count += 1;
						HANDLE tmpHandle = OpenProcess(PROCESS_ALL_ACCESS,TRUE,processesInfo[i]);
						BOOL result = TerminateProcess(tmpHandle,0);
						if(!result){
							cout << "Termination error with process of ID: "<< processesInfo[i]<<endl;
						}
						endTime[endTimeIndex] = time(0)*1000;
						
						endTimeIndex += 1;
						activeProcesses[i] = "";
						activeProcessesIndex -= 1;
						processInfoIndex -= 1;
						
					}
				}
				cout << count << " processes were killed."<<endl;
				terminatedCount += count;
		}
		else if (token1.compare("list") == 0){
			cin >> token2;
			int ind = 0;
			if(token2.compare("All") == 0 ){
				cout << "Process " << "ID" << "StartTime " << "EndTime " << "ElapsedTime"<<endl;
				for (int i = 0; i < 500 ; i++){
					if(processesInfo[i] != 0){
						int elapsedTime = endTime[i] - startTime[i];
						cout << ind << " "<<allProcesses[i] << " " << processesInfo[i]<< " "<<startTime[i] << " " << endTime[i] << " " << elapsedTime<<endl;
						ind += 1;
					}
				}
			}
			}
			else {
				cout << "Error"<<endl;
		}
	}
		
		//delete[] activeProcesses;
		//delete[] allProcesses;
		//delete[] processesInfo;
		
		
	
	return 0;
}