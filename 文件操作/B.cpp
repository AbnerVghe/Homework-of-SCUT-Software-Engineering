#include<bits/stdc++.h>
#define ll long long
#define foreach(s, e, x) for(int x = s; x <= e; x++)
#define foreach_sub(s, e, x) for(int x = s; x >= e; x--)
#define INF 0x3f3f3f3f
using namespace std;

class score{
    private:
        char number[10];
        char name[15];
        int scores[3];
        bool deleted;
    public:
        score(){
            deleted = 0;
        };

        score(char* _number, char* _name, int _score1 = 0, int _score2 = 0, int _score3 = 0){
            strcpy(number, _number);
            strcpy(name, _name);
            scores[0] = _score1, scores[1] = _score2, scores[2] = _score3;
            deleted = 0;
        }

        score setScore(int _score1 = 0, int _score2 = 0, int _score3 = 0){
            scores[0] = _score1, scores[1] = _score2, scores[2] = _score3;
            return *this;
        }

        int getSumScore(){
            int sum = 0;
            foreach(0, 2, i) sum += scores[i];
            return sum;
        }

        score printInfo(){
            cout << left << setw(10) << number << left << setw(15) << name;
            foreach(0, 2, i) cout << left << setw(4) << scores[i];
            cout << '\n';
            return *this;
        }

        char* getNumber(){
            return number;
        }

        score deleteStudent(){
            deleted = 1;
            return *this;
        }

        bool chechIfDeleted(){
            return deleted;
        }
};

int turnToNum(string str){
    int i = 0, sign = 1;
    if(str[i] == '-'){
        sign = -1;
        i++;
    }

    int ans = 0;
    while(str[i] != '.' && i < str.length()){
        ans *= 10;
        ans += str[i] - '0';
        i++;
    }
    i++;
    /*double j = 0.1;
    while(i < str.length()){
        ans += j*(str[i] - '0');
        j /= 10;
        i++;
    }*/

    return ans*sign;
}

void appendData(){
    char number[10], name[15];
    int scores[3];
    
    cout << "Enter the infomation of a new student:\n";
    cin.getline(number, 9, ',');
    cin.getline(name, 14, ',');
    foreach(0, 1, i){
        string tmp;
        getline(cin, tmp, ',');
        scores[i] = turnToNum(tmp);
    }
    string tmp;
    getline(cin, tmp);
    scores[2] = turnToNum(tmp);
    cin.clear();
    score tmpScore = {number, name, scores[0], scores[1], scores[2]};
    ofstream outInfo("stu.dat", ios::out | ios::binary | ios::app);
    if(!outInfo){
        cerr << "File could not be opened.\n";
        exit(1);
    }
    outInfo.seekp(0, ios::end);
    outInfo.write(reinterpret_cast<const char*>(&tmpScore), sizeof(score));
    outInfo.close();
}

/*int seekNumber(char *number){
    ifstream datInfo("stu.dat", ios::in | ios::binary);

    if(!datInfo){
        cerr << "File could not be opened.\n";
        exit(1);
    }

    int pos = 0;
    while(!datInfo.eof()){
        datInfo.seekg(pos * sizeof(score));
        score stu;
        datInfo.read(reinterpret_cast<char *>(&stu), sizeof(score));
        if(!stu.chechIfDeleted() && !strcmp(stu.getNumber(), number)){
            return pos;
        }
        else{
            cerr << "Student Number not found!\n";
            return -1;
        }
    }

    datInfo.close();
}*/

void updateData(){
    char number[10];

    fstream datInfo("stu.dat", ios::out | ios::in | ios::binary);

    if(!datInfo){
        cerr << "File could not be opened.\n";
        exit(1);
    }

    cout << "Enter the number of the student you'd like to modify:\n";
    cin.getline(number, 9);
    cin.clear();
    //int pos = seekNumber(number);

    int pos = 0;
    bool found = 0;
    score stu;
    while(!datInfo.eof()){
        datInfo.seekg(pos * sizeof(score));
        datInfo.read(reinterpret_cast<char *>(&stu), sizeof(score));
        if(!stu.chechIfDeleted() && !strcmp(stu.getNumber(), number)){
            found = 1;
            break;
        }
        pos++;
    }

    int scores[3];
    if(found){
        cout << "Enter the score you'd like to change to:\n";
        foreach(0, 1, i){
            string tmp;
            getline(cin, tmp, ',');
            scores[i] = turnToNum(tmp);
        }
        string tmp;
        getline(cin, tmp);
        scores[2] = turnToNum(tmp);
        cin.clear();
        
        stu.setScore(scores[0], scores[1], scores[2]);
        datInfo.seekp(pos * sizeof(score));
        datInfo.write(reinterpret_cast<const char*>(&stu), sizeof(score));
    
        cerr << "Successfully set.\n";
    }
    else{
        cerr << "Student Number not found!\n";
    }

    datInfo.close();
}

bool cmp(score *A, score *B){
    return A->getSumScore() > B->getSumScore();
}

void printData(){
    vector<score *> scoreP;
    ifstream datInfo("stu.dat", ios::in | ios::binary);

    if(!datInfo){
        cerr << "File could not be opened.\n";
        exit(1);
    }

    datInfo.seekg(0, ios::beg);
    while(!datInfo.eof()){
        score *stuP = new score;
        if(!datInfo.read(reinterpret_cast<char *>(stuP), sizeof(score))){
            delete stuP;
            break;
        }
        if(!stuP->chechIfDeleted()) scoreP.push_back(stuP);
        
        datInfo.tellg();
    }
    
    datInfo.close();

    sort(scoreP.begin(), scoreP.end(), cmp);
    for(auto p: scoreP){
        p->printInfo();
    }

    for(auto p: scoreP) delete p;
}

void deleteData(){
    char number[10];
    fstream datInfo("stu.dat", ios::out | ios::in | ios::binary);

    if(!datInfo){
        cerr << "File could not be opened.\n";
        exit(1);
    }

    cout << "Enter the number of the student you'd like to delete:\n";
    cin.getline(number, 9);
    cin.clear();

    int pos = 0;
    bool found = 0;
    score stu;
    while(!datInfo.eof()){
        datInfo.seekg(pos * sizeof(score));
        datInfo.read(reinterpret_cast<char *>(&stu), sizeof(score));
        if(!stu.chechIfDeleted() && !strcmp(stu.getNumber(), number)){
            found = 1;
            break;
        }
        pos++;
    }

    if(found){
        stu.deleteStudent();
        datInfo.seekp(pos * sizeof(score));
        datInfo.write(reinterpret_cast<const char*>(&stu), sizeof(score));    
        cerr << "Successfully deleted.\n";
    }
    else{
        cerr << "Student Number not found!\n";
    }

    datInfo.close();
}

void defragData(){
    cerr << "Defraging...\n";

    ifstream inInfo("stu.dat", ios::in | ios::binary);

    if(!inInfo){
        cerr << "File could not be opened.\n";
        exit(1);
    }

    cerr << "Collecting raw data...\n";
    vector<score> allScore;
    score stu;
    int pos = 0;
    while(inInfo.read(reinterpret_cast<char *>(&stu), sizeof(score))){
        if(!stu.chechIfDeleted()) allScore.push_back(stu);
        pos++;
    }
    cerr << "Data of " << pos << " student(s) collected when " << allScore.size() << " of them valid\n";

    inInfo.close();

    cerr << "Writing into a new file...\n";

    ofstream outInfo("stu.dat", ios::out | ios::binary);

    if(!outInfo){
        cerr << "File could not be opened.\n";
        exit(1);
    }

    pos = 0;
    for(auto tmpScore: allScore){
        outInfo.seekp(pos * sizeof(score));
        outInfo.write(reinterpret_cast<const char*>(&tmpScore), sizeof(score));
        pos++;
    }

    cerr << "Successfully defraged.\n";

    outInfo.close();
}

signed main(){
    ifstream inInfo("in.txt", ios::in);

    if(!inInfo){
        cerr << "File cout not be opened.\n";
        exit(1);
    }

    vector<score> inScores;

    while(!inInfo.eof()){
        char number[10], name[15];
        int scores[3];
        inInfo.getline(number, 9, ',');
        inInfo.getline(name, 14, ',');
        foreach(0, 1, i){
            string tmp;
            getline(inInfo, tmp, ',');
            scores[i] = turnToNum(tmp);
        }
        string tmp;
        getline(inInfo, tmp);
        scores[2] = turnToNum(tmp);
        inScores.push_back((score){number, name, scores[0], scores[1], scores[2]});
    }

    inInfo.close();

    /*for(auto inScore: inScores){
        inScore.printInfo();
        cout << '\n';
    }*/

    ofstream outInfo("stu.dat", ios::out | ios::binary);
    if(!outInfo){
        cerr << "File could not be opened.\n";
        exit(1);
    }

    for(auto inScore: inScores){
        outInfo.write(reinterpret_cast<const char*>(&inScore), sizeof(score));
    }
    
    outInfo.close();

    int opt;
    while(1){
        cout << "========\n";
        cout << "1: Append Data\n" << "2: Updata Data\n" << "3: Delete Data\n" << "4: Print Data\n" << "5: Defrag Data\n";
        cout << "========\n";
        cout << "Enter your opt:(0 to exit)\n";
        cin >> opt;
        cin.ignore();
        if(opt == 0) break;
        else if(opt == 1) appendData();
        else if(opt == 2) updateData();
        else if(opt == 3) deleteData();
        else if(opt == 4) printData();
        else if(opt == 5) defragData();
        else cerr << "Invalid option!\n";
    }
}