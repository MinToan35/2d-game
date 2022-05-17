#include<SFML/Graphics.hpp>
#include<time.h>
#include<list>
using namespace sf;
struct Point
{
	int x, y;
	float dx, dy;
};




int main()
{
	srand(time(0));
	RenderWindow app(VideoMode(400, 533), "Double Jump!");
	app.setFramerateLimit(60);
	Texture t1,t2,t3,t4,t5,t6;
	t1.loadFromFile("images/background1.png");
	t2.loadFromFile("images/doodle.png");
	t3.loadFromFile("images/platform.png");
	t4.loadFromFile("images/gameover.png");
	t5.loadFromFile("images/break1.png");
	t6.loadFromFile("images/break2.png");
	Sprite sbackground(t1),splayer(t2),over(t4),sbreak(t5),sbreak2(t6);
	Sprite splat(t3);
	over.scale(0.5, 0.5);
	int x = 200, y = 200,h=100;
	float dy = 0,dx=0;
	
	///Make platform
	Point plat[20];
	for (int i = 0;i < 10;i++)
	{
		plat[i].x = rand() % 332;
		plat[i].y = rand() % 533;

	}

	//Make flatform fall
	Point fall[10];
	Point fall2[10];
	for (int i = 0;i < 3;i++)
	{
		fall[i].x = rand() % 400;
		fall2[i].x = fall[i].x;
		fall[i].y = rand() % 533;
		fall2[i].y = fall[i].y;
		fall[i].dx = 0, fall[i].dy = 0;
		fall2[i].dx = 0, fall2[i].dy = 0;
	}
	
	
	
	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed) app.close();
			
		}

		
		
		
		
		//Button Right
		if (Keyboard::isKeyPressed(Keyboard::Right)) x += 4;
		//Button Left
		if (Keyboard::isKeyPressed(Keyboard::Left)) x -= 4;
		
		//Comeback before GAME OVER
		if (y > 533)
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				x = 300, y = 200;
				dy = 0;
				for (int i = 0;i < 10;i++)
				{
					plat[i].y += 533;
					if (plat[i].y > 533)
					{
						plat[i].y = rand() % 533;
						plat[i].x = rand() % 400;
					}
				}
			}
		}


		//gravity
		dy += 0.2;
		y += dy;
		

		//border x
		if (x > 400) x = -80;
		else if(x < -80) x = 400;
		
		//draw background
		app.draw(sbackground);


		//check collision with platform
		for (int i = 0;i < 10;i++)
		{
			if (x<plat[i].x + 44 && x + 72>plat[i].x&&dy>0&&y+82>plat[i].y&& y + 80 < plat[i].y+8) dy = -8;
		}

		//move screen
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



		///////platform fall
		for (int i = 0;i < 3;i++)
		{
			//move screen;
			if (y < h)
			{
				fall[i].y += 4;
				fall2[i].y += 4;
			}
			//reborn
			

			//fall
			if (x<fall[i].x + 44 && x + 72>fall[i].x && dy > 0 && y + 82 > fall[i].y && y + 80 < fall[i].y + 8)
			{
				fall[i].dy += 7;
				fall[i].dx -= 3;
				fall2[i].dx = 3;
				fall[i].y += fall[i].dy;
				
			}
			
			if (fall[i].dy > 0)
			{
				fall[i].y += fall[i].dy;
				fall[i].x += fall[i].dx;
				fall2[i].x += fall2[i].dx;
				
			}
			if (fall[i].y > 533)
			{
				fall[i].y = -14;
				fall2[i].y = -14;
				fall[i].x = rand() % 400;
				fall2[i].x = fall[i].x;
				fall[i].dy = 0;
				fall[i].dx = 0;
				fall2[i].dx = 0;
			
			}
			
			
		}

		//draw platform
		for (int i = 0;i < 10;i++)
		{
			splat.setPosition(plat[i].x, plat[i].y);
			app.draw(splat);
		}

		//draw platform fall
		for (int i = 0;i < 3;i++)
		{
			sbreak.setPosition(fall[i].x, fall[i].y);
			sbreak2.setPosition(fall2[i].x, fall[i].y);
			app.draw(sbreak);
			app.draw(sbreak2);
		}
		
		//draw player
		splayer.setPosition(x, y);
		app.draw(splayer);
	
		
		//over
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