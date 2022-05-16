#include<SFML/Graphics.hpp>
#include<time.h>
#include<list>
using namespace sf;
struct Point
{
	int x, y;
};




int main()
{
	srand(time(0));
	RenderWindow app(VideoMode(400, 533), "Double Jump!");
	app.setFramerateLimit(60);
	Texture t1,t2,t3,t4;
	t1.loadFromFile("images/background1.png");
	t2.loadFromFile("images/doodle.png");
	t3.loadFromFile("images/platform.png");
	t4.loadFromFile("images/gameover.png");
	Sprite sbackground(t1),splayer(t2),over(t4);
	Sprite splat(t3);
	over.scale(0.5, 0.5);
	int x = 200, y = 300,h=100;
	float dy = 0,dx=0;
	Point plat[20];
	for (int i = 0;i < 10;i++)
	{
		plat[i].x = rand() % 332;
		plat[i].y = rand() % 533;

	}

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed) app.close();
			
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) x += 4;
		if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 4;
		if (y>533)
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				y = 200, x = 200;
				dy = 0;
			
			}
		dy += 0.2;
		y += dy;
		
		if (x > 400) x = -80;
		else if(x < -80) x = 400;

		app.draw(sbackground);

		for (int i = 0;i < 10;i++)
		{
			if (x<plat[i].x + 44 && x + 72>plat[i].x&&dy>0&&y+82>plat[i].y&& y + 80 < plat[i].y+8) dy = -8;
		}


		for (int i = 0;i < 10;i++)
		{
			if (y < h)
			{
				plat[i].y += 4;
			}
			if (plat[i].y > 533)
			{
				plat[i].y = -14;
				plat[i].x = rand() % 400;
			}
		}

		
		for (int i = 0;i < 10;i++)
		{
			splat.setPosition(plat[i].x, plat[i].y);
			app.draw(splat);
		}

		splayer.setPosition(x, y);
		
		app.draw(splayer);


		if (y > 533)
		{
			over.setPosition(80, 200);
			over.setColor(Color::Red);
			app.draw(over);
		}
		app.display();
	}


	return 0;
}