#include <bits/stdc++.h>
using namespace std;

void printMovements(const vector<int>& sequence, int head) {
    int seek_count = 0, current_head = head;
    cout << "\nHead movements:\n";
    for (int request : sequence) {
        cout << current_head << " -> " << request << " (Seek: " << abs(request - current_head) << ")\n";
        seek_count += abs(request - current_head);
        current_head = request;
    }
    cout << "Total seek time: " << seek_count << "\n";
}

void fifo(const vector<int>& requests, int head) {
    cout << "\n--- FIFO Scheduling ---\n";
    cout << "Order of execution: ";
    for (int r : requests) cout << r << " ";
    cout << "\n";
    printMovements(requests, head);
}

void sstf(vector<int> requests, int head) {
    cout << "\n--- SSTF Scheduling ---\n";
    vector<int> sequence;
    vector<bool> visited(requests.size(), false);
    int current_head = head;

    for (size_t i = 0; i < requests.size(); ++i) {
        int min_distance = INT_MAX, index = -1;
        for (size_t j = 0; j < requests.size(); ++j) {
            if (!visited[j] && abs(requests[j] - current_head) < min_distance) {
                min_distance = abs(requests[j] - current_head);
                index = j;
            }
        }
        visited[index] = true;
        sequence.push_back(requests[index]);
        current_head = requests[index];
    }

    cout << "Order of execution: ";
    for (int r : sequence) cout << r << " ";
    cout << "\n";
    printMovements(sequence, head);
}

void scan(vector<int> requests, int head, int disk_size, int direction) {
    cout << "\n--- SCAN Scheduling ---\n";
    vector<int> left, right, sequence;

    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    if (direction == 0) left.insert(left.begin(), 0);
    else right.push_back(disk_size - 1);

    if (direction == 0) {
        for (int i = left.size() - 1; i >= 0; --i) sequence.push_back(left[i]);
        for (int r : right) sequence.push_back(r);
    } else {
        for (int r : right) sequence.push_back(r);
        for (int i = left.size() - 1; i >= 0; --i) sequence.push_back(left[i]);
    }

    cout << "Order of execution: ";
    for (int r : sequence) cout << r << " ";
    cout << "\n";
    printMovements(sequence, head);
}

void c_scan(vector<int> requests, int head, int disk_size, int direction) {
    cout << "\n--- C-SCAN Scheduling ---\n";
    vector<int> left, right, sequence;

    for (int r : requests) {
        if (r < head) left.push_back(r);
        else right.push_back(r);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    if (direction == 0) {
        left.insert(left.begin(), 0);
        right.push_back(disk_size - 1);
        for (int i = left.size() - 1; i >= 0; --i) sequence.push_back(left[i]);
        sequence.push_back(disk_size - 1);
        for (int i = right.size() - 1; i >= 0; --i)
            if (right[i] != disk_size - 1) sequence.push_back(right[i]);
    } else {
        right.push_back(disk_size - 1);
        left.insert(left.begin(), 0);
        for (int r : right) sequence.push_back(r);
        sequence.push_back(0);
        for (int r : left) if (r != 0) sequence.push_back(r);
    }

    cout << "Order of execution: ";
    for (int r : sequence) cout << r << " ";
    cout << "\n";
    printMovements(sequence, head);
}

int main() {
    vector<int> requests;
    int n, head, disk_size, choice, direction;

    cout << "Enter number of disk requests: ";
    cin >> n;
    cout << "Enter disk requests:\n";
    for (int i = 0; i < n; ++i) {
        int req; cin >> req;
        requests.push_back(req);
    }

    cout << "Enter initial head position: ";
    cin >> head;
    cout << "Enter disk size (e.g., 200): ";
    cin >> disk_size;

    do {
        cout << "\nChoose Disk Scheduling Algorithm:\n";
        cout << "1. FIFO\n2. SSTF\n3. SCAN\n4. C-SCAN\n5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: fifo(requests, head); break;
            case 2: sstf(requests, head); break;
            case 3:
                cout << "Enter head movement direction (0 for Low, 1 for High): ";
                cin >> direction;
                scan(requests, head, disk_size, direction);
                break;
            case 4:
                cout << "Enter head movement direction (0 for Low, 1 for High): ";
                cin >> direction;
                c_scan(requests, head, disk_size, direction);
                break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
