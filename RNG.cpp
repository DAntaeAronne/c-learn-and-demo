#include <random>

int randomNumber() {

    std::random_device rd;

    std::mt19937 gen(rd());

    int val = rd();

    return abs(val);
}
