#include<iostream>
#include<fstream>
#include<unordered_map>
#include<unordered_set>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>

using namespace std;

int main(int argc, char *argv[])
{
    vector<int> cntSite;
    vector<bool> keep;
    int cntSpeices = 0;
    {
        ifstream fin(argv[1]);
        string line;
        bool firstline = true;
        while (getline(fin, line)){
            if (line.size() >= 5 && line.substr(0, 5) == ">root") {
                getline(fin, line); continue;
            }
            if (line.size() >= 8 && line.substr(0, 8) == ">birdAnc") {
                getline(fin, line); continue;
            }
            cntSpeices++;
            getline(fin, line);
            if (firstline){
                firstline = false;
                cntSite.resize(line.size());
            }
            for (int i = 0; i < cntSite.size(); i++){
                cntSite[i] += (line[i] != '-');
            }
        }
        int cntDash = 0;
        for (int i = 0; i < cntSite.size(); i++){
            if (cntSite[i] == 0) cntDash++;
            else cntDash = 0;
            keep.push_back(cntDash <= 20);
        }
    }
    if (cntSpeices < 50) return 0;
    {
        ifstream fin(argv[1]);
        ofstream fout(argv[2]);
        string line;
        while (getline(fin, line)){
            if (line.size() >= 5 && line.substr(0, 5) == ">root") {
                getline(fin, line); continue;
            }
            if (line.size() >= 8 && line.substr(0, 8) == ">birdAnc") {
                getline(fin, line); continue;
            }
            fout << line << endl;
            getline(fin, line);
            string temp = line, temp2;
            for (int i = 0; i < cntSite.size(); i++){
                if (cntSite[i] && line[i] != 'A' && line[i] != 'C' && line[i] != 'G' && line[i] != 'T'){
                    for (int j = max<int>(0, i - 5); j < min<int>(cntSite.size(), i + 6); j++) temp[j] = '-';
                }
            }
            for (int i = 0; i < cntSite.size(); i++){
                if (keep[i]) temp2 += temp[i];
            }
            fout << temp2 << endl;
        }
    }
    return 0;
}