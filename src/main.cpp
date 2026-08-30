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
    return parts;
}

int main(){
   std::string command;

    while(true){
         std::cout << "\ntheown@terminal:" << fs::current_path() << "$";
          std:: getline(std::cin, command);
           
          if(command.empty()){
            continue;
          }

          std::vector<std::string> parts = splitCommand(command);
          std::string cmd = parts[0];
       
        if(command == "help"){
            showHelp();
        }
        else if(command == "pwd"){
            std::cout << fs::current_path() << "\n";
        }
        else if(command == "ls"){
            for(const auto& entry : fs::directory_iterator(fs::current_path())){
                std::cout << entry.path().filename().string() << "\n";
            }
        }
       
       else if(cmd == "cd"){
         if(parts.size() < 2){
            std::cout << "Usage: cd <directory>\n";
            continue;
            try{
                fs::current_path(parts[1]);
            }catch(const fs::filesystem_error & error){
                 std::cout << "Error: " << error.what() << "\n";
            }
         }
       } 
       
       else if(command == "echo"){
          for(size_t i = 1; i < parts.size() ; i++){
            std::cout << parts[i] << "";
          }
          std::cout << "\n";
       }
        else if(command == "clear"){
            system("clear");
        }
        else if(command == "exit"){
            std::cout << "GoodBye!\n";
            break;
        }else{
            std::cout << "Command not Found: " << command << "\n";
        }
   }
   return 0;
}