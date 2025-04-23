#include <bits/stdc++.h>
using namespace std;

void print_allocation(vector<int> allocation, int p_cnt){
    for(int i=0;i<p_cnt;i++){
        cout<<"process: "<<i+1<<" ->"<<"block: "<<allocation[i]+1<<"\n";
    }
    cout<<"\n";
}

void first_fit(int p_cnt,int b_cnt,vector<int> process,vector<int> blocks){
    
    vector<int> allocation(p_cnt,-1);
    for(int i=0;i<p_cnt;i++){
        for(int j=0;j<b_cnt;j++){
            if(blocks[j]>=process[i]){
                blocks[j]-=process[i];
                allocation[i]=j;
                break;
            }else{
                if(j==b_cnt-1){
                    cout<<"Insufficient memory"<<"\n";
                    return;
                }
            }
        }
    }
    print_allocation(allocation,p_cnt);
}

void next_fit(int p_cnt,int b_cnt,vector<int> process,vector<int> blocks){
    
    vector<int> allocation(p_cnt,-1);
    int ind=0;
    for(int i=0;i<p_cnt;i++){
        int j=ind;
        for(int count=0;count<b_cnt;count++){
            if(blocks[j]>=process[i]){
                ind=(j+1)%b_cnt;
                blocks[j]-=process[i];
                allocation[i]=j;
                break;
            }
            j=(j+1)%b_cnt;
        }
        if(allocation[i]==-1){
            cout<<"Insufficient memory"<<"\n";
            return;
        }
    }
    print_allocation(allocation,p_cnt);
}

void best_fit(int p_cnt,int b_cnt,vector<int> process,vector<int> blocks){
    
    vector<int> allocation(p_cnt,-1);
    int index=-1, mini=INT_MAX;
    for(int i=0;i<p_cnt;i++){
        index=-1, mini=INT_MAX;
        for(int j=0;j<b_cnt;j++){
            if(blocks[j]>=process[i]){
                int diff=blocks[j]-process[i];
                if(diff<mini){
                    mini=diff;
                    index=j;
                }
            }else{
                continue;
            }
        }
        if(allocation[i]==-1){
            cout<<"Insufficient memory"<<"\n";
        }else{
            allocation[i]=index;
            blocks[index]-=process[i];
        }
    }
    print_allocation(allocation,p_cnt);
}
void worst_fit(int p_cnt,int b_cnt,vector<int> process,vector<int> blocks){
    
    vector<int> allocation(p_cnt,-1);
    int index=-1,maxi=INT_MIN;
    for(int i=0;i<p_cnt;i++){
        index=-1,maxi=INT_MAX;
        for(int j=0;j<b_cnt;j++){
            if(blocks[j]>=process[i]){
                int diff=blocks[j]-process[i];
                if(diff>maxi){
                    maxi=diff;
                    index=j;
                }
            }else{
                continue;
            }
        }
        if(allocation[i]==-1){
            cout<<"Insufficient memory"<<"\n";
        }else{
            allocation[i]=index;
            blocks[index]-=process[i];
        }
    }
    print_allocation(allocation,p_cnt);
}

int main() {
    int b_cnt=0,p_cnt=0;
    cout<<"Enter the number of blocks: "<<"\n";
    cin>>b_cnt;
    cout<<"Enter the number of processes: "<<"\n";
    cin>>p_cnt;
    
    vector<int> process(p_cnt),blocks(b_cnt);
    cout<<"Enter the blocks: "<<"\n";
    for(int i=0;i<b_cnt;i++){
        cin>>blocks[i];
    }
    cout<<"Enter the processes: "<<"\n";
    for(int i=0;i<p_cnt;i++){
        cin>>process[i];
    }
    
    while(true){
        int choice;
        cout<<"Enter your choice: \n 1. First fit \n 2. next fit \n 3. best fit \n 4. worst fit"<<"\n";
        cin>>choice;
        switch(choice){
            case 1:
                first_fit(p_cnt,b_cnt,process,blocks);
                break;
            case 2:
                next_fit(p_cnt,b_cnt,process,blocks);
                break;
            case 3:
                best_fit(p_cnt,b_cnt,process,blocks);
                break;
            case 4:
                worst_fit(p_cnt,b_cnt,process,blocks);
                break;
            case 5:
                cout<<"Quitting"<<"\n";
                return 0;
            default:
                cout<<"Invalid enty"<<"\n";
        }
    }
    return 0;
}