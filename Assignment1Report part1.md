***Nour Abdi 20614750***

**1. My implementation of the algorithm:**
```
void Renderer::DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{
	// TODO: Implement bresenham algorithm
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm

	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	if (dy < 0)
		dy = -dy;
	if (dx < 0)
		dx = -dx;
	if (dy < dx)//abs(y1 - y0) < abs(x1 - x0)
		if (p1.x > p2.x)
			plotLineLow(p2 ,p1 ,color);
		else
			plotLineLow(p1, p2, color);
	else
		if (p1.y > p2.y)
			plotLineHigh(p2, p1, color);
		else
			plotLineHigh(p1, p2, color);
}
```
*The algorithm function using 2 basic sub-functions : plotLineLow and plotLineHigh, both clarified in the same class Renderer :*
```
void Renderer::plotLineLow(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{
	int y, D;
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	int yi = 1;
	if (dy < 0)
	{
		yi = -1;
		dy = -dy;
	}
	D = (2 * dy) - dx;
	y = p1.y;

	for (int i = p1.x; i <= p2.x; i++)
	{
		PutPixel(i, y, color);
		if (D > 0)
		{
			y = y + yi;
			D = D + (2 * (dy - dx));
		}
		else
			D = D + 2 * dy;
	}
}

void Renderer::plotLineHigh(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{
	int x, D;
	int dx = p2.x - p1.x;
	int dy = p2.y - p1.y;
	int xi = 1;
	if (dx < 0)
	{
		xi = -1;
		dx = -dx;
	}
	D = (2 * dx) - dy;
	x = p1.x;

	for (int i = p1.y; i <= p2.y; i++)
	{
		PutPixel(x, i, color);
		if (D > 0)
		{
			x = x + xi;
			D = D + (2 * (dx - dy));
		}
		else
			D = D + 2 * dx;
	}
}
```
**2. The picture of the sanity check results :**

![1](https://user-images.githubusercontent.com/34486030/97979688-486a4e80-1dd8-11eb-88cf-43fe863c5c32.png)

**3. A drawing of my own choice :**

![12](https://user-images.githubusercontent.com/34486030/97983648-44d9c600-1dde-11eb-94b2-a63a87018f4c.png)


