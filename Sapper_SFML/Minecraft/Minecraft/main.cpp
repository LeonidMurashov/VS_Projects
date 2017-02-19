#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <fstream>
#include <iostream>
#include <string>
#include <assert.h>
#include <random>
#include "helpFile.hpp"
using namespace sf;
using namespace std;

float angleX, angleY; // ”глы поворота камеры
bool lose = false;

class Player
{ 
public:
   float x,y,z;
   float dx,dy,dz;
   float w,h,d;  // width, height, depth 
   bool onGround;
   float speed;

   Player(float x0, float y0, float z0)
   {
    x=x0; y=y0; z=z0;
	dx=0; dy=0; dz=0;
	w=5; h=20; d=5; speed=3;
	onGround=false;
   }

  void update(float time)
   {
	   if(!lose)
	   {
			 onGround=0;
	 
			 x+=dx*time;
			 collision(dx,0,0);	     
			 y+=dy*time;        
			 collision(0,dy,0);
			 dy = 0;
			 z+=dz*time;
			 collision(0,0,dz);
 
			 dx=dz=0; 
	   }
   }

  void collision(float Dx,float Dy,float Dz)
  {
    for (int X=(x-w)/size;X<(x+w)/size;X++)
    for (int Y=(y-h)/size;Y<(y+h)/size;Y++)
    for (int Z=(z-d)/size;Z<(z+d)/size;Z++)
      if (check(X,Y,Z))  {
        if (Dx>0)  x = X*size-w; 
        if (Dx<0)  x = X*size+size+w; 
		if (Dy>0)  y = Y*size-h; 
        if (Dy<0) {y = Y*size+size+h; onGround=true; dy=0;} 
		if (Dz>0)  z = Z*size-d; 
        if (Dz<0)  z = Z*size+size+d; 
                          }
  }

  void keyboard()
  {
		if (Keyboard::isKeyPressed(Keyboard::Space))dy = speed; // if (onGround) {onGround=false; dy=12;};
		if (Keyboard::isKeyPressed(Keyboard::LShift))dy = -speed;

		if (Keyboard::isKeyPressed(Keyboard::W))	
		{
		 dx =- sin(angleX/180*PI) * speed; 
		 dz =- cos(angleX/180*PI) * speed;
		}

		if (Keyboard::isKeyPressed(Keyboard::S))	
		{
		 dx = sin(angleX/180*PI) * speed;
		 dz = cos(angleX/180*PI) * speed;
		}

		if (Keyboard::isKeyPressed(Keyboard::D))		
		{
		 dx = sin((angleX+90)/180*PI) * speed;	
		 dz = cos((angleX+90)/180*PI) * speed;
		}

		if (Keyboard::isKeyPressed(Keyboard::A))	
		{
		 dx = sin((angleX-90)/180*PI) * speed;	
		 dz = cos((angleX-90)/180*PI) * speed;
		}
  }

};

short GetMinesAround(int x, int y, int z)
{
	short mina = 0;
	for (int i = -1; i < 2; i++)
		for(int j = -1; j<2; j++)
			for(int k = -1; k<2; k++)
				if(check(x+i, y+j, z+k) == 2)
					mina++;

	/*for(int i = -1; i <= 1; i++)
	{
		if(check(x+i,y,z) == 2)
			mina++;		
		if(check(x,y+i,z) == 2)
			mina++;		
		if(check(x,y,z+i) == 2)
			mina++;
	}
	if(check(x,y,z) == 2)
		mina -= 2;*/

	return mina;
}

void GenerateMap()
{
	 for(int i = 0; i < sizeCube; i++)
		for(int j = 0; j < sizeCube; j++)
			for(int k = 0; k < sizeCube; k++)
			{
				mass[i][j][k] = rand()%20<18 ? 1 : 2;
				marked[i][j][k] = false;
			}

	/* for(int i = 0; i < sizeCube; i++)
		for(int j = 0; j < sizeCube; j++)
			for(int k = 0; k < sizeCube; k++)
				if(GetMinesAround(i,j,k) == 0)
					mass[i][j][k] = 0;*/
}

int main()
{
	srand(time(NULL));

	RenderWindow window(VideoMode::getDesktopMode(), "Sapper3D" ,Style::Fullscreen);

	start:

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glClearDepth(1.f);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 2000.f);  
    glEnable(GL_TEXTURE_2D);

	ShowCursor(FALSE);

	////карта высот////
	Image im;
	//im.loadFromFile("resources/heightmap.png");
	/*
	for(int x=0;x<256;x++)
 	 for(int z=0;z<256;z++)
	 {
		 int c = im.getPixel(x,z).r / 15;
         for(int y=0;y<c;y++)
	       if (y>c-3) mass[x][y][z]=1;
	///////////////3
	 }*/

	GenerateMap();
	 
	 Image img;
	// img.loadFromFile("D:\\delme\\1000.jpg");

    ///////текстуры///////
	Texture t; t.loadFromFile("resources/cursor.png");
	Sprite s(t); s.setOrigin(8,8); s.setPosition(window.getSize().x/2,window.getSize().y/2); 
	
	
	  GLuint skybox[6];
	skybox[0] = LoadTexture("resources/skybox2/skybox_front.bmp");
	skybox[1] = LoadTexture("resources/skybox2/skybox_back.bmp");
	skybox[2] = LoadTexture("resources/skybox2/skybox_left.bmp");
    skybox[3] = LoadTexture("resources/skybox2/skybox_right.bmp");
	skybox[4] = LoadTexture("resources/skybox2/skybox_bottom.bmp");
	skybox[5] = LoadTexture("resources/skybox2/skybox_top.bmp");
		
	GLuint mark = LoadTexture("resources/mark.png");
	GLuint markBox[6];
	for(int i = 0; i < 6; i++)
		markBox[i] =  mark;

     /* GLuint box[6];
	box[0] = LoadTexture("resources/grassBox/side.jpg");
	box[1] = LoadTexture("resources/grassBox/side.jpg");
	box[2] = LoadTexture("resources/grassBox/side.jpg");
	box[3] = LoadTexture("resources/grassBox/side.jpg");
	box[4] = LoadTexture("resources/grassBox/bottom.jpg");
	box[5] = LoadTexture("resources/grassBox/top.jpg");
	*/

	/*box[0] = LoadTexture("resources/grassBox1/side.jpg");
	box[1] = LoadTexture("resources/grassBox1/side.jpg");
	box[2] = LoadTexture("resources/grassBox1/side.jpg");
	box[3] = LoadTexture("resources/grassBox1/side.jpg");
	box[4] = LoadTexture("resources/grassBox1/bottom.jpg");
	box[5] = LoadTexture("resources/grassBox1/top.jpg");
	/**/
	GLuint cubeTexture[27];
	/*cubeTexture[0] = LoadTexture("resources\\box_test\\1.jpg");
	cubeTexture[1] = LoadTexture("resources\\box_test\\2.jpg");
	cubeTexture[2] = LoadTexture("resources\\box_test\\3.jpg");
	cubeTexture[3] = LoadTexture("resources\\box_test\\4.jpg");
	cubeTexture[4] = LoadTexture("resources\\box_test	\\5.jpg");
	cubeTexture[5] = LoadTexture("resources\\box_test\\6.jpg");*/

	for(int i = 0; i < 26; i++)
		cubeTexture[i] = LoadTexture("resources\\box_test2\\" + std::to_string((long double)i) + ".jpg");

	/**/
	//box[0].inv
	//////////////////////////



	Clock clock;
	bool mLeft=0,mRight=0; // mouse buttons
    Player p(+50 + size*sizeCube,0,+50 + size*sizeCube);


	
	// Setting up the lose label
	Text loseText;
	Vector2f slPos(window.getSize().x/2-250, window.getSize().y/2-50);
	Font font;
	assert(font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf"));
	loseText.setFont(font);
	loseText.setCharacterSize(80);
	loseText.setColor(Color::Black);
	loseText.setStyle(sf::Text::Bold || sf::Text::Regular);
	loseText.setPosition(slPos);
	loseText.setString("YOU LOSE!!!");
	// Creating background for label
	Texture t1;
	IntRect tRect(slPos.x, slPos.y, 500, 90);
	Sprite loseTextBG;
	t.setRepeated(true);
	loseTextBG.setTexture(t1);
	loseTextBG.setTextureRect(tRect);
	loseTextBG.setPosition(slPos);
	loseTextBG.setColor(Color(255, 255, 255, 200));
	

	// fon	
	Texture t2;
	t2.loadFromFile("resources/explosion2.png");
	IntRect tRect2(0, 0, window.getSize().x, window.getSize().y);
	Sprite explosion;
	t.setRepeated(false);
	explosion.setTexture(t2);
	explosion.setTextureRect(tRect2);
	explosion.setPosition(0,0);
	


	Text fps("", font, 35);
	//////////////////////основной цикл////////////////////
	


	while (window.isOpen())
    {		
		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		time = time/50;
		//if (time>3) time=3;
		
		sleep(milliseconds(4));

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if ((event.type == Event::KeyPressed) && (event.key.code == Keyboard::Escape))
                window.close();

			if (event.type == Event::MouseButtonPressed)
				{if (event.key.code == Mouse::Right) mRight=1;
				 if (event.key.code == Mouse::Left)  mLeft=1;}

			 if (lose && (event.type == Event::MouseButtonPressed))
			 {
				 p.x = -10;
				 p.y = -10;
				 p.z = -10;
				 lose = false;

				GenerateMap();
			 }
        }


glClear(GL_DEPTH_BUFFER_BIT);

p.keyboard();
p.update(time);

if(!lose)
{
		////-----------------------
		POINT mousexy;
		GetCursorPos(&mousexy);
		int xt=window.getPosition().x+(double)1920/(double)2; 
		int yt=window.getPosition().y+(double)1080/(double)2;

		angleX +=(double)(xt - mousexy.x)/(double)10; //4 Ч чувствительность 
		angleY +=(double)(yt - mousexy.y)/(double)10;

		if (angleY<-89.0){angleY=-89.0;}
		if (angleY>89.0){angleY=89.0;}

		SetCursorPos(xt,yt);       
		////----------------------



				if (mRight || mLeft)
				  {
					double x = p.x;
					double y = p.y+(double)p.h/(double)2;
					double z = p.z;

					int X,Y,Z,oldX,oldY,oldZ;
					int dist=0;
					while(dist<120)  // радиус действи€
					{
					  dist++;

					 x += -sin((double)angleX/(double)180*PI);    X=(double)x/(double)size;
					 y +=  tan((double)angleY/(double)180*PI);    Y=(double)y/(double)size;
					 z += -cos((double)angleX/(double)180*PI);    Z=(double)z/(double)size;
			
					 //fps.setString(to_string((long double)X) + " " + to_string((long double)Y) + " " + to_string((long double)Z));

					 if (check(X,Y,Z))
					 {
						 if(mLeft)
						 {
				 			if(mass[X][Y][Z]==1)
						   {mass[X][Y][Z]=0; break;}
						   else
						   {lose = true; sleep(seconds(0.5)); break;}
						 }
						 else if(mRight)
						 {
							 if(!marked[X][Y][Z])
								marked[X][Y][Z] = true;//sleep(seconds(0.5));
							 else
								marked[X][Y][Z] = false;//sleep(seconds(0.5));
							 break;
						 }

					 }
			   
					 oldX=X; oldY=Y; oldZ=Z;
					}
				  }
  
		mLeft=mRight=0;
	}

        
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(p.x,p.y+(double)p.h/(double)2,p.z,p.x-sin((double)angleX/(double)180*PI),p.y+p.h/2+(tan((double)angleY/(double)180*PI)),p.z-cos((double)angleX/(double)180*PI), 0, 1, 0); 

     
//////////рисуем боксы///////
   int R = 10;  
		
   int X=p.x/size;
   int Y=p.y/size;
   int Z=p.z/size;
	
    for(int x=X-R; x<X+R; x++)
 	 for(int y=0;y<25;y++)
 	  for(int z=Z-R;z<Z+R;z++)
	  {
		  if (!check(x,y,z)) continue;
		   int mines = GetMinesAround(x,y,z);		  
		   glTranslatef(size*x+size/2, size*y+size/2, size*z+size/2);



		   GLuint box[6];
		   for(int i = 0; i < 6; i++)
			   box[i] = cubeTexture [mines];
		   createBox(box, size/2);



		   if(marked[x][y][z]) 
			  ;//createBox(markBox, size/2+0.1f);

  		   glTranslatef(-size*x-size/2, -size*y-size/2, -size*z-size/2);
	  }


   int R2 = 50;		
   int X2=p.x/size;
   int Z2=p.z/size;
  /* int maxy;
   for(int n = 0; n<1000; n++)if(mass[X2][n][Z2]==1)maxy = n;
   for(int i =0; i< 200; i++)
	   for(int j = 0; j< 200; j++)
		   img.setPixel(i, j,sf::Color(maxy*20, maxy*20, maxy*20));*/
   //cout<<maxy;
  /*  for(int x=X2-R2; x<X2+R2; x++)
 	  for(int z=Z-R2;z<Z+R2;z++)
	  {
		  if(x<0 || z<0 || x>sizeCube-1 || z>sizeCube-1)img.setPixel((x-(X2-R2)), (z-(Z-R2)),sf::Color::White);
		  else
		  {
			  int maxy = -1;
			  for(int n = 0; n<sizeCube; n++)if(mass[x][n][z]==1)maxy = n;
			  if(maxy == -1) img.setPixel((x-(X2-R2)), (z-(Z-R2)),sf::Color(255, 0, 0));
			  img.setPixel((x-(X2-R2)), (z-(Z-R2)),sf::Color(20*maxy, 20*maxy, 20*maxy));
		  }
	  }*/
	  Texture tex2;
	  tex2.loadFromImage(img);
	  Sprite map(tex2); map.setPosition(1920-400,0); 
	  map.setScale(4,4);
	 // sf
	 // window.draw(	


	  ////fps
	  //(string)to_string((long double)time)
	//  fps.setString("something!!!!");
	//  fps.setPosition(0,0);
	//  fps.setColor(Color::Green);

		 Font font;//шрифт 
		 assert(font.loadFromFile("C:\\Windows\\Fonts\\Arial.TTF"));//передаем нашему шрифту файл шрифта
		 //создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пиксел€х);//сам объект текст (не строка)
		 fps.setColor(Color::Green);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
		 fps.setStyle(sf::Text::Bold || sf::Text::Regular);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый

	  	//fps.setString("FPS: " + to_string((long double)ceil(((float)1000/(float)time*0.02))));//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		//fps.setPosition(20, -2);//задаем позицию текста, отступа€ от центра камеры
		
		 int minesLeft = 0, blocksLeft = 0;
		 
	 for(int i = 0; i < sizeCube; i++)
		for(int j = 0; j < sizeCube; j++)
			for(int k = 0; k < sizeCube; k++)
				if(mass[i][j][k] != 0)
				{
					if(mass[i][j][k]==2)
						minesLeft++;
					blocksLeft++;
				}
		 
		fps.setString("Mines: " + to_string((long double)minesLeft) + "\nBlocks left:" + to_string((long double)blocksLeft) );//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		fps.setPosition(20, -2);//задаем позицию текста, отступа€ от центра камеры
		
		if(minesLeft == blocksLeft)
		{			
			loseText.setString("YOU WIN!!!\nWOW, write to Leonid Murashov \nand say: \"Leonid, I has finished \nyour game! Make it more \ndifficult :P\"\nThanks!");
			lose = true;
		}
		
		
		


	  ///skybox

	   glTranslatef(p.x, p.y, p.z);
	   createBox(skybox,1000);
	   glTranslatef(-p.x, -p.y, -p.z);
	   
	   
		window.pushGLStates();
		window.draw(s);      //рисуем курсор
	//	window.draw(map);
		window.draw(fps);
		if(lose){
			window.draw(explosion);
			window.draw(loseTextBG);	
			window.draw(loseText);	
		}
        window.popGLStates();
		
        window.display();
    }

	/*ofstream file;

	file.open("D:\\delme\\gg.txt", ios::out);
	for(int i = 0; i<1000; i++)
		for(int j = 0; j<1000; j++)
			for(int o = 0; o<1000; o++)
				file<<mass[i][j][o]<<' ';
	file.close();*/
    return 0;
}
