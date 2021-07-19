#include "tools.h"

void mazeGen(std::vector<std::vector<MazeNode>>& nodes, int iRows, int iCols)
{
	sf::Vector2f point(0, 0);
	
	std::vector<sf::Vector2f> history;
	std::vector<sf::Vector2f> vectors;
	vectors.push_back(sf::Vector2f(0, -1));
	vectors.push_back(sf::Vector2f(0, 1));
	vectors.push_back(sf::Vector2f(-1, 0));
	vectors.push_back(sf::Vector2f(1, 0));

	std::vector<int> vectorVariants;

	for (int r = 0; r < iRows; ++r)
		nodes[r][0].bLeftWall = false;

	for (int c = 0; c < iCols; ++c)
		nodes[0][c].bTopWall = false;

	nodes[point.y][point.x].bCollapse = true;

	while (true)
	{
		int iRandIndex = zer::athm::rand_int(vectors.size());

		if (!std::count(vectorVariants.begin(), vectorVariants.end(), iRandIndex))
		{
			sf::Vector2f temp = point + vectors[iRandIndex];

			if (zer::athm::inRange2D(iRows, iCols, temp.y, temp.x) && !nodes[temp.y][temp.x].bCollapse)
			{
				point = temp;
				
				if (vectors[iRandIndex].y < 0)
					nodes[point.y - vectors[iRandIndex].y][point.x - vectors[iRandIndex].x].bTopWall = false;
				else if (vectors[iRandIndex].y > 0)
					nodes[point.y][point.x].bTopWall = false;
				else if (vectors[iRandIndex].x < 0)
					nodes[point.y - vectors[iRandIndex].y][point.x - vectors[iRandIndex].x].bLeftWall = false;
				else if (vectors[iRandIndex].x > 0)
					nodes[point.y][point.x].bLeftWall = false;

				vectorVariants.clear();

				history.push_back(point);

				nodes[point.y][point.x].bCollapse = true;
			}
			else
				vectorVariants.push_back(iRandIndex);

			if (vectorVariants.size() == vectors.size())
			{
				if (!history.size())
					break;

				vectorVariants.clear();
				
				point = history[history.size() - 1];
				
				history.erase(history.end() - 1);
			}
		}
	}
}

void displayConsoleInformation(std::map<std::string, float>& cfg)
{
	system("cls");

	std::cout << "# " << mTitle << " #" << std::endl;
	std::cout << "\n[!] keyboard buttons for control:" << std::endl;
	std::cout << "\t [ ESC ] - exit;" << std::endl;
	std::cout << "\t [ R ] - restart;" << std::endl;
	std::cout << "\n[!] note: visit a \"" << mConfigPath << "\" file to change configuration;" << std::endl;
	std::cout << "\n[!] current configuration:" << std::endl;
	
	for (std::map<std::string, float>::iterator p = cfg.begin(); p != cfg.end(); p++)
		std::cout << "\t" << p -> first << " = " << p -> second << ";" << std::endl;
}

std::map<std::string, float> readConfig(std::string sConfigPath)
{
	std::map<std::string, float> cfg;

	zer::File file(sConfigPath);
	file.read({zer::file::Modifier::lines});

	for (int i = 0; i < file.linesLen(); ++i)
	{
		std::string sLine = file.lineAt(i);
		if (sLine.find(" = ") != std::string::npos)
		{
			std::vector<std::string> lineParts = zer::athm::split(sLine, " = ");
			cfg[lineParts[0]] = stof(lineParts[1]);
		}
	}

	return cfg;
}

EVENT_CODE eventListener(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			return CLOSE_EVENT_CODE;
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
				return CLOSE_EVENT_CODE;
			if (event.key.code == sf::Keyboard::R)
				return RESTART_EVENT_CODE;
		}
	}
	return NULL_EVENT_CODE;
}

int main()
{
	zer::athm::rand_init();

	sf::RenderWindow window(sf::VideoMode(mWW, mWH), mTitle);
	
	return init(window);
}