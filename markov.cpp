#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm> 
#include <string>
#include "tweet-service.h"

using namespace std;

void removeCharsFromString(string &str, const char* charsToRemove) {
    for (int i = 0; i < strlen(charsToRemove); i++) {
        str.erase(remove(str.begin(), str.end(), charsToRemove[i]), str.end());
    }
}

map<string, map<string, int> > readFile(string input) {
    ifstream file;
    file.open(input.c_str());
    
    map<string, map<string, int> > output;
    map<string, map<string, int> > ::iterator it;
    map<string, int> ::iterator it2;

    string currWord = "";
    string prevWord = "";
    string pattern = "().$*%'`&#@=+{}[]|\\;:><~//";
    while (file >> currWord) {
        bool check = false;
        
        removeCharsFromString(currWord, pattern.c_str());
        
        if (prevWord.compare("")) {
            it = output.find(prevWord);
            if (it != output.end()) {
                it2 = output[prevWord].find(currWord);
                if (it != output.end()) {
                   output[prevWord][currWord] ++; 
                } 
                else {
                    output.at(prevWord).insert(pair<string, int>(currWord, 1));
                }
            }
            else {
                output[prevWord] = {{currWord, 1}};
            }
        }
        
        prevWord = currWord;
    }
    
    return output;
}

vector<string> generateTweets(map<string, map<string, int> > input){
    vector<string> output;
    vector<pair<string, pair<string, int> > > pairList;
    string tweet = "";
    
    for (auto& x: input) {
        for (auto& y: x.second) {
            if (y.first.find("http") == string::npos && x.first.find("http") == string::npos) {
                pairList.push_back(make_pair(x.first, make_pair(y.first, y.second)));
            }
        }
    }

    sort(pairList.begin(), pairList.end(), [=](pair<string, pair<string, int> > a, pair<string, pair<string, int> > b){
        return a.second.second > b.second.second;
    });
    
    for (auto it = pairList.begin(); it != pairList.end(); it++ ){
        if (tweet.length() + it->first.length() + it->second.first.length() + 2 <= 280){
            tweet += it->first + " " + it->second.first + " ";
        }
        else {
            output.push_back(tweet);
            tweet = "";
        }
    }
    
    return output;
}

int main () {
    string username;
    cout << endl << "Enter your desired Twitter username: ";
    cin >> username;
    
    cout << endl << "Grabbing recent tweets from " << username << " ..." << endl;
    getTweets(username);

    map<string, map<string, int> > pairMap;
    pairMap = readFile("input.txt");
    
    int number = 0;
    vector<string> tweets = generateTweets(pairMap);
    
    cout << endl << "Enter desired number of tweets to generate or -1 to quit: ";
    cin >> number;
    
    if (number == -1){
        exit(0);
    }
    
    while (number > tweets.size()){
        cout << endl << "Error: cannot generate " << number << " tweets with given text" << endl;
        cout << endl << "Enter desired number of tweets to generate or -1 to quit: ";
        cin >> number;
        
        if (number == -1){
            exit(0);
        }
    }
    
    cout << endl;
    for (int i = 0; i < number; i++) {
        cout << "Tweet " << i+1 << " : " << endl << endl;
        cout << tweets.at(i) << endl << endl;
    }
    
    return 0;
}

