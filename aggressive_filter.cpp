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
    ofstream fout(argv[2]);
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
                cntSite[i] += (line[i] == 'A' || line[i] == 'C' || line[i] == 'G' || line[i] == 'T');
            }
        }
        keep.resize(cntSite.size(), true);
        for (int i = 0; i < cntSite.size(); i++){
            if (cntSite[i] < 4 || cntSite[i] * 2 < cntSpeices){
                for (int j = max<int>(0, i - 5); j < min<int>(cntSite.size(), i + 6); j++){
                    keep[j] = false;
                }
            }
        }
    }
    {
        ifstream fin(argv[1]);
        string line;
        while (getline(fin, line)){
            if (line.size() >= 5 && line.substr(0, 5) == ">root") {
                getline(fin, line); continue;
            }
            if (line.size() >= 8 && line.substr(0, 8) == ">birdAnc") {
                getline(fin, line); continue;
            }
            int namepos = 0;
            while (line[namepos] != '\t') namepos++;
            fout << line.substr(0, namepos) << endl;
            getline(fin, line);
            for (int i = 0; i < cntSite.size(); i++){
                if (!keep[i]) line[i] = '-';
            }
            fout << line << endl;
        }
    }
    return 0;
}