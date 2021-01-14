***Nour Abdi 206144750***
**Assignment 1 , Part 1 **

***1. My implementation of the algorithm:**

**Part 1 of the first assignment is to draw lines using Bresenham's algorithm. To test the
algorithm's correctness, as a sanity check, one should draw lines in all directions. One way to
do so is to draw lines from a point to many points on a circles centered around the points.
We Set the center point to be (half of windowWidth, half of windowHeight) (inour case its windowWidth = 1280, windowHeight = 720 -->(640,360);
Then, in a loop , We draw a line to all directions of circle with R=50 (radios of the circle) **

*In order to do the Bresenham's algorithm function (DrawLine) we need for 2 basic sub-functions : 
plotLineLow and plotLineHigh, both clarified in the same class Renderer :
plotLineLow and plotLineHigh: this functions computes and determines the 2D points
that should be selected in order to form a close approximation to a straight line between two points.*
```
void Renderer::DrawLine(const glm::vec2& p1, const glm::vec2& p2, const glm::vec3& color)
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

```
void Renderer::plotLineLow(const glm::vec2& p1, const glm::vec2& p2, const glm::vec3& color)
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

void Renderer::plotLineHigh(const glm::vec2& p1, const glm::vec2& p2, const glm::vec3& color)
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
*As we set a radios R=50 and an original point for the circle to be (640,360) , for a loop of 360 degrees divided by 
(alpha) angle we will find the deptj of the loop : as in the picture demonstrations for my implimentation of drawing the circle :*  

![1](https://user-images.githubusercontent.com/34486030/97979688-486a4e80-1dd8-11eb-88cf-43fe863c5c32.png)

**3. A drawing of my own choice :**
* Here I chose tow center circles and drew just half of eatch one from top and attached every point with one bottom point creating a LOVE shape 
All lines printed with the color of red *

![12](https://user-images.githubusercontent.com/34486030/97983648-44d9c600-1dde-11eb-94b2-a63a87018f4c.png)


