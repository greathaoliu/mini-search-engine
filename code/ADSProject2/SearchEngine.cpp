//
// Created by Hao Liu on 2019-03-19.
//
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "stemmer/porter2_stemmer.h"
#include "SearchEngine.h"

using namespace std;

void searchEngine::loadStopWords() {
    string filename("StopWordsList.txt");
    ifstream stopWordsStream(filename);
    if(!stopWordsStream.is_open()){
        cout<<"can't open stop words list."<<endl;
        return;
    }
    string word;
    while(stopWordsStream>>word){
        stopWords.insert(word);
    }
    cout<<"stop words size:"<<stopWords.size()<<endl;
}

void searchEngine::loadFilenames() {
    string filename("FilenamesList.txt");
    ifstream filenamesStream(filename);
    if(!filenamesStream.is_open()){
        cout<<"can't open filenames List"<<endl;
        return;
    }
    string name;
    while(filenamesStream>>name){
        filenames.push_back(name);
    }
    cout<<"filenames size:"<<filenames.size()<<endl;
}

void searchEngine::initialIndex() {
    string currentWord;
    for(const auto &filename : filenames){
        ifstream inStream(dirname+"/"+filename);
        if(!inStream.is_open())cout<<"Open file fail."<<endl;
        while(inStream>>currentWord){
            if(stopWords.find(currentWord) == stopWords.end()){//单词不在stop
                auto iter = invertedIndex.find(currentWord);
                if(iter == invertedIndex.end()) {//词不在索引中
                    auto *tmp = new postList;
                    tmp->push_back(pair<string, int>(filename, 1));
                    invertedIndex.insert(pair<string, postList*>(currentWord, tmp));
                    //cout<<currentWord<<endl;
                }
                else{//如果该词已经在索引中
                    if(iter->second->back().first == filename){
                        iter->second->back().second ++;
                    }
                    else{
                        iter->second->push_back(pair<string, int>(filename, 1));
                    }
                }
            }
        }
    }
    cout<<"inverted index size:"<<invertedIndex.size()<<endl;
}
bool compareFreq(pair<string, int>& a, pair<string, int>& b){
    return a.second > b.second;
}
vector<string> searchEngine::search(string& keyWords, double threshold) {//返回包含所有文件名的vector
    stringstream words;
    string currentWord;//当前要搜索的单词
    vector<string> filenames;
    currentWord = keyWords;
    Porter2Stemmer::trim(currentWord);
    Porter2Stemmer::stem(currentWord);//处理一下关键词
    auto list = invertedIndex.find(currentWord);
    if(list != invertedIndex.end()) {//有结果
        sort(list->second->begin(), list->second->end(), compareFreq);//把文件名按关键词出现次数排序
        for (auto tmp : *(list->second)) {
            filenames.push_back(tmp.first);
            //cout<<filenames.size();
        }
    }
    cout<<"number of all results:"<<filenames.size()<<endl;
    return filenames;
}