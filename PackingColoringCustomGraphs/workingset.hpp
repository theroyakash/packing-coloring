#if !defined(WORKING_SET)
#define WORKING_SET

#include <set>
#include <vector>

using namespace std;

class WorkingSet {
private:
    std::vector<int> workingset;
    int size = 0;

public:
    WorkingSet() {
        this->workingset = std::vector<int>();
        this->size = 0;
    }
    void add(int x) {
        this->workingset.push_back(x);
        ++this->size;
    }
    int getRandom() {
        srand(time(0));
        int starting_index = 0;
        int ending_index = this->size - 1;

        std::random_device randomDevice;
        std::mt19937 generator(randomDevice());

        std::uniform_int_distribution<int> distribution(starting_index, ending_index);
        int random_index = distribution(generator);
        return this->workingset[random_index];
    }
    int getSize() {
        return this->size;
    }
};

#endif  // WORKING_SET
