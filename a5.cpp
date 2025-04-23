#include <bits/stdc++.h>
using namespace std;

// to check if resources are available
bool cmpResource(int i, int resrc, vector<vector<int>> &need, vector<int> &avail)
{
    for (int j = 0; j < resrc; j++)
    {
        if (need[i][j] > avail[j])
            return false;
    }
    return true;
}

void printTable(vector<vector<int>> &alloc, vector<vector<int>> &max, vector<vector<int>> &need, int proc, int resrc, queue<int> seq)
{
    cout << "\nBanker's Algorithm Result:" << endl;
    cout << setw(10) << "Process" << setw(15) << "Max" << setw(15) << "Allocation" << setw(15) << "Need" << endl;
    cout << "-------------------------------------------------------------" << endl;

    for (int i = 0; i < proc; i++)
    {
        cout << setw(10) << "P" << i + 1;
        for (int j = 0; j < resrc; j++)
            cout << setw(5) << max[i][j];
        cout << setw(10);
        for (int j = 0; j < resrc; j++)
            cout << setw(5) << alloc[i][j];
        cout << setw(10);
        for (int j = 0; j < resrc; j++)
            cout << setw(5) << need[i][j];
        cout << endl;
    }

    cout << "\nSafe Sequence: ";
    while (!seq.empty())
    {
        cout << "P" << seq.front();
        seq.pop();
        if (!seq.empty())
            cout << " -> ";
    }
    cout << endl;
}

// helper func to check the safe state
void helper(vector<vector<int>> &alloc, vector<vector<int>> &max, vector<vector<int>> &need, vector<int> &avail, int proc, int resrc)
{
    vector<int> flag(proc, 0);
    queue<int> seq;
    int count = 0;

    while (count < proc)
    {
        bool found = false;
        for (int i = 0; i < proc; i++)
        {
            if (flag[i] == 0 && cmpResource(i, resrc, need, avail))
            {
                // Mark as completed
                flag[i] = 1;
                seq.push(i + 1);
                count++;
                found = true;
                // Release allocated resources
                for (int j = 0; j < resrc; j++)
                {
                    avail[j] += alloc[i][j];
                }
            }
        }
        if (!found)
            break; // deadlock
    }

    if (count < proc)
    {
        cout << "Deadlock encountered, UNSAFE STATE" << endl;
    }
    else
    {
        printTable(alloc, max, need, proc, resrc, seq);
    }
}

void bankers(vector<int> &total, int proc, int resrc)
{
    vector<vector<int>> alloc(proc, vector<int>(resrc, 0));
    vector<vector<int>> max(proc, vector<int>(resrc, 0));
    vector<vector<int>> need(proc, vector<int>(resrc, 0));
    vector<int> avail(resrc, 0);
    vector<int> allocated(resrc, 0); // 👈 NEW allocated array

    for (int i = 0; i < proc; i++)
    {
        // Take input for max requirement
        cout << "Enter the max requirement for Process " << i + 1 << ":\n";
        for (int j = 0; j < resrc; j++)
        {
            cout << "Resource " << j + 1 << ": ";
            cin >> max[i][j];
        }
        cout << endl;

        // Take input for allocated resources
        cout << "Enter the allocation for Process " << i + 1 << ":\n";
        for (int j = 0; j < resrc; j++)
        {
            cout << "Resource " << j + 1 << ": ";
            cin >> alloc[i][j];
            need[i][j] = max[i][j] - alloc[i][j];
            allocated[j] += alloc[i][j]; // ✅ Sum total allocated
        }
        cout << endl;
    }

    // Compute the available resources
    for (int j = 0; j < resrc; j++)
    {
        avail[j] = total[j] - allocated[j]; // ✅ Clean & clear
    }

    helper(alloc, max, need, avail, proc, resrc);
}

int main()
{
    int n, r;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resources: ";
    cin >> r;

    vector<int> total(r);
    for (int i = 0; i < r; i++)
    {
        cout << "Enter the total instances of Resource " << i + 1 << ": ";
        cin >> total[i];
    }

    bankers(total, n, r);
    return 0;
}
