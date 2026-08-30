#include <iostream>>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <vector>

namespace fs = std::filesystem;

void showHelp(){
    std::cout << "\nAvaible command\n";
    std::cout << " help - Show svailble commands\n";
    std::cout << " pwd - Show cuurent drectory \n";
    std::cout << " ls -List files\n";
    std::cout << "cd <directory> Change Directory";
    std:: cout << "echo <text> Print Print text\n";
    std::cout << " clear  - Clear termninal\n";
    std::cout << "exit -Exit terminal\n\n";
}

std::vector<std::string>splitCommand(const std::string & command){
    std::stringstream ss (command);
    std::vector<std::string>parts;
    std::string word;

    while(ss >> word){
        parts.push_back(word);
    }
}

int main(){
    std::string command;

    while(true){
        std::cout << "jihad@terminal:~$";
        std:: getline(std::cin, command);
        
        if(command == "help"){
            showHelp();
        }
        else if(command == "pwd"){
            system("pwd");
        }
        else if(command == "ls"){
            system("ls");
        }
        else if(command == "clear"){
            system("clear");
        }
        else if(command == "exit"){
            std::cout << "GoodBye!\n";
            break;
        }else if (command.empty()){
            continue;
        }else{
            std::cout << "Command not Found";
        }
   }
   return 0;
}