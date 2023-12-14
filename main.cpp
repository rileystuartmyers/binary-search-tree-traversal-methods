#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>

#include "tree.h"

int main(int argc, char* argv[]) {

    std::ofstream ofs("output.txt");
    std::ifstream ifs("input.txt");

    Node* root = nullptr;

    std::string input_string;

    int key = 0;

    while (std::getline(ifs, input_string)) {

        if (key == 1) {

            std::istringstream isi(input_string);
            int temp_int;

            while (isi >> temp_int) {

                Insert(root, temp_int);

            }

            key = 0;

        }
        
        if (key == 2) {

            std::istringstream isr(input_string);
            int temp_int;

            while (isr >> temp_int) {

                Remove(root, temp_int);

            }

            key = 0;

        } 
        
        if (key == 3) {
            
            Traverse(ofs, input_string, root);
                
            key = 0;

        }

        
        if (input_string.find("Insert") != std::string::npos) {

            key = 1;

        }
        
        if (input_string.find("Remove") != std::string::npos) {

            key = 2;

        }
        
        if (input_string.find("Traverse") != std::string::npos) {

            key = 3;

        }

    }

}