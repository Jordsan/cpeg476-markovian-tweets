#include "tweet-service.h"
#include <jsoncpp/json/json.h>

using namespace std;

size_t callback(const char* in, size_t size, size_t num, string* out){
    const size_t totalBytes(size * num);
    out->append(in, totalBytes);
    return totalBytes;
}
void getTweets(string username) {
    auto curl = curl_easy_init();
    if (curl) {
        string finalURL = "https://api.twitter.com/1.1/statuses/user_timeline.json?screen_name=";
        finalURL.append(username);
        finalURL.append("&tweet_mode=extended");
        
        curl_easy_setopt(curl, CURLOPT_URL, finalURL.c_str());
    
        struct curl_slist *chunk = NULL;
        chunk = curl_slist_append(chunk, "Authorization: Bearer AAAAAAAAAAAAAAAAAAAAADB53gAAAAAAQvAtkLepgSP7Xc9jnrgRE1%2BO5x4%3DQiz1no5NgFSQpmI5iuuPp9F8LIH3UwbMaeOc82cnvoWQvX6HCF");
     
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        
        string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl = NULL;
        
        Json::Value jsonData;
        Json::Reader jsonReader;
        
        vector<string> tweets;

        if (jsonReader.parse(response, jsonData)) {
            for(int i = 0; i < jsonData.size(); i++) {
                tweets.push_back(jsonData[i]["full_text"].asString());
            }
        }
        else {
            cout << "test" << endl;
        }
        
        ofstream file;
        file.open ("input.txt");
        for (string s: tweets) {
            file << s << "\n";
        }
        file.close();
    }
}