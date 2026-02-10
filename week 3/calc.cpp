#include <iostream>
#include <sstream>
#include "adder.h"

int main(int argc, char *argv[]){
    int a, b, c;
    std::cout << "Ran successfully! " << std::endl;
    if (argc != 3) return 1;
    
    std::string sa = argv[1];
    std::string sb = argv[2];
    
    std::stringstream ssa(sa);
    std::stringstream ssb(sb);
    
    ssa >> a;
    ssb >> b;
    
    c = add(a, b);
    
    std::cout << "Result is: " << c << std::endl;
    
    return 0;
}
