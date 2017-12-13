
# Markov Tweets

## By Jordan Michaels

<b>CPEG476 Project 3 - Markovian Tweets</b>

This project features a "tweet generator" based on markov chains. <br>
The project outputs 280 character messages from seeded text data. <br>
The data is gathered by querying the Twitter API for recent tweet information of an inputted username.


How to run the project: 

g++ markov.cpp tweet-service.cpp -std=c++11 -lcurl -ljsoncpp -o markov.out

then

./markov.out
