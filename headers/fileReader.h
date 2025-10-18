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

//Splitting the coordinates and separanting it by "vertices"
void CheckVertices(std::string &fileContent, std::vector<std::string> &variables, std::vector<Vector3> &verticesOBJ)
{
    const int triangleVertices = 3;
    float vertices[triangleVertices];
    int index = 0;

    SplitStrings(fileContent, variables, ' ');

    for(std::string iter : variables)
        if(iter.at(0) != 'v')
        {
            if(index < triangleVertices)
            {
                vertices[index] = std::stof(iter);
                index++;
            }
            if(index == triangleVertices)
            {
                verticesOBJ.push_back({vertices[0], vertices[1], vertices[2]});
                index = 0;
            }
        }
}

//Splitting the edges and separanting it by "faces"
void CheckEdges(std::string &fileContent, std::vector<std::string> &variables, std::vector<FaceIndex> &facesOBJ)
{
    int index = 0;
    int spaceCounter = 0;
    /* Removing 1 because the .obj file starts from 1 instead of 0.*/
    const int objConversion = 1;
    FaceIndex facesIndex;
    std::string faceLinks;

    SplitStrings(fileContent, variables, 'f');
    
    for(std::string iter : variables)
    {
        for(auto it : iter)
        {
            if(it == ' '){spaceCounter++;}
        }
        if(spaceCounter != 0)
        {
            SplitStrings(fileContent, variables, ' ');
            for(auto link : variables)
            {
                if(link.at(0) != 'f')
                {
                    if(index < spaceCounter)
                    {
                        for(int i = 0; i < link.find('/'); i++)
                        {faceLinks += link.at(i);}
                        facesIndex.index[index] = std::stoi(faceLinks) - objConversion;
                        faceLinks = "";
                        index++;
                    }
                    if(index == spaceCounter)
                    {
                        facesOBJ.push_back(facesIndex);
                        index = 0;
                    }
                }
            }
        }
    }
}

// function that gets a .obj file and extracts its vertices and faces
void ReadOBJFile(std::string filepath, std::vector<Vector3> &verticesOBJ, std::vector<FaceIndex> &facesOBJ)
{   
    std::string fileContent;
    std::vector<std::string> variables;

    // Read from the text file
    std::ifstream readFile(filepath);

    while (std::getline(readFile, fileContent))
    {
       // Identifying if its reading the vertices
        if(fileContent[0] == 'v' and fileContent[1] == ' ')
        {CheckVertices(fileContent, variables, verticesOBJ);}

        // Identifying if its reading the faces
        if(fileContent[0] == 'f')
        {CheckEdges(fileContent, variables, facesOBJ);}
    }

    // Close the file
    readFile.close();
}