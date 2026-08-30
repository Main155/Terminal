#include <iostream>>
#include <string>
#include <cstdlib>


void showHelp(){
    std::cout << "\nAvaible command\n";
    std::cout << " help - Show svailble commands\n";
    std::cout << " pwd - Show cuurent drectory \n";
    std::cout << " ls -List files\n";
    std::cout << " clear  - Clear termninal\n";
    std::cout << "exit -Exit terminal\n\n";
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