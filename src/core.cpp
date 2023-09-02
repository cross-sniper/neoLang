// core.cpp

#include "macros.h" // Define the language macros here

using namespace std;

std::map<std::string, int> vars; // Storage for variables
std::map<std::string, std::vector<std::any>> arrays;

bool hasExitValue = false;
int exit_val = 0;

// Function to execute a line of custom code
void executeCustomCode(const std::string &line, const char *argv[],const auto contents)//the contents variable here, is the full content of the file given to it
{
   if (line.substr(0, 6) == "print ")
{
    std::string varName = line.substr(6);
    
    // Check if it's a variable
    if (vars.find(varName) != vars.end())
    {
        echo(std::to_string(vars[varName]));
    }
    // Check if it's an array
    else if (arrays.find(varName) != arrays.end())
    {
        std::vector<std::any> &elements = arrays[varName];
        for (const auto &element : elements)
        {
            // Handle each element's type
            if (element.type() == typeid(int))
            {
                echo(std::to_string(std::any_cast<int>(element)));
            }
            else if (element.type() == typeid(std::string))
            {
                echo(std::any_cast<std::string>(element));
            }
            // Add more type checks as needed for other types
            else if (element.type() == typeid(float))
            {
                echo(std::to_string(std::any_cast<float>(element)));
            }
            else if (element.type() == typeid(double))
            {
                echo(std::to_string(std::any_cast<double>(element)));
            }
            // Handle other types as necessary
            else
            {
                std::cerr << "Unsupported element type in array: " << varName << std::endl;
            }
        }
    }
    else if (line.find("'") != std::string::npos || line.find("\"") != std::string::npos)
    {
        // Handle strings enclosed in single or double quotes
        size_t firstQuotePos = line.find_first_of("'\"");
        size_t lastQuotePos = line.find_last_of("'\"");

        if (firstQuotePos != std::string::npos && lastQuotePos != std::string::npos && firstQuotePos != lastQuotePos)
        {
            std::string stringValue = line.substr(firstQuotePos + 1, lastQuotePos - firstQuotePos - 1);
            echo(stringValue);
        }
        else
        {
            std::cerr << "Malformed string: " << line << std::endl;
        }
    }
    else
    {
        std::cerr << "Variable or array not found: " << varName << std::endl;
    }
}else if (line.substr(0, 3) == "jmp")
{
    std::string target = line.substr(4); // Extract the target line number or label
    int targetLine = std::stoi(target); // Convert the target to an integer

    // Implement logic to set the execution pointer to the target line
    lineNum = targetLine - 1; // Adjust the line number to jump to (subtract 1 because it will be incremented in the loop)
}

    else if (line.substr(0, 5) == "exit ")
    {
        exit_val = std::stoi(line.substr(5)); // Convert exit value to integer
        hasExitValue = true;
        // You can extract the exit value and perform validation here
    }
    else if (line.substr(0, 4) == "set ")
    {
        std::stringstream ss(line.substr(4));
        std::string varName;
        int varValue;
        ss >> varName >> varValue;
        if (!ss.fail())
        {
            vars[varName] = varValue;
        }
        else
        {
            std::cerr << "Invalid variable assignment: " << line << std::endl;
        }
    }
    else if (line.substr(0, 4) == "add ")
    {
        std::stringstream ss(line.substr(4));
        std::string varName;
        int varValue;
        ss >> varName >> varValue;
        if (!ss.fail())
        {
            if (vars.find(varName) != vars.end())
            {
                vars[varName] += varValue;
            }
            else
            {
                std::cerr << "Variable not found: " << varName << std::endl;
            }
        }
        else
        {
            std::cerr << "Invalid command syntax: " << line << std::endl;
        }
    }
    else if (line.substr(0, 4) == "dec ")
    {
        std::stringstream ss(line.substr(4));
        std::string varName;
        int varValue;
        ss >> varName >> varValue;
        if (!ss.fail())
        {
            if (vars.find(varName) != vars.end())
            {
                vars[varName] -= varValue;
            }
            else
            {
                std::cerr << "Variable not found: " << varName << std::endl;
            }
        }
        else
        {
            std::cerr << "Invalid command syntax: " << line << std::endl;
        }
    }
    else if (line.substr(0, 4) == "div ")
    {
        std::stringstream ss(line.substr(4));
        std::string varName;
        int varValue;
        ss >> varName >> varValue;
        if (!ss.fail())
        {
            if (vars.find(varName) != vars.end())
            {
                vars[varName] /= varValue;
            }
            else
            {
                std::cerr << "Variable not found: " << varName << std::endl;
            }
        }
        else
        {
            std::cerr << "Invalid command syntax: " << line << std::endl;
        }
    }
    else if (line.substr(0, 4) == "mul ")
    {
        std::stringstream ss(line.substr(4));
        std::string varName;
        int varValue;
        ss >> varName >> varValue;
        if (!ss.fail())
        {
            if (vars.find(varName) != vars.end())
            {
                vars[varName] *= varValue;
            }
            else
            {
                std::cerr << "Variable not found: " << varName << std::endl;
            }
        }
        else
        {
            std::cerr << "Invalid command syntax: " << line << std::endl;
        }
    }
    else if (line.substr(0, 4) == "mod ")
    {
        std::stringstream ss(line.substr(4));
        std::string varName;
        int varValue;
        ss >> varName >> varValue;
        if (!ss.fail())
        {
            if (vars.find(varName) != vars.end())
            {
                vars[varName] %= varValue;
            }
            else
            {
                std::cerr << "Variable not found: " << varName << std::endl;
            }
        }
        else
        {
            std::cerr << "Invalid command syntax: " << line << std::endl;
        }
    }
    else if (line.substr(0, 6) == "clear ")
    {
        std::string varName = line.substr(6);
        if (vars.find(varName) != vars.end())
        {
            vars.erase(varName);
        }
        else
        {
            std::cerr << "Variable not found: " << varName << std::endl;
        }
    }
    else if (line.substr(0, 4) == "err ")
    {
        std::stringstream ss(line.substr(4));
        int err_code;
        ss >> err_code;
        if (!ss.fail())
        {
            // Implement or replace with appropriate error handling
            exit(err_code);
        }
        else
        {
            std::cerr << "Invalid error code: " << line << std::endl;
        }
    }
    else if (line.substr(0, 5) == "uses ")
    {
        std::string file_name = line.substr(5);

        // Get the directory of the current script
        std::string script_directory = argv[1];
        size_t last_slash_pos = script_directory.find_last_of("/\\");
        if (last_slash_pos != std::string::npos)
        {
            script_directory = script_directory.substr(0, last_slash_pos + 1);
        }

        std::string full_path = script_directory + file_name;

        do
        {
            std::string file_contents;
            {
                std::ifstream input(full_path);
                if (!input.is_open())
                {
                    std::cerr << "Failed to open the file: " << full_path << std::endl;
                }
                else
                {
                    std::stringstream contents_stream;
                    contents_stream << input.rdbuf();
                    file_contents = contents_stream.str();
                    /* Process file_contents or execute it within the Neo context */
                    executeCustomCode(file_contents,argv,contents);
                }
            }
        } while (0);
    }

else if (line.substr(0, 4) == "arr ")
{
    std::string arrayDeclaration = line.substr(4);

    // Parse the array declaration to extract the array name and elements (if any)
    size_t spacePos = arrayDeclaration.find(' ');
    if (spacePos != std::string::npos)
    {
        std::string arrayName = arrayDeclaration.substr(0, spacePos);
        std::string arrayElements = arrayDeclaration.substr(spacePos + 1);

        // Now, you have the array name and elements; you can process them as needed.
        // For example, you can split the elements and store them in a vector data structure.

        // Example: Split elements by ',' and store them in a vector of std::any
        std::vector<std::any> elements;
        size_t startPos = 0;
        size_t commaPos = arrayElements.find(',');
        while (commaPos != std::string::npos)
        {
            std::string elementStr = arrayElements.substr(startPos, commaPos - startPos);
            
            // Use std::any to store the element with its original type
            try {
                int intValue = std::stoi(elementStr);
                elements.push_back(intValue);
            } catch (const std::invalid_argument&) {
                // If it's not an integer, store it as a string
                elements.push_back(elementStr);
            }
            
            startPos = commaPos + 1;
            commaPos = arrayElements.find(',', startPos);
        }
        // Don't forget the last element (no ',' after it)
        std::string lastElementStr = arrayElements.substr(startPos);
        try {
            int intValue = std::stoi(lastElementStr);
            elements.push_back(intValue);
        } catch (const std::invalid_argument&) {
            // If it's not an integer, store it as a string
            elements.push_back(lastElementStr);
        }

        // Now, you have 'arrayName' and 'elements' vector ready for further processing.
        // Store the vector of std::any in the 'arrays' map with 'arrayName'.

        // Store the array in the 'arrays' map
        arrays[arrayName] = elements;
    }
    else
    {
        std::cerr << "Invalid array declaration: " << line << std::endl;
    }
}

    else
    {
        echo(line + " not recognized")
    }
}
