#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

#ifndef TREES_H
#define TREES_H

struct Node {

    Node* left;
    Node* right;
    Node* parent;

    int data;

};

void Insert(Node* &place, int _data) {

    if (place == nullptr) {

        Node* temp = new Node();
        temp -> left = nullptr;
        temp -> right = nullptr;
        temp -> data = _data;
        temp -> parent = nullptr;

        place = temp; 

        return;

    } else if (_data > place -> data) {

        if (place -> right == nullptr) {

            Node* temp = new Node();
            temp -> left = nullptr;
            temp -> right = nullptr;
            temp -> data = _data;
            temp -> parent = place;

            place -> right = temp;
            
            return;

        } else {

            Insert(place -> right, _data);

        }

    } else if (_data < place -> data) {

        if (place -> left == nullptr) {

            Node* temp = new Node();
            temp -> left = nullptr;
            temp -> right = nullptr;
            temp -> data = _data;
            
            temp -> parent = place;

            place -> left = temp;

            return;

        } else {

            Insert(place -> left, _data);

        }

    } else {

        return;

    }
        
}

void Print(Node* place) {

    if (place == nullptr) {

        return;

    } else {

        std::cout << place -> data << " ";

        Print(place -> left);
        Print(place -> right);
    }

}

Node* Find_Removal(Node* place, int _data) {

    if (place -> data == _data) {

        return place;

    } else {

        if (_data > place -> data) {

            if (place -> right == nullptr) {

                return nullptr;

            } else {

                return Find_Removal(place -> right, _data);

            }

        } else {

            if (place -> left == nullptr) {

                return nullptr;

            } else {

                return Find_Removal(place -> left, _data);

            }

        }

    }
    
}

void Remove(Node* &seed, int _data) {

    if (seed == nullptr) {

        return;

    }

    Node* place = Find_Removal(seed, _data);
    Node* place_parent;

    if (place == nullptr) {

        return;

    }

    if ((place -> left == nullptr) && (place -> right == nullptr)) { // no children

        if (place -> parent == nullptr) {

            Node* temp = seed;
            seed = nullptr;
            delete temp;
            return;

        }

        place_parent = place -> parent;

        if (place_parent -> left == place) {

            place_parent -> left = nullptr;

        } else {

            place_parent -> right = nullptr;

        }
        
        delete place;
        return;

    } else if ((place -> left != nullptr) && (place -> right != nullptr)) { // two children

            Node* temp = place;

            temp = temp -> right; // shift once to right, then go all left

            while (temp -> left != nullptr) {

                temp = temp -> left;

            }

            place -> data = temp -> data;

            place_parent = temp -> parent;

            if (place_parent -> left == temp) {

                place_parent -> left = nullptr;

            } else {

                place_parent -> right = nullptr;

            }

            delete temp;
            
            return;

    } else { // one child

            if (place -> left != nullptr) {

                Node* temp = place -> left;

                place -> data = temp -> data;

                if (temp -> left == nullptr) {

                    place -> left = nullptr;

                } else {

                    place -> left = temp -> left;                
                    place -> left -> parent = place;

                }

                if (temp -> right == nullptr) {

                    place -> right = nullptr;

                } else {

                    place -> right = temp -> right;
                    place -> right -> parent = place;

                }

                delete temp;
                return;

            } else {

                Node* temp = place -> right;

                place -> data = temp -> data;

                if (temp -> left == nullptr) {

                    place -> left = nullptr;

                } else {

                    place -> left = temp -> left;
                    place -> left -> parent = place;

                }

                if (temp -> right == nullptr) {

                    place -> right = nullptr;

                } else {

                    place -> right = temp -> right;
                    place -> right -> parent = place;

                }

                delete temp;
                return;

            }

    }

}

void inOrder(std::vector<int> &output, Node* place) {

    if (place == nullptr) {

        return;

    } else {

        inOrder(output, place -> left);

        output.push_back(place -> data);

        inOrder(output, place -> right);

    }

}

void preOrder(std::vector<int> &output, Node* place) {

    if (place == nullptr) {

        return;

    } else {

        output.push_back(place -> data);

        preOrder(output, place -> left);

        preOrder(output, place -> right);

    }

}

void postOrder(std::vector<int> &output, Node* place) {

    if (place == nullptr) {

        return;

    } else {

        postOrder(output, place -> left);

        postOrder(output, place -> right);

        output.push_back(place -> data);

    }

}

void Traverse(std::ofstream&  _ofs, std::string _data, Node* place) {

    if (place == nullptr) {

        _ofs << "False" << std::endl;
        
        return;

    }

    std::vector<int> user_input;
    int num;

    std::istringstream istt(_data);

    while (istt >> num) {

        user_input.push_back(num);

    }

    std::vector<int> inorder_values;
    std::vector<int> preorder_values;
    std::vector<int> postorder_values; 

    bool inorder_match = true;
    bool preorder_match = true;
    bool postorder_match = true;

    inOrder(inorder_values, place);
    preOrder(preorder_values, place);
    postOrder(postorder_values, place);

    if (user_input.size() != inorder_values.size()) {

        _ofs << "False" << std::endl;

        return;

    } else {

        for (int i = 0; i < user_input.size(); ++i) {

            if (user_input[i] != inorder_values[i]) {

                inorder_match = false;

            }

            if (user_input[i] != preorder_values[i]) {

                preorder_match = false;

            }

            if (user_input[i] != postorder_values[i]) {

                postorder_match = false;

            }

        }

    }

    if (inorder_match) {

        _ofs << "Inorder" << std::endl;

    }

    if (preorder_match) {

        _ofs << "Preorder" << std::endl;

    }

    if (postorder_match) {

        _ofs << "Postorder" << std::endl;

    }

    if (!(inorder_match || preorder_match || postorder_match)) {

        _ofs << "False" << std::endl;

    }

}

#endif
