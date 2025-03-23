#include <iostream>
#include "MakingAPosition.h"

int main(){
    std::cout << "Hello from Alex Gudis";
    std::cout << "Hello from Greg Goozmer";
    std::cout << "Greg Goozmer is going to fuck Dasha when I go home";
    std::cout << "Ofc, Alexey. I very very want her... She is very beautiful!!! I love her.";

    Positon position1 = MakingPosition();
    int posShoulder = position1.getShoulder();
    std::cout << posShoulder;
    return 0;
}
