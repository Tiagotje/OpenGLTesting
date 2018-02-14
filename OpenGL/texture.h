#pragma once
#include <string>

class Tex2D
{
	unsigned int ID;
	int width, height, nrChannels;
public:
	Tex2D(){}

	Tex2D(std::string name);

	void use();

	unsigned int getID() { return ID; }

};