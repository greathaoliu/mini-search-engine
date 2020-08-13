//
// Created by Hao Liu on 2019-03-19.
//

#ifndef MINISEARCHENGINE_SEARCHENGINE_H
#define MINISEARCHENGINE_SEARCHENGINE_H

#include <string>
#include <map>
#include <set>
#include <vector>

using namespace std;

typedef vector<pair<string, int>> postList;//文件名，出现次数

class searchEngine{
private:
    set<string> stopWords;//包含所有stop words的集合
    vector<string> filenames;
    string dirname = "Stemmed";//存放文本的子目录名
    map<string, postList*> invertedIndex;//搜索时使用的倒排文件索引

public:
    void loadStopWords();//加载stop words到集合中
    void loadFilenames();//加载文本文件名到vector中
    void initialIndex();//初始化倒排文件索引
    vector<string> search(string& keyWords, double threshold = 1.0);//搜索，输入关键词和threshold，返回包含关键词的文件名列表
};
#endif //MINISEARCHENGINE_SEARCHENGINE_H
