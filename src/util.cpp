#include <iostream>
#include <random>

long long rand_int(long long min, long long max){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    
    return (long long) dist(gen);
}