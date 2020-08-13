#include <iostream>
#include <ratio>
#include "SearchEngine.h"
int main() {
    clock_t t1, t2;
    double duration;
    string keyWord;
    searchEngine searchShakespeare;
    cout << "Loading..." << endl;
    searchShakespeare.loadStopWords();
    searchShakespeare.loadFilenames();
    searchShakespeare.initialIndex();
    cout << "Initialization is done" << endl;
    cout << "Please input the keyword to search" << endl;

    float threshold;
    cin >> keyWord;
    cout << "Please input the threshold" << endl;
    cin >> threshold;
    t1 = clock();
    auto const &result = searchShakespeare.search(keyWord);
    int numOfResult = int(result.size()*threshold) + 1;
    if (numOfResult == 0)cout << "Retrieve no result, you may input a stop word. Please try again." << endl;
    else{
        for (int i = 0; i < numOfResult; i++) {//保证如果有结果，至少返回一个结果
                cout << i + 1 << ":" << result[i] << endl;
        }
    }
    t2 = clock();
    duration = double(t2-t1)/CLOCKS_PER_SEC;
    cout<<"retrieve "<<numOfResult<<" results"<<endl;
    cout<<"cost time:"<<duration<<"s"<<endl;
    return 0;
}
