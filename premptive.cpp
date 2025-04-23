#include <bits/stdc++.h>
using namespace std;

struct process {
    int processNo;
    int arrivalTime;
    int burstTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int responseTime;
    int priority;
};

void printps(int n, vector<process> &p) {
    cout << "\nOutput Table:\n";
    cout << "Process | Arrival Time | Burst Time | Completion Time | Turnaround Time | Waiting Time | Response Time\n";
    for (int i = 0; i < n; i++) {
        cout << "   " << p[i].processNo << "\t\t" << p[i].arrivalTime << "\t\t"
             << p[i].burstTime << "\t\t" << p[i].completionTime << "\t\t"
             << p[i].turnaroundTime << "\t\t" << p[i].waitingTime << "\t\t"
             << p[i].responseTime << "\n";
    }
}

void ps(int n, vector<process> &p) {
    int curTime = 0, cnt = 0;
    float totalWT = 0, totalTAT = 0;

    vector<int> remainingTime(n);
    vector<int> firstResponse(n, -1);

    for (int i = 0; i < n; i++) {
        remainingTime[i] = p[i].burstTime;
    }

    while (cnt < n) {
        int idx = -1, minPriority = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (p[i].arrivalTime <= curTime && remainingTime[i] > 0) {
                if (p[i].priority < minPriority) {
                    minPriority = p[i].priority;
                    idx = i;
                } 
                else if (p[i].priority == minPriority) {
                    if (p[i].arrivalTime < p[idx].arrivalTime) {
                        idx = i;
                    }
                }
                
            }
        }
        

        if (idx != -1) {
            if (firstResponse[idx] == -1) {
                firstResponse[idx] = curTime;
            }

            remainingTime[idx]--;

            if (remainingTime[idx] == 0) {
                p[idx].completionTime = curTime + 1;
                p[idx].turnaroundTime = p[idx].completionTime - p[idx].arrivalTime;
                p[idx].waitingTime = p[idx].turnaroundTime - p[idx].burstTime;
                p[idx].responseTime = firstResponse[idx] - p[idx].arrivalTime;
                totalWT += p[idx].waitingTime;
                totalTAT += p[idx].turnaroundTime;
                cnt++;
            }
        }

        curTime++;
    }

    printps(n, p);
    cout << "\nAverage Waiting Time: " << totalWT / n << endl;
    cout << "Average Turnaround Time: " << totalTAT / n << endl;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<process> p(n);
    for (int i = 0; i < n; i++) {
        p[i].processNo = i + 1;
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> p[i].arrivalTime;
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> p[i].burstTime;
        cout << "Enter priority of process " << i + 1 << ": ";
        cin >> p[i].priority;
    }

    ps(n, p);

    return 0;
}