int lineNum = 0; // Keep track of the current line number
#include "core.cpp"
int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "incorrect usage" << std::endl;
        std::cerr << "Correct is \"neo <file.neo>\"";
        return EXIT_FAILURE;
    }

    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);

        if (!input)
        {
            std::cerr << "Failed to open the file." << std::endl;
            return EXIT_FAILURE;
        }

        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    std::stringstream line_stream(contents); // Create a stream to read lines
    // ...

    std::string line;
    
    while (std::getline(line_stream, line))
    {
        if (line.empty() || line.substr(0, 3) == "<->")
        {
            continue; // Skip lines that start with a comment character
        }
        executeCustomCode(line,argv,contents); // Execute the line as custom code
    }

    // ...

    if (!hasExitValue)
    {
        std::cerr << "No exit value provided. Infinite loop would occur." << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        return exit_val;
    }

    return EXIT_SUCCESS;
}
