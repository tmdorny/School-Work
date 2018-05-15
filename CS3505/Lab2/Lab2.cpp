#include <iostream>
class Cat {
    int lives; // Cats have 9 lives
public:
    // Construct a Cat with the number of lives
    Cat(int startLives) : lives(startLives) {
        // nothing else to do
    }
// Report number of lives
void reportLives() {
    std::cout << "Cat has " << lives << " lives left. :o";
    return;
}
// Decrement lives
void loseLife() {
    lives --;
    return;
}
};



int main() {
    Cat mittens(9);
    mittens.reportLives();
    mittens.loseLife();
    mittens.reportLives();

}