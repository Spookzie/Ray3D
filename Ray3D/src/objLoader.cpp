#include "objLoader.h"


std::vector<Vertex> LoadOBJ(const char* file_name)
{
	std::vector<glm::fvec3> vertexPositions;
	std::vector<glm::fvec2> vertexTexcoords;
	std::vector<glm::fvec3> vertexNormals;
	
	//Face vectors
	std::vector<GLint> vertexPositionIndicies;
	std::vector<GLint> vertexTexcoordIndicies;
	std::vector<GLint> vertexNormalIndicies;

	//Vertex Array
	std::vector<Vertex> vertices;

	//File reading variables
	std::stringstream ss;
	std::ifstream in_file(file_name);
	std::string line = "";
	std::string prefix = "";
	glm::vec3 tempVec3;
	glm::vec2 tempVec2;
	GLint tempGLint = 0;

	//Opening file
	if (!in_file.is_open())
		std::cout << "ERROR::objLoader.cpp::LoadOBJ(): Could not open file" << std::endl;

	//Reading one line at a time
	while (std::getline(in_file, line))
	{
		ss.clear();
		ss.str(line);
		ss >> prefix;

		if (prefix == "#")
		{ }
		else if (prefix == "g")
		{ }
		else if (prefix == "v")	//Vertex position
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertexPositions.push_back(tempVec3);
		}
		else if (prefix == "vt")
		{
			ss >> tempVec2.x >> tempVec2.y;
			vertexTexcoords.push_back(tempVec2);
		}
		else if (prefix == "vn")
		{
			ss >> tempVec3.x >> tempVec3.y >> tempVec3.z;
			vertexNormals.push_back(tempVec3);
		}
		else if (prefix == "f")
		{

		}
		else
		{ }

		//DEBUG
		std::cout << line << std::endl;
		std::cout << "No. of Vertices: " << vertexPositions.size() << std::endl;
	}


	//Loaded success
	return vertices;
}