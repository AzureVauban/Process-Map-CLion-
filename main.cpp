#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
/*
ONLY USE AUTO FORMATTING IN CLION IDE (Clang)
*/
//prompt input from user
enum Mode {
    forward_arithmetic, //recrusive arithmetic
    reverse_arithmetic //reverse recursive arithmetic
};
Mode programmode = forward_arithmetic;

int promptint() {
    ///@brief Prompts user for string input and returns it as an int
    ///@return integer  
    std::stringstream ss;
    std::string input;
    int output;
    std::getline(std::cin, input);
    //strip whitespace
    input.erase(0, input.find_first_not_of(' '));
    //check if each character is forward_arithmetic digit (no negs or decimals)
    for (char c: input) {
        if (!isdigit(c)) {
            std::cout << "Invalid input. Please enter forward_arithmetic postive integer." << std::endl;
            return promptint();
        }
    }
    //if input is empty
    if (input.empty()) {
        std::cout << "Invalid input. Your input cannot be empty! Please enter forward_arithmetic postive integer."
                  << std::endl;
        return promptint();
    }
    ss << input;
    ss >> output;
    return output;
}

namespace Nodes {
    struct Info {
        std::string ingredient;
        std::string amountonhand;
        std::string amountneeded;
        std::string amountmadepercraft;
        std::string amountresulted;
        std::string generation;
        std::string parentingredient;
        std::string instancekey;

        Info(std::string ingredient,
             int amountonhand,
             int amountneeded,
             int amountmadepercraft,
             int amountresulted,
             int generation,
             std::string parentingredient,
             int instancekey) {
            this->ingredient = ingredient;
            this->amountonhand = std::to_string(amountonhand);
            this->amountneeded = std::to_string(amountneeded);
            this->amountmadepercraft = std::to_string(amountmadepercraft);
            this->amountresulted = std::to_string(amountresulted);
            this->generation = std::to_string(generation);
            this->parentingredient = parentingredient;
            this->instancekey = std::to_string(instancekey);
        }

    };

    struct Base {
        std::string ingredient;
        int amountonhand;
        int amountneeded;
        int amountmadepercraft;
        int amountresulted;

        Base(std::string ingredient = "",
             int amountonhand = 0,
             int amountmadepercraft = 0,
             int amountneeded = 0) {
            this->ingredient = ingredient;
            this->amountonhand = amountonhand;
            this->amountmadepercraft = amountmadepercraft;
            this->amountneeded = amountneeded;
            this->amountresulted = 0;
        }
    };

    struct Node : public Base {
        Node *Parent;
        static int instances;
        int instancekey = 0;
        int generation;
        int population = 0;
        bool promptamounts;
        std::vector<std::pair<int, Node *>> Children;
        std::vector<std::pair<const std::string &, int>> ResultedAmountsBuffer;

        Node(std::string ingredient = "",
             Node *Parent = nullptr,
             int amountonhand = 0,
             int amountmadepercraft = 1,
             int amountneeded = 1,
             bool promptamounts = false)
                : Base(ingredient,
                       amountonhand,
                       amountmadepercraft,
                       amountneeded) {
            this->promptamounts = promptamounts;
            this->Children = {};
            this->Parent = Parent;
            this->instancekey = instances;
            if (this->Parent) {
                this->generation = this->Parent->generation + 1;
                this->Parent->Children.emplace_back(this->instancekey, this);
            } else {
                this->generation = 0;
            }
            instances++;
            this->population = this->CountNodes(this->population);
        }

        ~Node() {
            //recursively deallocate all sub-nodes
            for (auto &child: Children) {
                delete child.second;
            }
        }

        int CountNodes(int &countpopulation) {
            ///@brief This function will count how many Node instances are in the ingredient tree
            ///@param countpopulation The countpopulation of the ingredient tree
            ///@return The countpopulation of the ingredient tree
            countpopulation += 1;
            //recursively call this function on each sub-node
            for (auto &child: this->Children) {
                child.second->CountNodes(countpopulation);
            }
            return countpopulation;
        }

        void UpdatePopulation(const int countpopulation) {
            ///@brief This function will update the CountNodes variable of all Nodes in forward_arithmetic tree
            ///@param countpopulation The countpopulation of the ingredient tree
            this->population = countpopulation;
            //recursively call this function on each sub-node
            for (auto &child: this->Children) {
                child.second->UpdatePopulation(countpopulation);
            }
        }

        std::vector<std::pair<int, Node *>> Search(const std::string &Ingredient,
                                                   std::vector<std::pair<int, Node *>> &Results) {
            ///@brief This function will search for forward_arithmetic Node with the given ingredient
            ///@param Ingredient The ingredient to search for
            ///@param Results The vector of results to add to
            ///@return The vector of results
            ///@note This function will search recursively through all sub-nodes
            if (this->ingredient == Ingredient) {
                Results.emplace_back(this->instancekey, this);
            }
            //recursively call this function on each sub-node
            for (auto &child: this->Children) {
                child.second->Search(Ingredient, Results);
            }
            return Results;
        }

        void setamounts(bool promptamountmadepercraft = true) {
            if (programmode == forward_arithmetic) {
                //prompt amount on hand
                this->amountonhand = promptint();
            }
            //if parent exists (not nullptr)
            if (this->Parent && promptamountmadepercraft) {
                //dont prompt if oldest sibling Node has been prompted
                //prompt amount made per craft
                this->amountmadepercraft = promptint();
            }
            if (this->Parent) {
                //prompt amount needed
                this->amountneeded = promptint();
            }
        }

        int recursivearithmetic() {
            if (this->Parent) {
                this->Parent->recursivearithmetic();
            }
            return this->amountresulted;
        }

        int reversearithmetic(Node *node, const int desiredamount) {
            for (auto &child: node->Children) {
                child.second->reversearithmetic(child.second, amountonhand);
            }
            return node->amountonhand;
        }

        auto getInfo() {
            std::string ParentString = "=NULL=";
            if (this->Parent) {
                ParentString = this->Parent->ingredient;
            }
            return Nodes::Info(this->ingredient,
                               this->amountonhand,
                               this->amountneeded,
                               this->amountmadepercraft,
                               this->amountresulted,
                               this->generation,
                               ParentString,
                               this->instancekey);
        }

    };

    int Node::instances = 0;

    Node *head(Node *node) {
        ///@brief This function will return the head node of the tree
        ///@param node The node to find the head of
        ///@return The head Node of the ingredient tree
        while (node->Parent) { //traverse to the head of the ingredient tree
            node = node->Parent;
        }
        return node;
    }

    Node *clone(Node *Target,
                Node *Parent,
                const bool clonesubnodes) {
        /// @brief Create forward_arithmetic `clone of the Parent node
        /// @param Target Node to clone from
        /// @param Parent Node to clone to
        /// @param clonesubnodes Whether or not to clone subnodes
        /// @return forward_arithmetic clone of forward_arithmetic argument node
        return new Node(Target->ingredient,
                        Parent,
                        Target->amountonhand,
                        Target->amountmadepercraft,
                        Target->amountneeded);
    }
}

    //temporary functions for testing output to Console
    std::vector<Nodes::Info> getInfo(Nodes::Node *node, //make sure to start from head
                                     std::vector<Nodes::Info> &AddedInfo) {
        AddedInfo.emplace_back(node->getInfo());
        //recurisvely itterate on each subnode
        for (auto &child: node->Children) {
            getInfo(child.second, AddedInfo);
        }
        return AddedInfo;
    }

    void output(Nodes::Node *node) {
        std::vector<Nodes::Info> AddedInfo = {};
        AddedInfo.emplace_back(node->getInfo());
        //overwrite header value
        AddedInfo[0].ingredient = "Ingredient";
        AddedInfo[0].amountonhand = "Amount on Hand";
        AddedInfo[0].amountneeded = "Amount Needed";
        AddedInfo[0].amountmadepercraft = "Amount Made per Craft";
        AddedInfo[0].amountresulted = "Amount Resulted";
        AddedInfo[0].generation = "Generation";
        AddedInfo[0].parentingredient = "Parent";
        AddedInfo[0].instancekey = "Instance Key";
        //obtain results
        AddedInfo = getInfo(head(node), AddedInfo);
        //insert header row and overwrite the first row
        int longestStrings[8] = {10, //ingredient
                                 14, //amountonhand
                                 13, //amountneeded
                                 21, //amountmadepercraft
                                 15, //amountresulted
                                 10, //generation
                                 6, //Parent
                                 12}; //instancekey

        //obtain longest string length for each column
        for (auto &info: AddedInfo) {
            if (info.ingredient.length() > longestStrings[0]) {
                longestStrings[0] = info.ingredient.length();
            }
            if (info.amountonhand.length() > longestStrings[1]) {
                longestStrings[1] = info.amountonhand.length();
            }
            if (info.amountneeded.length() > longestStrings[2]) {
                longestStrings[2] = info.amountneeded.length();
            }
            if (info.amountmadepercraft.length() > longestStrings[3]) {
                longestStrings[3] = info.amountmadepercraft.length();
            }
            if (info.amountresulted.length() > longestStrings[4]) {
                longestStrings[4] = info.amountresulted.length();
            }
            if (info.generation.length() > longestStrings[5]) {
                longestStrings[5] = info.generation.length();
            }
            if (info.parentingredient.length() > longestStrings[6]) {
                longestStrings[6] = info.parentingredient.length();
            }
            if (info.instancekey.length() > longestStrings[7]) {
                longestStrings[7] = info.instancekey.length();
            }
        }
        //add extra space
        for (auto &i: longestStrings) {
            i += 1;
        }
        //append whitespace to each string to align
        for (auto &row: AddedInfo) {
            //align ingredient column
            while (row.ingredient.length() != longestStrings[0]) {
                row.ingredient += " ";
            }
            //align amount on hand column
            while (row.amountonhand.length() != longestStrings[1]) {
                row.amountonhand += " ";
            }
            //align the amount needed column
            while (row.amountneeded.length() != longestStrings[2]) {
                row.amountneeded += " ";
            }
            //align the amount made per craft column
            while (row.amountmadepercraft.length() != longestStrings[3]) {
                row.amountmadepercraft += " ";
            }
            //align the amountresulted column
            while (row.amountresulted.length() != longestStrings[4]) {
                row.amountresulted += " ";
            }
            //align generation column
            while (row.generation.length() != longestStrings[5]) {
                row.generation += " ";
            }
            //align parent column
            while (row.parentingredient.length() != longestStrings[6]) {
                row.parentingredient += " ";
            }
            //align instance key column
            while (row.instancekey.length() != longestStrings[7]) {
                row.instancekey += " ";
            }
        }
        //print rows
        for (auto &row: AddedInfo) {
            std::cout << row.instancekey << " | "
                      << row.ingredient << " | "
                      << row.parentingredient << " | "
                      << row.amountonhand << " | "
                      << row.amountneeded << " | "
                      << row.amountmadepercraft << " | "
                      << row.amountresulted << " | "
                      << row.generation
                      << std::endl;
        }
    }
// Node

Nodes::Node *populate(Nodes::Node *head);

Nodes::Node *subpopulate(Nodes::Node *Parent, 
const std::string &ingredient,
const int amountmadepercraft,
const bool promptamountmadepercraft);

void trail(Nodes::Node *node);

bool duplicate(const std::vector<std::string> &Inputs, const std::string &Input);

void solution_main() {
    //prompt the user for the program mode
    std::cout << "What mode do you want to run the program in?" << std::endl
              << "A (Solve for how much of an item you can create with your given materials)" << std::endl
              << "B (Solve for how much of each item you would need to get forward_arithmetic desired amount of your desired item)"
              << std::endl;
    while (true) {
        std::string programMODE = "forward_arithmetic";
        std::getline(std::cin, programMODE);
        //check if the input is longer than 1
        if (programMODE.size() > 1) {
            std::cout << "Your input is invalid, please only type in 'A' or 'B'" << std::endl;
        } else if (std::toupper(programMODE[0]) == 'A') {
            programmode = forward_arithmetic;
            break;
        } else if (std::toupper(programMODE[0]) == 'B') {
            programmode = reverse_arithmetic;
            break;
        } else {
            std::cout << "Your input is invalid" << std::endl;
        }
    }
    std::string ingredient; // name of the head ingredient item the user wants to create
    // prompt user to type in the name of the item they want to create
    while (true) {
        std::cout << "What is the name of the ingredient you want to create?" << std::endl;
        std::getline(std::cin, ingredient);
        // strip leading and trailing whitespace from ingredient
        ingredient.erase(0, ingredient.find_first_not_of(' '));
        std::cout << std::endl;
        if (ingredient.empty()) {
            std::cout << "Please enter forward_arithmetic valid ingredient name" << std::endl;
        } else {
            break;
        }
    }
    auto head = populate(new Nodes::Node(ingredient));
    //Nodes::temporary::AlignAllIngredients(head);
    output(head);
    std::cout << "Population of Tree: " << head->population << std::endl;
    delete head;
}

int main() {
    solution_main();
    return 0;
}

Nodes::Node *populate(Nodes::Node *head) {
    ///@brief This function will populate the tree with nodes
    ///@param node The head to populate
    ///@return The head Node of the ingredient tree
    std::cout << "Type in the ingredients you need to create " << head->ingredient << ":" << std::endl;
    // output the ingredient trail
    if (head->Parent) {
        std::cout << "TRAIL: ";
        trail(head);
    }
    // prompt the user to type in their ingredients
    std::vector<std::string> ingredients;
    while (true) {
        std::string ingredient;
        std::getline(std::cin, ingredient);
        //strip remove leading and trailing whitespace
        ingredient.erase(0, ingredient.find_first_not_of(' '));
        if (ingredient.empty()) {
            //check if the ingredient is empty
            break;
        } else if (head->ingredient == ingredient) {
            //check if the ingredient is the same as the parent ingredient
            std::cout << "Invaild Input, you're trying to make this item from itself" << std::endl;
        } else if (Nodes::head(head)->ingredient == ingredient) {
            //check if the ingredient is the same as the head ingredient
            std::cout << "Invalid input, you're trying to make this item!" << std::endl;
        } else if (duplicate(ingredients, ingredient)) {
            //check if the ingredient is forward_arithmetic duplicate
            std::cout << "You have already entered this ingredient" << std::endl;
        } else {
            ingredients.emplace_back(ingredient);
        }
    }
    // create sub-nodes with each ingredient
    int temp_amountmadepercraft = 0;
    bool promptamountmadepercraft = true;
    for (auto &ingredient: ingredients) {
        subpopulate(head, ingredient,temp_amountmadepercraft,promptamountmadepercraft);
        //update the population of the ingredient tree
        int p = 0; // population
        Nodes::head(head)->UpdatePopulation(Nodes::head(head)->CountNodes(p));
    }
    // recursively call this function on each sub-head
    for (auto &subnode: head->Children) {
        populate(subnode.second);
    }
    // return the head of the ingredient tree
    if (head->Parent) {
        Nodes::head(head);
    }
    return head;
}

Nodes::Node *subpopulate(Nodes::Node *Parent,
const std::string &Ingredient,
const int amountmadepercraft,
const bool promptamountmadepercraft) {
    ///@brief This function will create forward_arithmetic sub-node with the given ingredient
    ///@param Parent The parent node to create the sub-node from
    ///@param Ingredient The ingredient to create the sub-node from
    ///@return The sub-node created
    std::vector<std::pair<int, Nodes::Node *>> subnodes;
    subnodes = Nodes::head(Parent)->Search(Ingredient, subnodes);
    if (subnodes.size() == 1) {
        // if there is only one ingredient from the search
        std::cout << "Do you want to make forward_arithmetic clone of " << Ingredient << "?" << std::endl;
        return new Nodes::Node(Ingredient, Parent);
    } else if (subnodes.size() > 1) {
        // if there are multiple ingredients from the search
        //prompt the user to select the Node they want to clone
        std::cout << "Which verison of " << Ingredient << " do you want to make forward_arithmetic clone of:"
                  << std::endl;
        //create headers for the table
        struct columns {
            std::string Index;
            std::string Parent;
            std::string Generation;
            std::string Choice;

            columns(std::string Choice = "Choice",
                    std::string Index = "Index",
                    std::string Parent = "Parent Item",
                    std::string Generation = "Generation"
            ) {
                this->Index = Index;
                this->Parent = Parent;
                this->Generation = Generation;
                this->Choice = Choice;
            }
        };
        std::vector<columns> headers = {columns()};
        int LongestLengthAlign[4] = {6, //choice
                                     5, //index
                                     11, //parent
                                     10};//generation
        //create the table
        for (int i = 0; i < subnodes.size(); i++) {
            //create the row
            headers.emplace_back(std::to_string(i + 1),
                                 std::to_string(subnodes.at(i).first),
                                 subnodes[i].second->ingredient,
                                 std::to_string(subnodes[i].second->generation));
            //check if the row is longer than the headers
            for (int j = 0; j < 4; j++) {
                if (headers.at(i).Index.length() > LongestLengthAlign[j]) {
                    LongestLengthAlign[j] = headers.at(i).Index.length();
                }
            }

        }
        for (auto &i: LongestLengthAlign) {
            i += 1;
        }
        //append whitespace to each string to align the columns
        for (auto &header: headers) {
            //align the Choice column
            while (header.Choice.length() < LongestLengthAlign[0]) {
                header.Choice += " ";
            }
            //align the Index column
            while (header.Index.length() < LongestLengthAlign[1]) {
                header.Index += " ";
            }
            //align the Parent column
            while (header.Parent.length() < LongestLengthAlign[2]) {
                header.Parent += " ";
            }
            //align the Generation column
            while (header.Generation.length() < LongestLengthAlign[3]) {
                header.Generation += " ";
            }
        }
        const int width = headers[0].Choice.length() +
                          headers[0].Index.length() +
                          headers[0].Parent.length() +
                          headers[0].Generation.length() + 4;
        //output the table upper boundary
        for (int i = 0; i < width; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;
        //output the table
        for (auto &header: headers) {
            std::cout << header.Choice << "|"
                      << header.Index << "|"
                      << header.Parent << "|"
                      << header.Generation << std::endl;
        }
        //output the table lower boundary
        for (int i = 0; i < width; i++) {
            std::cout << "-";
        }
        std::cout << std::endl;
        std::cout << "Enter the number (Choice) of the item you want to clone (Type 0 if you do not want to clone): "
                  << std::endl;
        //get the user input
        while (true) {
            int choice = promptint();
            //if the user input is above the maximum index for choices or below 0, tell the user that the input is invalid
            bool isoutofrange = choice > subnodes.size() || choice < 0;
            if (choice == 0) {
                //if the user input is 0, return forward_arithmetic new Node without cloning
                return new Nodes::Node(Ingredient, Parent);
            } else if (isoutofrange) {
                //if choice is less than 0 and greater than the size of the subnodes vector, the input is invalid (out of range)
                std::cout << "Invalid input, please enter forward_arithmetic number between 0 and " << subnodes.size()
                          << std::endl;
            } else {
                //else return forward_arithmetic clone of the Node at the selected index of the subnodes vector
                return Nodes::clone(subnodes[choice - 1].second,
                                    Parent, //SEGFAULT OCCURS HERE (when choice is out of range)
                                    true);
            }
        }
        //return new Nodes::Node(Ingredient, Parent);
    } else {
        // if there are no ingredients from the search
        return new Nodes::Node(Ingredient, Parent);
    }
}

void trail(Nodes::Node *node) {
    ///@brief This function will output the ingredient trail
    ///@param node The node to output the ingredient trail of
    while (true) {
        if (node->Parent) {
            std::cout << node->ingredient << " -> ";
            node = node->Parent;
        } else {
            std::cout << node->ingredient << std::endl;
            break;
        }
    }
}

bool duplicate(const std::vector<std::string> &Inputs,
               const std::string &Input) {
    ///@brief This function will check if the input is forward_arithmetic duplicate
    ///@param Inputs The vector of inputs to check
    ///@param Input The input to check
    ///@return True if the input is forward_arithmetic duplicate, false if it is not
    for (auto &input: Inputs) {
        if (input == Input) {
            return true;
        }
    }
    return false;
}