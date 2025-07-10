#include<bits/stdc++.h>
using namespace std;
class voter{
    public:
        string voterID;
        string name;
        int age;
        bool hasvoted;

        voter(string id,string n,int a){
            voterID=id;
            name=n;
            age=a;
            hasvoted =false;
        }
};
class candidate{
  public:
  string candidateID;
  string name;
  string party;
  int votecount;
  candidate(string id,string n,string p){
      candidateID=id;
      name=n;
      party=p;
      votecount=0;
  }
};

vector<voter> voters;
vector<candidate> candidates;
void registervoter(){
    string id,name;
    int age;
    cout<<"Enter voter ID: ";
    cin>>id;
    for(const auto& voter : voters){
        if(voter.voterID ==id){
            cout<<"Error: voter ID already exists.\n";
            return;
        }
    }
    cout<<"Enter Name: ";
    cin.ignore();
    getline(cin,name);
    cout<<"Enter Age: ";
    cin>>age;
    if(age<18 ){
        cout<<"You must be 18 or older.";
        return;
    }
    voters.emplace_back(id,name,age);
    cout<<"Voter Registered successfully!";
}
void addcandidate(){
    if(candidates.size() >=10) {
        cout<<"Cannot add more than 10 candidates.\n";
        return;
    }
    string id,name,party;
    cout<<"Enter candidate ID: ";
    cin>>id;
    for (const auto& it: candidates){
        if(it.candidateID == id) {
            cout<<"Entered candidate ID already exists.\n";
            return;
        }
    }

    cout<<"Enter Name: ";
    cin.ignore();
    getline(cin,name);
    cout<<"Enter party: ";
    getline(cin,party);
    candidates.emplace_back(id,name,party);
    cout<<"Candidate added successfully!\n";
}
void castvote(){
    string voterid;
    cout<<"Enter your voter ID: ";
    cin>>voterid;
    auto voterit=find_if(voters.begin(),voters.end(),[&](const voter& v){return v.voterID==voterid;});

    if (voterit==voters.end()){
        cout<<"voter ID not found.\n";
        return;
    }
    if(voterit->hasvoted){
        cout<<"You have already voted.\n";
        return;
    }
    if(candidates.empty()){
        cout<<"No candidates available for vote.\n";
        return;
    }
    cout<<"Available candidates:\n";
    for(const auto& it : candidates)
    cout<<it.candidateID<<" - "<<it.name<<"("<<it.party <<")\n";

    string candidateid;
    cout<<"Enter the candidate ID you want to vote for: ";
    cin>>candidateid;

    auto it=find_if(candidates.begin(),candidates.end(),[&](const candidate& c){return c.candidateID==candidateid;});
    if(it==candidates.end()){
        cout<<"Invalid candidate ID.\n";
        return;
    }
    it->votecount++;
    voterit->hasvoted=true;
    cout<<"Your vote has been cast successfully!\n";
}
void displayresults(){
    if(candidates.empty()){
        cout<<"No candidates to show.\n";
        return;
    }
    cout<<"\nElection results:\n";
    int maxvotes=-1;
    for(const auto& c:candidates){
        cout<<c.name<<"("<<c.party<<") - "<<c.votecount<<" votes\n";
        if(c.votecount>maxvotes){
            maxvotes=c.votecount;
        }
    }
    vector<string>winners;
    for(const auto& c : candidates){
        if(c.votecount==maxvotes){
            winners.push_back(c.name);
        }
    }
    if(winners.size()==1){
        cout<<"\nWinner: "<<winners[0]<<" with "<<maxvotes <<" votes!\n";
    }
    else{
        cout<<"\nIt's a tie between: \n";
        for(const auto& name: winners){
            cout<<"- "<<name<<endl;
        }
        cout<<"Each has "<<maxvotes<<" votes.";
    }
}

int main()
{
    int choice;
    while(true){
        cout << "\n===== ONLINE VOTING SYSTEM =====" << endl;
        cout << "1. Register a Voter\n2. Add a Candidate\n3. Cast a Vote\n4. Display Results\n5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice){
            case 1: registervoter(); break;
            case 2: addcandidate(); break;
            case 3: castvote(); break;
            case 4: displayresults(); break;
            case 5: cout<<"Exiting.....\n"; return 0;
            default: cout<<"Invalid choice,\n";
        }
    }
    return 0;
}
