#include "Path.h"

const Path::RgbPoint Path::pathPoint(0, 0, 0);
const Path::RgbPoint Path::beginPoint(0, 0, 255);
const Path::RgbPoint Path::endPoint(255, 0, 0);
const Path::RgbPoint Path::towerPoint(255, 0, 255);

//Path::Path(Terrain* terrain)
//	: terrain(terrain)
//{
//}

Path::Path()
{}

Path::~Path()
{
}

void Path::Init(const string &filename)
{
	LoadPathMap(filename);
	SmoothPath();
}

Vector3f Path::GetRotation(const Vector3f &currentPos, int nextPathPointIndex) const
{
	Vector3f rotation(0.f, 0.f, 0.f);
	const int dIndexForRotY = 15;
	const float radToDeg = 180.0 / 3.141592;

	float targetX = pathPoints[std::min(nextPathPointIndex + dIndexForRotY, (int)pathPoints.size() - 1)].first;
	float targetZ = pathPoints[std::min(nextPathPointIndex + dIndexForRotY, (int)pathPoints.size() - 1)].second;

	Vector3f lookAt(targetX - currentPos.x, currentPos.y, targetZ - currentPos.z);
	lookAt = lookAt.Normalize();
	rotation.y = 90.0 + atan2(lookAt.z, lookAt.x) * radToDeg;
	
	return rotation;
}

void Path::LoadPathMap(const string &filename)
{
	FILE *file = fopen(filename.c_str(), "rb");
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

//#define CHECK_POINTS
#ifdef CHECK_POINTS
	std::vector<RgbPoint> diffrentPoints;
#endif
	for (int j = 1, pdI = 0; j <= height; ++j)
	{
		for (int i = 1; i <= width; ++i, pdI += 3)
		{
			RgbPoint currentPoint = RgbPoint(pathData[pdI + 2], pathData[pdI + 1], pathData[pdI]);
			char currentPointChar = RgbToPointChar(currentPoint);
			map[i][j/*width - j + 1*/] = currentPointChar;
			if (currentPointChar == towerPointChar)
				possibleTowerPoints.push_back(std::make_pair(i, j/*width - j*/));
#ifdef CHECK_POINTS
			bool hasIt = false;
			for (auto p : diffrentPoints)
				if (p == currentPoint)
					hasIt = true;
			if (!hasIt)
				diffrentPoints.push_back(currentPoint);
#endif
		}
	}
	delete pathData;
#ifdef CHECK_POINTS
	for (auto p : diffrentPoints)
		printf("%d %d %d -> '%c'\n", p.r, p.g, p.b, RgbToPointChar(RgbPoint(p.r, p.g, p.b)));
#endif

	CalculatePathPoints(map);
	for (int i = 0; i < width+2; ++i)
		delete[] map[i];
	delete [] map;
}

void Path::SmoothPath()
{
	const int groupSize = 5;
	const float divFactor = (float)groupSize;
	float x = 0.f;
	float z = 0.f;
	for (int i = 0; i < groupSize; ++i)
	{
		x += pathPoints[0].first;
		z += pathPoints[0].second;
	}

	std::vector<std::pair<float, float>> smoothedPath;
	smoothedPath.push_back(pathPoints[0]);
	for (int i = 1; i < pathPoints.size(); ++i)
	{
		x -= pathPoints[std::max(i - groupSize, 0)].first;
		z -= pathPoints[std::max(i - groupSize, 0)].second;
		x += pathPoints[i].first;
		z += pathPoints[i].second;
		smoothedPath.push_back(std::make_pair(x / divFactor, z / divFactor));
	}
	//smoothedPath.shrink_to_fit();
	pathPoints = smoothedPath;
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
	if (rgbPoint == Path::towerPoint || rgbPoint == RgbPoint( 255, 255, 0 ))
		return Path::towerPointChar;
	return defaultPointChar;
}
