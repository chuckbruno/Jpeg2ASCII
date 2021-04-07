// Jpeg2ASCII.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

#define RED_COEFF 0.2125
#define GREEN_COEFF 0.7154
#define BLUE_COEFF 0.0721


char getCorrespondingAsciiChar(int grayScale, std::string among) {
	return among[(int)(grayScale / 255.f*among.size())];
}

int main(int argc, char* argv[])
{

	if (argc != 3) {
		std::cerr << "wrong args, please set image path and ascii path" << std::endl;
		return -1;
	}

	std::string path;
	std::string outputPath;

	path = argv[1];
	outputPath = argv[2];

	//std::string path = "h13.jpg";
	//std::string outputPath = "16_low.txt";
	std::string among = "@%#Oo*+=-:.";

	sf::Image image;
	if (!image.loadFromFile(path)) {
		std::cerr << "cannot open image file" << std::endl;
		return -1;
	}

	sf::Image bwImage(image);
	std::cout << "Conversion to black and white ..." << std::endl;

	for (int i(0); i < image.getSize().x; i++) {
		for (int j(0); j < image.getSize().y; j++) {
			sf::Color tempColor = image.getPixel(i, j);
			bwImage.setPixel(i, j, sf::Color::Color(tempColor.r*RED_COEFF + tempColor.g*GREEN_COEFF + tempColor.b*BLUE_COEFF,
													tempColor.r*RED_COEFF + tempColor.g*GREEN_COEFF + tempColor.b*BLUE_COEFF,
													tempColor.r*RED_COEFF + tempColor.g*GREEN_COEFF + tempColor.b*BLUE_COEFF));
		}
	}

	//convert to gray image
	//bwImage.saveToFile("gray.jpg");

	std::cout << "Done" << std::endl;
	std::cout << "Conversion to ASCII ..." << std::endl;

	std::string asciiArt;
	for (int j(0); j < bwImage.getSize().y; j ++) {
		for (int i(0); i < bwImage.getSize().x; i ++) {
			asciiArt += getCorrespondingAsciiChar(bwImage.getPixel(i, j).r, among);
		}
		asciiArt += "\n";
	}

	std::ofstream output(outputPath);
	if (!output.is_open()) {
		std::cerr << "cannot write ascii text to file" << std::endl;
		return -1;
	} 
	output << asciiArt;
	output.close();
	std::cout << "Finished! You will find the result at : " << outputPath << std::endl;
	return 0;
}
