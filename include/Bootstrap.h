#ifndef SAMPLING_BOOTSTRAP_H
#define SAMPLING_BOOTSTRAP_H

#include <vector>
#include <random>

using namespace std;

template <class T> class Bootstrap {
private:
    vector<T> instanceList;
public:
    Bootstrap(const vector<T> &instanceList, unsigned int seed);
    vector<T> getSample();
};

template<class T> Bootstrap<T>::Bootstrap(const vector<T> &instanceList, unsigned int seed) {
    unsigned long N;
    srand(seed);
    N = instanceList.size();
    this->instanceList.reserve(N);
    for (int i = 0; i < N; i++){
        this->instanceList.push_back(instanceList.at(random() % N));
    }
}

template<class T> vector<T> Bootstrap<T>::getSample(){
    return instanceList;
}

#endif //SAMPLING_BOOTSTRAP_H
