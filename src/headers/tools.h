#include "config.h"

struct MazeNode
{
	bool bCollapse = false;
	bool bTopWall = true;
	bool bLeftWall = true;
};

void mazeGen(std::vector<std::vector<MazeNode>>& nodes, int iRows, int iCols);
void displayConsoleInformation(std::map<std::string, float>& cfg);

std::map<std::string, float> readConfig(std::string sConfigPath);

EVENT_CODE eventListener(sf::RenderWindow& window);

int init(sf::RenderWindow& window);
int main();