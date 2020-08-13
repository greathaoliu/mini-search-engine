#include <iostream>
#include <ratio>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <string>
#include <set>
#include <dirent.h>
#include <algorithm>
#include "stemmer/porter2_stemmer.h"

using namespace std;

bool compareFreq(pair<string, int> &a, pair<string, int> &b)
{
    return (a.second > b.second);
}

int main()
{
    set<string> stopWords;
    vector<string> documents;
    string stopWordsFile("StopWordsList.txt");
    string filenamesFile("FilenamesList.txt");
    ifstream stopWordsIn(stopWordsFile);
    ifstream FilenamesIn(filenamesFile);
    double duration;
    clock_t t1, t2;

    string oDir = "ShakespeareComplete"; //原文文件夹名
    string dDir = "Stemmed";  //目标文件夹名


    t1 = clock();
    system("mkdir Stemmed");

    DIR *dir;
    struct dirent *entry;
    dir = opendir(oDir.c_str());

    ifstream in;
    ofstream out;
    string filename;
    string currentWord;
    map<string, int> termFreq;
    int docNum = 0;
    ofstream filenamesOut(filenamesFile);
    while((entry = readdir(dir)) != NULL){
        filename = entry->d_name;
        if(filename == "." || filename == "..") continue;
        in.open(oDir + "/" + filename);
        out.open(dDir + "/" + filename);

        while (in >> currentWord)
        {
            Porter2Stemmer::trim(currentWord);
            Porter2Stemmer::stem(currentWord);

            if(currentWord == "") continue;
            termFreq[currentWord]++;

            out<<currentWord<<' ';
        }
        in.close();
        out.close();

        documents.push_back(filename);
        filenamesOut<<filename<<' ';

        docNum++;
    }

    typedef pair<string, int> pair;
    vector<std::pair<string, int>> vecTf;
    copy(termFreq.begin(), termFreq.end(), back_inserter<vector<pair>>(vecTf));//复制到vector容器中
    sort(vecTf.begin(), vecTf.end(), compareFreq);
    ofstream StopWordOut(stopWordsFile);
    for(auto it = vecTf.begin(); it != vecTf.end(); ++it){
        if(it->second > 2800)//出现次数大于2800的认定为stop words，试出来比较合适
        {
            stopWords.insert(it->first);
            StopWordOut << it->first << ' ';
        }
        else break;
    }
    cout << "Pretreatment is done."<<endl;

    t2 = clock();
    duration = double(t2-t1)/CLOCKS_PER_SEC;
    cout<<"cost time:"<<duration<<"s"<<endl;
    return 0;
}
