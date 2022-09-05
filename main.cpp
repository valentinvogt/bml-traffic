const unsigned H = 600;
const unsigned W = 600;

#include <SFML/Graphics.hpp>
#include <random>
#include "states.h"
#include "display.h"
#include "car.h"

const unsigned H_plot = 400;
const unsigned W_plot = 400;

using color_matrix = std::vector<std::vector<unsigned>>;
using color = sf::Color;

int main()
{
	const unsigned red = 1;
	const unsigned blue = 2;
	const unsigned white = 0;

	auto c_red = color(255, 0, 0);
	auto c_blue = color(255, 255, 0);
	auto c_white = color(0, 0, 0);
	auto c_axes = color(255, 255, 255);

	double d_red = 0.4;
	double d_blue = 0.4;

	int speed_red = 1;
	int speed_blue = 1;

	// Set up Window
	sf::RenderTexture RT;
	RT.create(W, H);
	sf::RenderWindow window(sf::VideoMode(W, H, 32), "Test");
	window.setFramerateLimit(60);

	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_real_distribution<> dist(0., 2.);

	//Creates the sf::Vertex matrix
	display pixels(W, H);
	states T(W, H);

	std::vector<car> blue_cars;
	std::vector<car> red_cars;

	for (unsigned i = 0; i < H; ++i)
	{
		for (unsigned j = 0; j < W; ++j)
		{
			double a = dist(rng);
			if (a < d_red)
			{
				T.set_color(i, j, red);
				pixels.set_pixel(i, j, c_red);
				red_cars.emplace_back(i, j);
			}
			else if (a < d_red + d_blue)
			{
				T.set_color(i, j, blue);
				pixels.set_pixel(i, j, c_blue);
				blue_cars.emplace_back(i, j);
			}
			else
			{
				T.set_color(i, j, white);
				pixels.set_pixel(i, j, c_white);
			}
		}
	}

    unsigned number_blue = blue_cars.size();
    unsigned number_red = red_cars.size();

	sf::VertexArray curve_b(sf::LinesStrip);
	sf::VertexArray curve_r(sf::LinesStrip);
	sf::VertexArray axis(sf::LinesStrip);
	axis.append(sf::Vertex(sf::Vector2f(W_plot - 50, 50), c_axes));
	axis.append(sf::Vertex(sf::Vector2f(50, 50), c_axes));
	axis.append(sf::Vertex(sf::Vector2f(50, H_plot - 50), c_axes));
	axis.append(sf::Vertex(sf::Vector2f(W_plot - 50, H_plot - 50), c_axes));

	sf::RenderWindow plots(sf::VideoMode(W_plot, H_plot), "Plots");

	std::vector<double> blue_hist;
	std::vector<double> red_hist;

	unsigned iter = 0;
	while (window.isOpen())
	{
		sf::Event event;
		while (plots.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				plots.close();
		}
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//Draws the pixel matrix
		RT.clear();
		RT.draw(pixels.matrix.data(), H * W, sf::Points);

		//And finally draws the RenderTexture to the RenderWindow
		RT.display();
		window.clear();
		window.draw(sf::Sprite(RT.getTexture()));
		window.display();

		++iter;
		states T1(W, H);
		T1.colors = T.colors;

		float blue_moving = 0;

		for (auto& c : blue_cars)
		{
			unsigned i = c.x;
			unsigned j = c.y;
			if (T.check_y(speed_blue, i, j, white))
			{
				T1.set_color(i, j, white);
				T1.set_color(i, j + speed_blue, blue);
				c.move_y(speed_blue);
				blue_moving++;
				pixels.set_pixel(i, j, c_white);
				pixels.set_pixel(i, j + speed_blue, c_blue);
			}
		}

		states T2(W, H);
		T2.colors = T1.colors;

		float blue_rate = blue_moving / number_blue;

		blue_hist.push_back(blue_rate);
		unsigned s = blue_hist.size();
		curve_b.clear();
		for (unsigned i = 0; i < s; ++i)
		{
			curve_b.append(sf::Vertex(sf::Vector2f(50 + (W_plot - 100) * i / (s + 1), H_plot - 50 - (H_plot - 100) * blue_hist[i]), c_blue));
		}
		plots.clear();
		plots.draw(curve_b);

		double red_moving = 0;

		for (auto& c : red_cars)
		{
			unsigned i = c.x;
			unsigned j = c.y;
			if (T1.check_x(speed_red, i, j, white))
			{
				T2.set_color(i, j, white);
				T2.set_color(i + speed_red, j, red);
				c.move_x(speed_red);
				pixels.set_pixel(i, j, c_white);
				pixels.set_pixel(i + speed_red, j, c_red);
				red_moving++;
			}
		}

		T.colors = T2.colors;

		double red_rate = red_moving / number_red;

		red_hist.push_back(red_rate);
		s = red_hist.size();
		curve_r.clear();
		for (unsigned i = 0; i < s; ++i)
		{
			curve_r.append(sf::Vertex(sf::Vector2f(50 + (W_plot - 100) * i / (s + 1), H_plot - 50 - (H_plot - 100) * red_hist[i]), c_red));
		}
		plots.draw(curve_r);
		plots.draw(axis);
		plots.display();
		if (red_moving == 0 && blue_moving == 0)
			break;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		while (plots.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				plots.close();
		}

		//Draws the pixel matrix
		RT.clear();
		RT.draw(pixels.matrix.data(), H * W, sf::Points);

		//And finally draws the RenderTexture to the RenderWindow
		RT.display();
		window.clear();
		window.draw(sf::Sprite(RT.getTexture()));
		window.display();
	}
	return 0;
}