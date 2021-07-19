#include "config.h"
#include "tools.h"

int loop(sf::RenderWindow& window, std::map<std::string, float>& cfg)
{
	displayConsoleInformation(cfg);

	int iSqW = cfg["squareWidth"];
	int iRows = mWH / iSqW;
	int iCols = mWW / iSqW;

	std::vector<std::vector<MazeNode>> nodes(iRows, std::vector<MazeNode>(iCols, MazeNode()));

	sf::VertexArray line(sf::LineStrip, 2);
	line[0].color = sf::Color(255, 255, 255);
	line[1].color = sf::Color(255, 255, 255);

	mazeGen(nodes, iRows, iCols);

	window.clear();

	for (int r = 0; r < iRows; ++r)
	{
		for (int c = 0; c < iCols; ++c)
		{
			if (nodes[r][c].bTopWall)
			{
				line[0].position = sf::Vector2f(c * iSqW, r * iSqW);
				line[1].position = sf::Vector2f(c * iSqW + iSqW, r * iSqW);

				window.draw(line);
			}
			if (nodes[r][c].bLeftWall)
			{
				line[0].position = sf::Vector2f(c * iSqW, r * iSqW);
				line[1].position = sf::Vector2f(c * iSqW, r * iSqW + iSqW);
				
				window.draw(line);
			}
		}
	}

	window.display();

	while (window.isOpen())
	{
		switch (eventListener(window))
		{
			case (CLOSE_EVENT_CODE):
				window.close();
				break;

			case RESTART_EVENT_CODE:
				init(window);
				break;
		}
	}
	return 0;
}

int init(sf::RenderWindow& window)
{
	std::map<std::string, float> cfg = readConfig(mConfigPath);
	return loop(window, cfg);
}