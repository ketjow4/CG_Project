#include "Path.h"

const Path::RgbPoint Path::pathPoint(0, 0, 0);
const Path::RgbPoint Path::beginPoint(0, 0, 255);
const Path::RgbPoint Path::endPoint(255, 0, 0);

Path::Path()
{
}


Path::~Path()
{
}

void Path::Init(char *filename)
{
	LoadPathMap(filename);
}

void Path::LoadPathMap(char *filename)
{
	FILE *file = fopen(filename, "rb");
	if (!file) { printf("path file error\n"); return; }

	// Get path width
	fseek(file, 18, SEEK_SET);
	fread(&width, 4, 1, file);

	// Get path height
	fseek(file, 22, SEEK_SET);
	fread(&height, 4, 1, file);

	// Get path data
	int pathSize = width * height * 3;
	unsigned char *pathData = new unsigned char[pathSize];
	fseek(file, 54, SEEK_SET);
	fread(pathData, 1, pathSize, file);
	fclose(file);

	// Init map
	char** map = new char*[width+2];
	for (int i = 0; i < width+2; ++i)
		map[i] = new char[height+2];

	// Set map
	//std::vector<RgbPoint> diffrentPoints;
	for (int j = 1, pdI = 0; j <= height; ++j)
	{
		for (int i = 1; i <= width; ++i, pdI += 3)
		{
			map[i][j] = RgbToPointChar(RgbPoint(pathData[pdI + 2], pathData[pdI + 1], pathData[pdI]));
			//auto newP = RgbPoint(pathData[pdI + 2], pathData[pdI + 1], pathData[pdI]);
			//bool hasIt = false;
			//for (auto p : diffrentPoints)
			//	if (p == newP)
			//		hasIt = true;
			//if (!hasIt)
			//	diffrentPoints.push_back(newP);
		}
	}
	delete pathData;

	//for (auto p : diffrentPoints)
		//printf("%d %d %d\n", p.r, p.g, p.b);

	CalculatePathPoints(map);
	for (int i = 0; i < width+2; ++i)
		delete[] map[i];
	delete [] map;
}

void Path::CalculatePathPoints(char **map)
{
	std::vector<std::pair<int, int>> Q;
	std::vector<int> parentQIndices;

	// Find begin point
	for (int i = 1; i <= width; ++i)
		for (int j = 1; j <= height; ++j)
			if (map[i][j] == Path::beginPointChar)
			{
				Q.push_back(std::make_pair(i, j));
				parentQIndices.push_back(-1);
				map[i][j] *= -1; // used
				i = width + 1;
				j = height + 1;
			}

	// BFS
	unsigned int current = 0;
	int endPointIndex = -1;
	while (current < Q.size())
	{
		int x = Q[current].first;
		int z = Q[current].second;
		for (int dx = -1; dx <= 1; ++dx)
			for (int dz = -1; dz <= 1; ++dz)
			{
				if (map[x + dx][z + dz] == Path::pathPointChar || map[x + dx][z + dz] == Path::endPointChar)
				{
					if (map[x + dx][z + dz] == Path::endPointChar)
						endPointIndex = Q.size();
					Q.push_back(std::make_pair(x + dx, z + dz));
					parentQIndices.push_back(current);
					map[x + dx][z + dz] *= -1;
				}
			}
		++current;
	}

	// Trace
	int nextIndex = endPointIndex;
	while (nextIndex != -1)
	{
		float x = (float)(Q[nextIndex].first - 1);
		float z = (float)(Q[nextIndex].second - 1);
		pathPoints.push_back(std::make_pair(x, z));
		nextIndex = parentQIndices[nextIndex];
	}
	std::reverse(pathPoints.begin(), pathPoints.end());

	//for (auto x : pathPoints)
	//	printf("%f %f\n", x.first, x.second);
}

char Path::RgbToPointChar(const RgbPoint &rgbPoint) const
{
	if (rgbPoint == Path::pathPoint)
		return Path::pathPointChar;
	if (rgbPoint == Path::beginPoint)
		return Path::beginPointChar;
	if (rgbPoint == Path::endPoint)
		return Path::endPointChar;
	return defaultPointChar;
}
