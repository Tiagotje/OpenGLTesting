#pragma once
#include <string>

class Tex2D
{
	unsigned int ID;
	int width, height, nrChannels;
public:
	Tex2D(){}

	Tex2D(std::string name, bool alpha);

	Tex2D(std::string name) : Tex2D(name, false) {};

	void use();

	unsigned int getID() { return ID; }

};