#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>
#include "linearmath.h"
#include "grid.h"
#include "Engine.h"

using namespace std;

void clearArray(Line2D line[], int nOfLines) {
	for (int i = 0; i < nOfLines; i++) {
		//line[i] = Line2D;
	}
}

void printPoint3D(Point3D point) {
	cout << point.x << ", " << point.y << ", " << point.z << endl;
}

void printPoint2D(Point2D point) {
	cout << point.x << ", " << point.y << endl;
}

sf::Vertex * transformToScreenCoordinates(int w, int h, Line2D lines[], int nOfLines) {
	sf::Vertex * screenCoordinates = (sf::Vertex*)malloc(sizeof(sf::Vertex) * nOfLines * 2);
	Point2D center = { w / 2.0f, h / 2.0f };

	for (int i = 0; i < nOfLines; i++) {
		int index = i * 2;
		screenCoordinates[index] = { sf::Vector2f(center.x * lines[i].start.x + center.x, center.y - center.y * lines[i].start.y) };
		screenCoordinates[index + 1] = { sf::Vector2f(center.x * lines[i].end.x + center.x, center.y - center.y * lines[i].end.y) };
	}

	return screenCoordinates;
}

clock_t ticksPerFrame(unsigned int fps) {
	return (clock_t)((1.0f / fps)*CLOCKS_PER_SEC);
}

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	Point3D transformer = { -0.0,-0.0,0.025 };
	Point3D outline[4];
	Line3D inside[36];
	makeGrid(outline, inside);

	unsigned int  base = 0;
	unsigned int linesToRender = 1;
	linesToRender = 36 - base;

	Line2D * transformed;
	transformed = (Line2D*)(malloc(sizeof(Line2D) * 36));
	int nOfLines = RenderEngine::projectLines(inside + base, linesToRender, transformed, 120.0f);
	cout << nOfLines << endl;
	sf::Vertex * lines = transformToScreenCoordinates(800, 800, transformed, nOfLines);

	Point2D arr[] = { {1,2}, {5.5,7.5}, {0.01,10.5} };
	float * pts = (float*)arr;
	printPoint2D(arr[1]);
	cout << pts[2] << "," << pts[3] << endl;

	int counter = 0;
	float speed = 0.05;
	float angle = 0;
	float radPerPixel = (3.14 / 360) * 5;

	sf::Vector2i mousePosition;
	window.setMouseCursorVisible(false);
	while (window.isOpen())
	{
		mousePosition = sf::Mouse::getPosition(window);
		mousePosition -= {0, 0};
		rotatePoints3DY((Point3D*)inside, linesToRender * 2, -radPerPixel * mousePosition.x);
		rotatePoints3DX((Point3D*)inside, linesToRender * 2, -radPerPixel * mousePosition.y);
		sf::Mouse::setPosition({ 0,0 }, window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			//keyboard and mouse events are tied to moving around the 3D world
			else if (event.type == sf::Event::KeyPressed) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					translateLines3D(inside + base, linesToRender, { speed,0,0 });
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					translateLines3D(inside + base, linesToRender, { -speed,0,0 });
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					translateLines3D(inside + base, linesToRender, { 0,-speed,0 });
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					translateLines3D(inside + base, linesToRender, { 0,speed,0 });
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
					translateLines3D(inside + base, linesToRender, { 0,0,speed });
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
					translateLines3D(inside + base, linesToRender, { 0,0,-speed });
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					translateLines3D(inside + base, linesToRender, { speed,0,0 });
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					//rotatePoints3DY((Point3D*)inside, linesToRender * 2, -1);
					translateLines3D(inside + base, linesToRender, { -speed,0,0 });
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					window.close(); break;
				}
			}
		}

		window.clear();
		window.draw(lines, nOfLines * 2, sf::Lines);
		free((void*)lines); free((void*)transformed);
		transformed = (Line2D*)(malloc(sizeof(Line2D) * 36));

		nOfLines = RenderEngine::projectLines(inside + base, linesToRender, transformed, 60.0f);
		if (nOfLines == 1) {
			cout << "1" << endl;
		}

		lines = transformToScreenCoordinates(800, 800, transformed, nOfLines);
		counter++;
		window.display();

		std::this_thread::sleep_for(std::chrono::milliseconds(33));
	}

	return 0;
}