#ifndef DA_TP_CLASSES_UFDS
#define DA_TP_CLASSES_UFDS

#include <vector>
using namespace std;

class UFDS {
public:
    UFDS(unsigned int N);
    unsigned long findSet(unsigned int i);
    bool isSameSet(unsigned int i, unsigned int j);
    void linkSets(unsigned int i, unsigned int j);

private:
    vector<unsigned int> path; 
    vector<unsigned int> rank;
};


#endif
