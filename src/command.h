#pragma once

#include <unordered_map>
#include <vector>
#include <functional>
#include <chrono>
#include <thread>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <limits>

namespace command
{
	[[nodiscard]] inline bool exists(const std::string& filename)
	{
		if (!std::filesystem::exists(filename))
		{
			return false;
		}
		return true;
	}

	static std::unordered_map<std::string,
		std::function<void(const std::vector<std::string>&)>> command =
	{
		{"mkdir", [](const std::vector<std::string>& args)   // Create directory
		{
			if (args.size() < 2)
			{ //Length
				std::cerr << "Usage: mkdir <dirname>\n";
				return; //Prompt
			}
			std::error_code ec;
			if (std::filesystem::create_directory(args[1], ec))
			{
			   std::cout << "Directory created.\n";
			}
			else
			{
				std::cerr << "Error: " << ec.message() << "\n"; //error
			}
		}},

		{"ls",[](const std::vector<std::string>&)//List files
		{
			for (const auto& entry : std::filesystem::directory_iterator(std::filesystem::current_path()))
			{
			   std::cout << entry.path().filename().string() << "\n";                //print
			}
		}},

		{"pwd", [](const std::vector<std::string>&)
		{
			std::error_code ec;                    // Show current path
			auto path = std::filesystem::current_path(ec);
			if (ec)
			{
				std::cerr << "Error: " << ec.message() << "\n"; //error
				return;
			}
			std::cout << path.string() << "\n";  //print
		}},

		{"help", [](const std::vector<std::string>&)   //help
		{
			std::cout << "Available commands:\n";
			std::cout << "  mkdir <dir>    Create directory\n";
			std::cout << "  ls             List files\n";
			std::cout << "  pwd            Show current path\n";
			std::cout << "  touch <file>   Create empty file\n";
			std::cout << "  cat <file>     Show file content\n";
			std::cout << "  rm <file>      Remove file\n";
			std::cout << "  rmdir <dir>    Remove empty directory\n";
			std::cout << "  cd <path>      Change directory\n";
			std::cout << "  echo <text>    Print text\n";
			std::cout << "  exit            Exit the program\n";
			std::cout << "  cls            Clear screen\n";
			std::cout << "  sleep <s>      Sleep for seconds\n";
		}},

		{"cls",[](const std::vector<std::string>&)  //Clear screen
		{
			  std::cout << "\033[2J\033[3J\033[H" << std::flush;//clear            
		}},

		{"sleep", [](const std::vector<std::string>& args)
		{
		if (args.size() < 2) {            //Length
			std::cerr << "Usage: sleep <seconds>\n";
			return;
		}
		try {
			long long time = std::stoll(args[1]);
			if (time <= 0)
			{    //Length
				std::cerr << "Error: positive number required\n";
				return;
			}
			std::this_thread::sleep_for(std::chrono::seconds(time));   //s
			std::cout << "Done\n";
			}
			catch (const std::exception&)
			{
			std::cerr << "Error: invalid number\n";  //error
		}
		}},

		{"touch", [](const std::vector<std::string>& args)  //create
		{
			if (args.size() < 2)
			{
				std::cerr << "Usage: touch <filename>\n";
				return;
			}
			std::ofstream file(args[1]);
			if (!file)
			{
				std::cerr << "Error: unable to create file\n";
				return;
			}
			std::cout << "File created\n";
		}},

		{"cd", [](const std::vector<std::string>& args) // Change directory
		{
		   if (args.size() < 2)
		   {
			   // Length 
			   std::cerr << "Usage: cd <path>\n";
			   return;
			}
			std::error_code ec;
			std::filesystem::current_path(args[1], ec);
			if (ec)
			{
				std::cerr << "Error: " << ec.message() << "\n"; //error
			}
			else
			{
				std::cout << "Changed directory to " << args[1] << "\n";
			}
		}},
		{ "cat", [](const std::vector<std::string>& args)
		{    //Show file content
			if (args.size() < 2)
			{
				std::cerr << "Usage: cat <filename>\n";
				return;
			}
			if (!exists(args[1]))
			{
				std::cerr << "ERR:The file does not exist.\n";
				return;
			}
			std::ifstream file(args[1]);
			if (!file)
			{
				std::cerr << "Error: unable to open file\n";
				return;
			}
			std::string line;
			while (std::getline(file, line))
			{
				std::cout << line << "\n";
			}
		} },

		{ "rm", [](const std::vector<std::string>& args)
		{   //delete file
			if (args.size() < 2)
			{
				std::cerr << "Usage: rm <filename>\n";
				return;
			}
			if (!exists(args[1]))
			{
				std::cerr << "ERR:The file does not exist.\n";
				return;
			}
			std::error_code ec;
			std::string option;
			std::cout << "Are you sure you want to delete " << args[1] << "? (T/F): ";
			std::getline(std::cin, option);
			if (option == "F")
			{
				std::cout << "Operation canceled successfully\n";
				return;   //F
			}
			if (option == "T")
			{
				std::filesystem::remove(args[1], ec);
				std::cout << "Removed\n";
				return;
			}
			else
			{
				std::cerr << "Error: invalid input\n";  //error
			}
		}},

		{ "rmdir", [](const std::vector<std::string>& args)
		{     //delete dir
			if (args.size() < 2)
			{
				//Length
				std::cerr << "Usage: rmdir <dir>\n";
				return;
			}
			std::error_code ec;
			if (std::filesystem::remove(args[1], ec))
			{
				std::cout << "Directory removed\n";
			}
			else
			{
				std::cerr << "Error: " << ec.message() << "\n"; //error
			}
		} },
		{ "echo", [](const std::vector<std::string>& args)
		{
			std::string out;
			for (size_t i = 1; i < args.size(); ++i) out += args[i] + " ";
			std::cout << out << "\n";
		}},

	};

	inline void return_command()
	{
		std::string input;

		while (true)
		{
			std::vector<std::string> parts;
			std::cout << "\ntheown@terminal:" << std::filesystem::current_path() << "$";
			if (!std::getline(std::cin, input))
			{
				std::cerr << "Error: failed to read input\n";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				continue;
			}

			if (input.empty())
			{
				std::cerr << "Error: command cannot be empty\n";
				continue;
			}

			if (input == "exit")
			{
				std::cout << "GoodBye!\n";
				break;
			}
			std::istringstream iss(input);
			std::string part;
			while (iss >> part)
			{
				parts.push_back(part);
			}

			auto cmd = command.find(parts[0]);
			if (cmd != command.end())
			{
				cmd->second(parts);
			}
			else
			{
				std::cerr << "Error: command not found\n";
			}
		}
	}
}
