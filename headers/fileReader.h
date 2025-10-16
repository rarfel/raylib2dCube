#pragma once

#include <fstream>
#include <iostream>
#include <vector>

/* A split function, the original can be found here https://ideone.com/1RCZM8*/
size_t SplitStrings(const std::string &txt, std::vector<std::string> &strs, char ch)
{
    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();
 
    // Decompose statement
    while( pos != std::string::npos )
    {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;
 
        pos = txt.find(ch, initialPos);
    }
 
    // Add the last one
    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));
 
    return strs.size();
}

// function that gets a .obj file and extracts its vertices and faces
std::vector<Vector3> ReadOBJFile(std::string filepath)
{
    std::string fileContent;
    std::vector<std::string> variables;
    std::vector<Vector3> verticesOBJ;
    const int verticesCounter = 3;
    float vertices[verticesCounter];
    int index = 0;

    // Read from the text file
    std::ifstream readFile(filepath);

    while (std::getline(readFile, fileContent))
    {
        SplitStrings(fileContent, variables, ' ');
        // Identifying if its reading the vertices
        if(fileContent[0] == 'v' and fileContent[1] == ' ')
        {
            for(auto iter : variables)
                if(iter[0] != 'v')
                {
                    if(index < verticesCounter)
                    {
                        vertices[index] = std::stof(iter);
                        index++;
                    }
                    if(index == verticesCounter)
                    {
                        verticesOBJ.push_back({vertices[0], vertices[1], vertices[2]});
                        index = 0;
                    }
                }

        }
        // Identifying if its reading the faces
        if(fileContent[0] == 'f')
        {
            for(auto iter : variables)
                std::cout << iter << std::endl;
        }
    }

    // Close the file
    readFile.close();
    return verticesOBJ;
}