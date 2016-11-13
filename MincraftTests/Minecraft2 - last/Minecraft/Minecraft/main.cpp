#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>
#include <fstream>
#include <iostream>
#include <assert.h>
#include "helpFile.hpp"
using namespace sf;
//using namespace std;


float angleX, angleY; // ”глы поворота камеры


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
	w=5; h=20; d=5; speed=5;
	onGround=false;
   }

  void update(float time)
   {
     if (!onGround) dy-=1.5*time;
	 onGround=0;
	 
	 x+=dx*time;
     collision(dx,0,0);	     
     y+=dy*time;        
     collision(0,dy,0);
     z+=dz*time;
     collision(0,0,dz);
 
	 dx=dz=0; 
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
		if (Keyboard::isKeyPressed(Keyboard::Space))dy = 12; // if (onGround) {onGround=false; dy=12;};

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

int main()
{
	RenderWindow window(VideoMode(1920, 1080), "Minecraft C++" ,Style::Fullscreen);
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
	im.loadFromFile("resources/heightmap.png");

	for(int x=0;x<256;x++)
 	 for(int z=0;z<256;z++)
	 {
		 int c = im.getPixel(x,z).r / 15;
         for(int y=0;y<c;y++)
	       if (y>c-3) mass[x][y][z]=1;
	///////////////3
	 }
	 
	 Image img;
	 img.loadFromFile("D:\\delme\\1000.jpg");

    ///////текстуры///////
	Texture t; t.loadFromFile("resources/cursor.png");
	Sprite s(t); s.setOrigin(8,8); s.setPosition(1920/2,1080/2); 
	
	
	  GLuint skybox[6];
	skybox[0] = LoadTexture("resources/skybox2/skybox_front.bmp");
	skybox[1] = LoadTexture("resources/skybox2/skybox_back.bmp");
	skybox[2] = LoadTexture("resources/skybox2/skybox_left.bmp");
    skybox[3] = LoadTexture("resources/skybox2/skybox_right.bmp");
	skybox[4] = LoadTexture("resources/skybox2/skybox_bottom.bmp");
	skybox[5] = LoadTexture("resources/skybox2/skybox_top.bmp");


     /* GLuint box[6];
	box[0] = LoadTexture("resources/grassBox/side.jpg");
	box[1] = LoadTexture("resources/grassBox/side.jpg");
	box[2] = LoadTexture("resources/grassBox/side.jpg");
	box[3] = LoadTexture("resources/grassBox/side.jpg");
	box[4] = LoadTexture("resources/grassBox/bottom.jpg");
	box[5] = LoadTexture("resources/grassBox/top.jpg");
	*/

	      GLuint box[6];
	/*box[0] = LoadTexture("resources/grassBox1/side.jpg");
	box[1] = LoadTexture("resources/grassBox1/side.jpg");
	box[2] = LoadTexture("resources/grassBox1/side.jpg");
	box[3] = LoadTexture("resources/grassBox1/side.jpg");
	box[4] = LoadTexture("resources/grassBox1/bottom.jpg");
	box[5] = LoadTexture("resources/grassBox1/top.jpg");
	/**/
	box[0] = LoadTexture("resources\\box_test\\1.jpg");
	box[1] = LoadTexture("resources\\box_test\\2.jpg");
	box[2] = LoadTexture("resources\\box_test\\3.jpg");
	box[3] = LoadTexture("resources\\box_test\\4.jpg");
	box[4] = LoadTexture("resources\\box_test\\5.jpg");
	box[5] = LoadTexture("resources\\box_test\\6.jpg");
	/**/
	//box[0].inv
	//////////////////////////



	Clock clock;
	bool mLeft=0,mRight=0; // mouse buttons
    Player p(3000,400,3000);



	//////////////////////основной цикл////////////////////



	while (window.isOpen())
    {
		float time = clock.getElapsedTime().asMilliseconds();
		clock.restart();
		time = time/50;
		//if (time>3) time=3;


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
        }


glClear(GL_DEPTH_BUFFER_BIT);

p.keyboard();
p.update(time);


////-----------------------
POINT mousexy;
GetCursorPos(&mousexy);
int xt=window.getPosition().x+1920/2; 
int yt=window.getPosition().y+1080/2;

angleX +=(xt - mousexy.x)/8; //4 Ч чувствительность 
angleY +=(yt - mousexy.y)/8;

if (angleY<-89.0){angleY=-89.0;}
if (angleY>89.0){angleY=89.0;}

SetCursorPos(xt,yt);       
////----------------------



        if (mRight || mLeft)
          {
			float x = p.x;
			float y = p.y+p.h/2;
            float z = p.z;

			int X,Y,Z,oldX,oldY,oldZ;
			int dist=0;
		    while(dist<120)  // радиус действи€
		    {
		      dist++;

			 x += -sin(angleX/180*PI);    X=x/size;
             y +=  tan(angleY/180*PI);    Y=y/size;
             z += -cos(angleX/180*PI);    Z=z/size;
			
		     if (check(X,Y,Z))
			   if (mLeft) { mass[X][Y][Z]=0; break;}
             else   {mass[oldX][oldY][oldZ]=1; break;}
			   
			 oldX=X; oldY=Y; oldZ=Z;
			}
	      }
  
mLeft=mRight=0;

        
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(p.x,p.y+p.h/2,p.z,p.x-sin(angleX/180*PI),p.y+p.h/2+(tan(angleY/180*PI)),p.z-cos(angleX/180*PI), 0, 1, 0); 

     
//////////рисуем боксы///////
   int R = 8;  
		
   int X=p.x/size;
   int Y=p.y/size;
   int Z=p.z/size;
	
    for(int x=X-R; x<X+R; x++)
 	 for(int y=0;y<25;y++)
 	  for(int z=Z-R;z<Z+R;z++)
	  {
		  if (!check(x,y,z)) continue;

		   glTranslatef(size*x+size/2, size*y+size/2, size*z+size/2);

		   createBox(box, size/2);

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
    for(int x=X2-R2; x<X2+R2; x++)
 	  for(int z=Z-R2;z<Z+R2;z++)
	  {
		  if(x<0 || z<0 || x>999 || z>999)img.setPixel((x-(X2-R2)), (z-(Z-R2)),sf::Color::White);
		  else
		  {
			  int maxy = -1;
			  for(int n = 0; n<1000; n++)if(mass[x][n][z]==1)maxy = n;
			  if(maxy == -1) img.setPixel((x-(X2-R2)), (z-(Z-R2)),sf::Color(255, 0, 0));
			  img.setPixel((x-(X2-R2)), (z-(Z-R2)),sf::Color(20*maxy, 20*maxy, 20*maxy));
		  }
	  }/**/
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
		 Text fps("", font, 25);//создаем объект текст. закидываем в объект текст строку, шрифт, размер шрифта(в пиксел€х);//сам объект текст (не строка)
		 fps.setColor(Color::Green);//покрасили текст в красный. если убрать эту строку, то по умолчанию он белый
		 fps.setStyle(sf::Text::Bold || sf::Text::Regular);//жирный и подчеркнутый текст. по умолчанию он "худой":)) и не подчеркнутый

	  	fps.setString("FPS: " + std::to_string((long double)ceil(((float)1000/(float)time*0.02))));//задаем строку тексту и вызываем сформированную выше строку методом .str() 
		fps.setPosition(20, -2);//задаем позицию текста, отступа€ от центра камеры
		
		
		


	  ///skybox

	   glTranslatef(p.x, p.y, p.z);
	   createBox(skybox,1000);
	   glTranslatef(-p.x, -p.y, -p.z);
	   
	   
		window.pushGLStates();
		window.draw(s);      //рисуем курсор
		window.draw(map);
		window.draw(fps);
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
