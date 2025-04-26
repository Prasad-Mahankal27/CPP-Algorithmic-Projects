#include <bits/stdc++.h>
using namespace std;

struct Process {
    int id, arrival, burst, priority;
    int remaining, completion, turnaround, waiting;
};

void printTable(const vector<Process>& processes) {
    cout << "\n+------+----------+--------+------------+------------+---------+\n";
    cout << "| PID  | Arrival  | Burst  | Completion | Turnaround | Waiting |\n";
    cout << "+------+----------+--------+------------+------------+---------+\n";

    for (const auto& p : processes) {
        cout << "| P" << setw(3) << p.id
             << " | " << setw(8) << p.arrival
             << " | " << setw(6) << p.burst
             << " | " << setw(10) << p.completion
             << " | " << setw(10) << p.turnaround
             << " | " << setw(7) << p.waiting << " |\n";
    }

    cout << "+------+----------+--------+------------+------------+---------+\n";
}

void fcfs(vector<Process>& processes) {
    int time = 0;
    for (auto& p : processes) {
        if (time < p.arrival)
            time = p.arrival;
        time += p.burst;
        p.completion = time;
        p.turnaround = p.completion - p.arrival;
        p.waiting = p.turnaround - p.burst;
    }
    printTable(processes);
}

void sjf(vector<Process>& processes) {
    int time = 0, done = 0, n = processes.size();
    while (done < n) {
        int idx = -1, shortest = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival <= time && processes[i].completion == 0 && processes[i].burst < shortest) {
                shortest = processes[i].burst;
                idx = i;
            }
        }
        if (idx == -1) {
            ++time;
        } else {
            time += processes[idx].burst;
            processes[idx].completion = time;
            processes[idx].turnaround = time - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
            ++done;
        }
    }
    printTable(processes);
}

void prioritySchedule(vector<Process>& processes) {
    int time = 0, done = 0, n = processes.size();
    while (done < n) {
        int idx = -1, highest = INT_MAX;
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival <= time && processes[i].completion == 0 && processes[i].priority < highest) {
                highest = processes[i].priority;
                idx = i;
            }
        }
        if (idx == -1) {
            ++time;
        } else {
            time += processes[idx].burst;
            processes[idx].completion = time;
            processes[idx].turnaround = time - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
            ++done;
        }
    }
    printTable(processes);
}

void roundRobin(vector<Process>& processes, int tq) {
    int time = 0, done = 0, n = processes.size();
    cout << "\nGantt Chart:\n|";

    while (done < n) {
        bool moved = false;
        for (auto& p : processes) {
            if (p.arrival <= time && p.remaining > 0) {
                int run = min(p.remaining, tq);
                cout << " P" << p.id << " (" << time << "-" << time + run << ") |";
                time += run;
                p.remaining -= run;
                if (p.remaining == 0) {
                    p.completion = time;
                    p.turnaround = p.completion - p.arrival;
                    p.waiting = p.turnaround - p.burst;
                    ++done;
                }
                moved = true;
            }
        }
        if (!moved) ++time;
    }

    cout << endl;
    printTable(processes);
}

int main() {
    int choice, tq;

    while (true) {
        int n;
        cout << "\nEnter number of processes (0 to exit): ";
        cin >> n;
        if (n == 0) break;

        vector<Process> processes(n);

        for (int i = 0; i < n; ++i) {
            processes[i].id = i + 1;
            cout << "Enter Arrival and Burst time for P" << i + 1 << ": ";
            cin >> processes[i].arrival >> processes[i].burst;
            processes[i].remaining = processes[i].burst;
        }

        cout << "\nChoose Scheduling Algorithm:\n";
        cout << "1. First Come First Serve (FCFS)\n";
        cout << "2. Shortest Job First (SJF)\n";
        cout << "3. Priority Scheduling\n";
        cout << "4. Round Robin\n";
        cout << "Choice: ";
        cin >> choice;

        if (choice == 3) {
            for (int i = 0; i < n; ++i) {
                cout << "Enter Priority for P" << i + 1 << ": ";
                cin >> processes[i].priority;
            }
        }

        if (choice == 4) {
            cout << "Enter Time Quantum: ";
            cin >> tq;
        }

        switch (choice) {
            case 1: fcfs(processes); break;
            case 2: sjf(processes); break;
            case 3: prioritySchedule(processes); break;
            case 4: roundRobin(processes, tq); break;
            default: cout << "Invalid choice.\n"; break;
        }
    }

    return 0;
}
