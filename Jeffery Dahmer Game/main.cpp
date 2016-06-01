
/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, and, strings
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <SDL_image.h>

#include <sstream>
#include <iostream>

std::string IntToString (int integer);
class number
{
public:

    void render (int x, int y, int width, int height,  std::string number);

private:




};

//The actual hardware texture
SDL_Texture* Intro[1586];
SDL_Texture* ChildHood [2];
SDL_Texture* CrimeScene;
SDL_Texture* trial [3];
SDL_Texture* death;
SDL_Texture* menu;
SDL_Texture* society;
SDL_Texture* Student;





class maps
{
public:
    void ScrollingMaps (void);
    void SpaceShipRender (void);
    bool collision (void);

private:
    int YScroll=0;
    void render (int x, int y, int width, int height,  int MapNumber);
    int random=1;
    int Last=1;
    int speed=0;

};
int IntroW=0;
int IntroH=0;
int RocketW=0;
int RocketH=0;
int NumberW=0;
int NumberH=0;

class buttons
{

public:
    void render (void);
    bool ClickedPause (int xcoordinate, int ycoordinate);


private:




};
//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();

    //Deallocates memory
    ~LTexture();



    bool loadMedia(void);
    SDL_Texture* loadFromFile( std::string path, int width, int height );


    //Deallocates texture
    void free();



    //Renders texture at given point
    void render( int x, int y, SDL_Texture* Texture,int width,int height,  SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );



    //Gets image dimensions
    int getWidth();
    int getHeight();




private:
    //The actual hardware texture
    SDL_Texture* mTexture;


};



//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;
SDL_Surface *screen =NULL;
LTexture gSplashTexture;

//Screen dimensions
SDL_Rect gScreenRect = { 0, 0, 320, 240 };
int RocketXDifference=0;
int RocketYDifference=0;
int RocketX=0;
int RocketY=0;


bool buttons::ClickedPause (int xcoordinate, int ycoordinate)
{
    if (xcoordinate>=gScreenRect.w-100 and ycoordinate<=100)
    {
        return true;
    }
    return false;
}


LTexture::LTexture()
{
    //Initialize
    mTexture = NULL;

}
bool IntroRender (int x, int y)
{
    //Event handler
    SDL_Event e;
    LTexture texture;
    std::string counter="";

    for (int i=0; i<1502; i+=2)
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
            SDL_RenderClear( gRenderer );
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                return false;
            }
        }
        bool quit=false;
        counter+="IntroPics/Intro";
        counter+=IntToString(i+1);
        counter+=".jpg";
        Intro [i]=texture.loadFromFile( counter.c_str(),gScreenRect.w, gScreenRect.h);
        gSplashTexture.render(x, y,Intro[i],IntroW, IntroH);
        //Update screen
        SDL_RenderPresent( gRenderer );
        if (Intro [i]!=NULL)

        {
            SDL_DestroyTexture( Intro [i] );
            Intro [i] = NULL;
        };

        printf(counter.c_str());
        counter="";
        SDL_Delay(10);

    }

//    //Render splash
//    for (int i=0 ; i<1410; i++)
//
//    {
//    if (Intro [i]!=NULL)
//
//        {
//            SDL_DestroyTexture( Intro [i] );
//           Intro [i] = NULL;
//        };
//    if (i<910)
//    Intro [i+500]=texture.loadFromFile( counter.c_str(),gScreenRect.w, gScreenRect.h);
//    }
    return true;
}
std::string IntToString (int integer)
{


    std::stringstream convert;   // stream used for the conversion

    convert << integer;      // insert the textual representation of 'Number' in the characters in the stream

    return convert.str();
}
char IntToChar (int integer)
{
    return (integer+48);
}

void maps::render (int x, int y, int width, int height,  int MapNumber)
{



    //Render splash
    // gSplashTexture.render(x, y,Map[MapNumber-1],MapW, MapH);
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

SDL_Texture* LTexture::loadFromFile( std::string path, int width, int height )
{


    //The final texture
    SDL_Texture* newTexture = IMG_LoadTexture(gRenderer,path.c_str());




    if( newTexture == NULL )
    {
        printf( "Unable to create texture from %s! SDL Error:%s\n", path.c_str(), SDL_GetError() );
    }




    return newTexture;
}




void LTexture::free()
{
    //Free texture if it exists
    if( mTexture != NULL )
    {
        SDL_DestroyTexture( mTexture );
        mTexture = NULL;


    }


    for (int i=0; i<1410; i++)
    {
        if (Intro [i]!=NULL)

        {
            SDL_DestroyTexture( Intro [i] );
            Intro [i] = NULL;
        }
    }


}





void LTexture::render( int x, int y, SDL_Texture* Texture ,int width,int height, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, width, height };

    //Set clip rendering dimensions
    if( clip != NULL )
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx( gRenderer, Texture, clip, &renderQuad, angle, center, flip );
}






bool init()
{
    //Initialization flag
    bool success = true;




    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        SDL_Log( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {

        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            SDL_Log( "Warning: Linear texture filtering not enabled!" );
        }

        //Get device display mode
        SDL_DisplayMode displayMode;
        if( SDL_GetCurrentDisplayMode( 0, &displayMode ) == 0 )
        {
            gScreenRect.w = displayMode.w-100;
            gScreenRect.h = displayMode.h-100;

        }

        //Create window
        gWindow = SDL_CreateWindow( "Jeffrey Dahmer, Once a Killer, Always a Killer?", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenRect.w, gScreenRect.h, SDL_WINDOW_SHOWN);
        if( gWindow == NULL )
        {
            SDL_Log( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                SDL_Log( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            }
        }
    }

    return success;
}

bool LTexture::loadMedia(void)
{
//Get rid of preexisting texture
    free();
    std::string counter="";




    IntroW=gScreenRect.w;
    IntroH=gScreenRect.h;
    ChildHood [0]=loadFromFile( "Child/HisChildhood1.png",  gScreenRect.w, gScreenRect.w );
    ChildHood [1]=loadFromFile( "Child/HisChildhood2.png", gScreenRect.w, gScreenRect.w);
    CrimeScene=loadFromFile( "TheCrimeScene.png", gScreenRect.w, gScreenRect.w);
    trial [0]=loadFromFile( "TheTrial/TheTrial1.png", gScreenRect.w, gScreenRect.w);
    trial [1]=loadFromFile( "TheTrial/TheTrial2.png", gScreenRect.w, gScreenRect.w);
    trial [2]=loadFromFile( "TheTrial/TheTrial3.png", gScreenRect.w, gScreenRect.w);
    menu=loadFromFile( "Menu.png", gScreenRect.w, gScreenRect.w);
    society=loadFromFile( "ImpactOnSociety.png", gScreenRect.w, gScreenRect.w);
    //student=loadFromFile( "ImpactOnSociety.png", gScreenRect.w, gScreenRect.w);
    death=loadFromFile( "HisDeath.png", gScreenRect.w, gScreenRect.w);
    Student=loadFromFile( "Student.png", gScreenRect.w, gScreenRect.w);




    return true;




}


void close()
{
    //Free loaded images
    gSplashTexture.free();

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    bool Menu=false;
    int  Clickx=0;
    int Clicky=0;
    bool court=false;
    bool home= false;
    bool scene=false;
    bool prison=false;
    bool impact= false;
    bool student=false;
    bool DisplayMenu=false;
    int counts=0;
    number Num;
    maps Maps;
    int counter=0;

    buttons Buttons;
    bool pause=false;
    //Start up SDL and create window
    if( !init())
    {
        SDL_Log( "Failed to initialize!\n" );
    }
    else
    {

        //Main loop flag
        bool quit = false;

        //Event handler
        SDL_Event e;
        RocketXDifference=0;
        RocketYDifference=0;
        gSplashTexture.loadMedia();

        //While application is running
        while( !quit )
        {

            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }

                else if( e.type == SDL_WINDOWEVENT )
                {
                    //Window resize/orientation change
                    if( e.window.event == SDL_WINDOWEVENT_SIZE_CHANGED )
                    {

                        //Get screen dimensions
                        gScreenRect.w = e.window.data1;
                        gScreenRect.h = e.window.data2;

                        gSplashTexture.loadMedia();





                        //Update screenRocketY-gScreenRect.h/5
                        SDL_RenderPresent( gRenderer );
                    }

                }

            }


            //Clear screen
            SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );
            SDL_RenderClear( gRenderer );





            //Maps.collision();



            //Maps.ScrollingMaps();

            if (counter==0)

            {
                if (!(IntroRender(( gScreenRect.w - gScreenRect.w/2 - gScreenRect.w/3 - gScreenRect.w/5) / 2, 0))) break;

                while (true)
                {
                    Clickx=0;
                    Clicky=0;
                    //Handle events on queue
                    while( SDL_PollEvent( &e ) != 0 )
                    {
                        //User requests quit
                        if( e.type == SDL_QUIT )
                        {
                            //Free resources and close SDL
                            close();

                            return 0;
                        }
                        else if(e.type == SDL_MOUSEBUTTONDOWN)
                        {
                            Clickx=e.button.x;
                            Clicky=e.button.y;
                        }
                    }
                    std::cout<<std::endl<<"x="<<Clickx;
                    std::cout<<std::endl<<"y="<<Clicky;
                    if ((court==false and home==false and scene==false and prison==false and impact==false and student==false))
                    {
                        counts=0;
                        if (Clickx<=gScreenRect.w/1.35869565217 and Clickx>=gScreenRect.w/4.71698113208 and Clicky<=gScreenRect.h/1.16959064327 and Clicky>=gScreenRect.h/1.48148148148 and Menu!=true or DisplayMenu==true)
                        {
                            gSplashTexture.render(( gScreenRect.w - gScreenRect.w/2 - gScreenRect.w/3 - gScreenRect.w/5) / 2,0,menu,IntroW, IntroH);
                            //Update screen
                            SDL_RenderPresent( gRenderer );
                            Menu=true;
                            DisplayMenu=false;
                        }
                        else if (Menu==true and Clickx<=gScreenRect.w/2.1676300578 and Clickx>=gScreenRect.w/7.69230769231 and Clicky<=gScreenRect.h/5.19480519481 and Clicky>=gScreenRect.h/10.6666666667 )
                        {

                            court=true;
                            home= false;
                            scene=false;
                            prison=false;
                            impact= false;
                            student=false;
                        }
                        else if (Menu==true and Clickx<=gScreenRect.w/1.19426751592 and Clickx>=gScreenRect.w/1.97368421053 and Clicky<=gScreenRect.h/5.19480519481 and Clicky>=gScreenRect.h/10.6666666667  )
                        {
                            court=false;
                            home= true;
                            scene=false;
                            prison=false;
                            impact= false;
                            student=false;
                        }
                        else if (Menu==true and Clickx<=gScreenRect.w/2.1676300578 and Clickx>=gScreenRect.w/7.69230769231 and Clicky<=gScreenRect.h/1.86046511628 and Clicky>=gScreenRect.h/2.30547550432 )
                        {
                            court=false;
                            home= false;
                            scene=true;
                            prison=false;
                            impact= false;
                            student=false;
                        }
                        else if (Menu==true and Clickx<=gScreenRect.w/1.19426751592 and Clickx>=gScreenRect.w/1.97368421053 and Clicky<=gScreenRect.h/1.86046511628 and Clicky>=gScreenRect.h/2.30547550432 )
                        {
                            court=false;
                            home= false;
                            scene=false;
                            prison=true;
                            impact= false;
                            student=false;
                        }
                        else if (Menu==true and Clickx<=gScreenRect.w/2.1676300578 and Clickx>=gScreenRect.w/7.69230769231 and Clicky<=gScreenRect.h/1.21396054628 and Clicky>=gScreenRect.h/1.3816925734  )
                        {
                            court=false;
                            home= false;
                            scene=false;
                            prison=false;
                            impact= true;
                            student=false;
                        }
                        else if (Menu==true and Clickx<=gScreenRect.w/1.19426751592 and Clickx>=gScreenRect.w/1.97368421053 and  Clicky<=gScreenRect.h/1.21396054628 and Clicky>=gScreenRect.h/1.3816925734  )
                        {
                            court=false;
                            home= false;
                            scene=false;
                            prison=false;
                            impact= false;
                            student=true;
                        }

                    }
                    else
                    {

                        if (court==true)
                        {
                            gSplashTexture.render(( gScreenRect.w - gScreenRect.w/2 - gScreenRect.w/3 - gScreenRect.w/5) / 2,0,trial[counts],IntroW, IntroH);
                            //Update screen
                            SDL_RenderPresent( gRenderer );
                            if (Clickx<=gScreenRect.w/1.31694468832+100 and Clickx>=gScreenRect.w/1.97889182058 and Clicky<=gScreenRect.h and Clicky>=gScreenRect.h/1.09140518417)
                            {
                                if (counts<2)
                                {
                                    counts++;
                                }
                            }
                        }
                        else if (home==true)
                        {
                            gSplashTexture.render(( gScreenRect.w - gScreenRect.w/2 - gScreenRect.w/3 - gScreenRect.w/5) / 2,0,ChildHood [counts],IntroW, IntroH);
                            //Update screen
                            SDL_RenderPresent( gRenderer );
                             if (Clickx<=gScreenRect.w/1.31694468832+100 and Clickx>=gScreenRect.w/1.97889182058 and Clicky<=gScreenRect.h and Clicky>=gScreenRect.h/1.09140518417)
                            {
                                if (counts==0)
                                {
                                    counts++;
                                }
                            }
                        }
                        else if (scene==true)
                        {
                            gSplashTexture.render(( gScreenRect.w - gScreenRect.w/2 - gScreenRect.w/3 - gScreenRect.w/5) / 2,0,CrimeScene,IntroW, IntroH);
                            //Update screen
                            SDL_RenderPresent( gRenderer );
                        }
                        else if (prison==true)
                        {
                            gSplashTexture.render(( gScreenRect.w - gScreenRect.w/2 - gScreenRect.w/3 - gScreenRect.w/5) / 2,0,death,IntroW, IntroH);
                            //Update screen
                            SDL_RenderPresent( gRenderer );
                        }
                        else if (impact==true)
                        {
                            gSplashTexture.render(( gScreenRect.w - gScreenRect.w/2 - gScreenRect.w/3 - gScreenRect.w/5) / 2,0,society,IntroW, IntroH);
                            //Update screen
                            SDL_RenderPresent( gRenderer );
                        }
                        else if (student==true)
                        {
                            gSplashTexture.render(( gScreenRect.w - gScreenRect.w/2 - gScreenRect.w/3 - gScreenRect.w/5) / 2,0,Student,IntroW, IntroH);
                                //Update screen
                                SDL_RenderPresent( gRenderer );
                        }

                        if (Clickx<=gScreenRect.w/1.1655011655 and Clickx>=gScreenRect.w/1.9305019305 and Clicky<=gScreenRect.h/12.3076923077 and Clicky>=0)
                        {
                            court=false;
                            home= false;
                            scene=false;
                            prison=false;
                            impact= false;
                            student=false;
                            DisplayMenu=true;
                        }


                    }
                }
            }


        }
    }





//Free resources and close SDL
    close();

    return 0;
}
