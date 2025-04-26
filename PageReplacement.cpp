#include <bits/stdc++.h>
using namespace std;

void print_frames(vector<int> frames){
    for(auto frame: frames){
        if(frame==-1){
            cout<<" ";
        }else{
        cout<<frame<<" ";
        }
    }
    cout<<"\n";
}

void fcfs(vector<int> pages, int frame_cnt){
    
    vector<int> frames(frame_cnt,-1);
    int index=-1;
    for(auto symbol: pages){
        bool hit=false;
        for(auto frame: frames){
            if(frame==symbol){
                hit=true;
                break;
            }
        }
        if(hit) page_hits++;
        else{ 
            index=(index+1)%frame_cnt;
            frames[index]=symbol;
        }
      print_frames(frames);
    }
    // cout << "\nPage hits: " << page_hits;
    // cout << "\nPage misses: " << pages.size() - page_hits;
    // cout << "\nRatio of Page Hit: " << (float)page_hits / pages.size();
    // cout << "\nRatio of Page Miss: " << (float)(pages.size() - page_hits) / pages.size() << endl;
}

void lru(vector<int> pages, int frame_cnt){
    vector<int> frames(frame_cnt, -1);
    vector<int> recent(frame_cnt, -1);
    for(int toy=0;toy<pages.size();toy++){
        bool hit=false;
        for(int box=0;box<frame_cnt;box++){
            if(frames[box]==pages[toy]){
                hit=true;
                recent[box]=toy;
                break;
            }
        }
        
        if(hit) page_hits++;
        else{
            int replace_index=-1;
            for(int box=0;box<frame_cnt;box++){
                if(frames[box]==-1){
                    replace_index=box;
                    break;
                } //empty available
            }
            if(replace_index==-1){
                int lru_index=toy;
                for(int box=0;box<frame_cnt;box++){
                    if(recent[box]<lru_index){
                        lru_index=recent[box];
                        replace_index=box;
                    }
                }
            }//not empty,has to replace with lru
            frames[replace_index] = pages[toy];
            recent[replace_index] = toy;
        }
    print_frames(frames);
    }
}

void optimal(vector<int> pages, int frame_cnt){
    vector<int> frames(frame_cnt, -1);
    vector<int> recent(frame_cnt, -1);
    for(int toy=0;toy<pages.size();toy++){
        bool hit=false;
        for(int box=0;box<frame_cnt;box++){
            if(frames[box]==pages[toy]){
                hit=true;
                recent[box]=toy;
                break;
            }
        }
        
        if(hit) page_hits++;
        else{
            int replace_index=-1;
            int farthest=i+1;
            for(int box=0;box<frame_cnt;box++){
                if(frames[box]==-1){
                    replace_index=box;
                    break;
                }
            } //fill in available
            for(int k=toy+1;k<pages.size();k++){
               if(pages[k]==frames[box]){
                   break;
               } 
            } //dont replace, needed
            if(k==pages.size()){
                replace_index=box;
                break;
            } //readily replace no use in future
            if(k>farthest){
                farthest=k;
                replace_index=box;
            } //readily replace farthest optimal
            frames[replace_index]=pages[toy];
        }
    print_frames(frames);
    }
}

int main() {
    int frame_cnt;
    int n;
    vector<int> pages(n);
    
    cout<<"Enter the number of pages: "<<"\n";
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>pages[i];
    }
    cout<<"Enter the number of frames: "<<"\n";
    cin>>frame_cnt;
    
    while(true){
    int choice;
    cout<<"Enter your choice: \n 1.fcfs \n 2. lru \n 3. optimal \n 4. Quit "<<"\n";
    cin>>choice;
    switch(choice){
        case 1: 
            fcfs(pages,frame_cnt);
            break;
        case 2: 
            lru(pages,frame_cnt);
            break;
        case 3:
            optimal(pages,frame_cnt);
            break;
        case 4: 
            cout<<"Quitting"<<"\n";
            return;
        default:
            cout<<"Invalid entry"<<"\n";
    }
    }
    
    return 0;
}