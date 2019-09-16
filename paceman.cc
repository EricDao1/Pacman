#include <stdio.h>
#include <allegro5/allegro.h>
#include <iostream>
using namespace std;
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>//allows .wav, .flac, .ogg, .it, .mod, .s3m, .xm
#include <math.h>
#include <allegro5\allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

   int maxFrame2 = 2;
	int curFrame2 = 0;
	int frameCount2 = 0;
	int frameWidth2 = 35;
	int frameHeight2 = 35;
	int frameDelay2 = 5;

	
	class ghost{
public:
    ghost();
    void initGhost(int x, int y, char c, int dir, bool dead, int Gspeed);
    bool isdead();
    void drawGhost();
    void printInfo();
    void chase(int x, int y, int level[20][20]);
	void chase2(int x, int y, int level[20][20]);
	void chase3(int x, int y, int level[20][20]);
	void chase4(int x, int y, int level[20][20]);
private:
    ALLEGRO_BITMAP* Blinky;
	ALLEGRO_BITMAP* Inky;
	ALLEGRO_BITMAP* Pinky;
	ALLEGRO_BITMAP* Clyde;
	int hitwall;

    int xpos;
    int ypos;
    char color;
    int direction;
    bool dead;
    int speed;
};


const int RIGHT = 1;
const int LEFT = 2;
const int DOWN = 3;
const int UP = 4;
const int PACSIZE = 35;

const int WALLSIZE = 40;


int collision( int pacman_x,int pacman_y, int dir, int level[20][20]);
	

int main(int argc, char **argv)
{
	ALLEGRO_DISPLAY *display = NULL;
	ALLEGRO_EVENT_QUEUE *event_queue = NULL;
	ALLEGRO_TIMER *timer = NULL;
	ALLEGRO_BITMAP *pacman = NULL;
	ALLEGRO_BITMAP *wall = NULL;
	ALLEGRO_BITMAP *dot = NULL;
	int score = 0;


	ghost blinky;
	blinky.initGhost(362,322,'r',30,0,2);
	
	ghost clyde;
	clyde.initGhost(400,370,'o',30,0,2);
	
		ghost pinky;
	pinky.initGhost(390,350,'p',30,0,2);

		ghost inky;
	inky.initGhost(380,340,'b',30,0,2);




	const int maxFrame = 6;
	int curFrame = 0;
	
	int frameCount = 0;
	int frameDelay = 5;
	int frameWidth = 35;
	int frameHeight = 35;

	

	//these two variables hold the x and y positions of the pacman
	//initalize these variables to where you want your pacman to start
	int pacman_x = 50;
	int pacman_y = 50;
	

	

	//here's our key states. they're all starting as "false" because nothing has been pressed yet.
	//the first slot represents "up", then "down", "left" and "right"
	bool key[4] = { false, false, false, false };

	//don't redraw until an event happens
	bool redraw = true;

	//this controls our game loop
	bool doexit = false;

	al_init();

	//get the keyboard ready to use
	al_install_keyboard();

	timer = al_create_timer(.02);

	display = al_create_display(800, 800);

	al_init_primitives_addon();



	int level[20][20]={
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,2,2,2,2,2,2,2,2,2,1,2,2,2,2,2,2,2,2,1,
		1,2,2,1,1,2,1,1,1,2,1,2,1,1,1,2,1,1,2,1,
		1,2,2,2,2,2,1,2,2,2,2,2,2,1,2,2,2,2,2,1,
		1,1,1,1,2,2,1,2,2,1,1,2,2,1,2,1,1,1,1,1,
		1,2,2,2,2,2,1,2,2,1,1,2,2,1,2,2,2,2,2,1,
		1,2,2,1,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,
		1,2,1,1,1,2,1,1,1,2,1,1,1,2,2,1,2,2,2,1,
		1,2,2,1,2,2,1,1,2,2,2,1,1,2,1,1,1,2,2,1,
		1,1,2,1,2,2,1,1,1,1,1,1,1,2,2,1,2,2,1,1,
		1,2,2,1,2,2,2,2,2,2,2,2,2,2,2,1,2,2,2,1,
		1,2,2,2,2,1,1,1,1,1,1,1,1,1,2,2,2,2,2,1,
		1,1,1,2,2,2,2,2,2,2,2,2,2,2,2,1,2,1,1,1,
		1,2,2,2,1,2,1,1,1,1,1,1,1,2,1,1,2,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,2,1,1,2,1,1,2,2,1,2,2,1,1,1,2,1,1,2,1,
		1,2,2,1,2,2,2,2,1,1,1,2,2,2,2,2,1,2,2,1,
		1,2,2,1,2,1,1,2,2,1,2,2,1,1,1,2,1,2,2,1,
		1,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

		for(int i = 0; i<20; i++){
			for(int j = 0; j<20; j++){
				cout<<level[i][j]<<" ";
			}
			cout<<endl;

		}

		ALLEGRO_SAMPLE *sample=NULL;
		al_install_audio();
		al_init_acodec_addon();
		al_reserve_samples(1);
		sample = al_load_sample( "Ding.wav" );


		al_init_image_addon();
		 al_init_font_addon(); 
   al_init_ttf_addon();

		ALLEGRO_FONT *font = al_load_ttf_font("Candara.ttf",72,0 );
 



		pacman = al_load_bitmap("pacman.png");
		al_convert_mask_to_alpha(pacman, al_map_rgb(255,255,255));
		//pacman=al_create_bitmap(35,35);
		



		wall = al_create_bitmap(40,40);

		dot = al_create_bitmap(6,6);

		al_set_target_bitmap(dot);

		al_clear_to_color(al_map_rgb(0, 255, 255));

		al_set_target_bitmap(wall);

		al_clear_to_color(al_map_rgb(255, 0, 255));

		//al_set_target_bitmap(pacman);

		//al_clear_to_color(al_map_rgb(255, 255, 0));

		al_set_target_bitmap(al_get_backbuffer(display));

		event_queue = al_create_event_queue();

		al_register_event_source(event_queue, al_get_display_event_source(display));

		al_register_event_source(event_queue, al_get_timer_event_source(timer));

		//tell the event queue that it should take keyboard events, too 
		al_register_event_source(event_queue, al_get_keyboard_event_source());

		al_clear_to_color(al_map_rgb(0,0,0));

		al_flip_display();

		al_start_timer(timer);

		//so the game loop is set to act on "ticks" of the timer OR keyboard presses 
		//OR the mouse closing the display
		while(!doexit)
		{ cout<<pacman_x<< pacman_y<<endl;
			ALLEGRO_EVENT ev;
			al_wait_for_event(event_queue, &ev);

			//////////////////////////////////////////////////////////////////////////////////////////////////
			//here's the movement algorithm

			if(ev.type == ALLEGRO_EVENT_TIMER) {

			if(++frameCount2 >= frameDelay2){
				if(++curFrame2>= maxFrame2)
					curFrame2 = 0;
					frameCount2 = 0;
					}

				//if the up button is pressed AND we're still below the top wall,
				//move the box "up" by 4 pixels
				if(key[0] && !collision(pacman_x, pacman_y, UP, level)) {
					pacman = al_load_bitmap("pacmanup.png");
					al_convert_mask_to_alpha(pacman, al_map_rgb(255,255,255));
					pacman_y -= 4.0;
					if(++frameCount >= frameDelay){
						if(++curFrame>= maxFrame)
							curFrame = 0;
						frameCount = 0;
					}
				}

				//if the down button is pressed AND we're still above the bottom wall
				//move the box "down" by 4 pixels
				if(key[1] && !collision(pacman_x, pacman_y, DOWN, level)) {
					pacman = al_load_bitmap("pacmandown.png");
					al_convert_mask_to_alpha(pacman, al_map_rgb(255,255,255));
					pacman_y += 4.0;
					if(++frameCount >= frameDelay){
						if(++curFrame>= maxFrame)
							curFrame = 0;
						frameCount = 0;
					}
				}
				
				//if the left button is pressed AND we're still right of the left wall
				//move the box left by 4 pixels
				if(key[2] &&  !collision(pacman_x, pacman_y, LEFT, level)) {

					pacman = al_load_bitmap("pacmanleft.png");
					al_convert_mask_to_alpha(pacman, al_map_rgb(255,255,255));
					pacman_x -= 4.0;
					if(++frameCount >= frameDelay){
						if(++curFrame>= maxFrame)
							curFrame = 0;
						frameCount = 0;
					}
				}

				//if the left button is pressed AND we're still left of the right wall
				//move the box right by 4 pixels
				if(key[3] && !collision(pacman_x, pacman_y, RIGHT, level)) {

					pacman = al_load_bitmap("pacmanright.png");
					al_convert_mask_to_alpha(pacman, al_map_rgb(255,255,255));
					pacman_x += 4.0;
					if(++frameCount >= frameDelay){
						if(++curFrame>= maxFrame)
							curFrame = 0;
						frameCount = 0;
					}
				}



				//call function for chase



				//////////eating dots!
				if(level[pacman_y/40][pacman_x/40]==2){
					al_play_sample(sample, 1.0, 0.0,4,ALLEGRO_PLAYMODE_ONCE,NULL);
					score++;
					level[pacman_y/40][pacman_x/40]=0;
				}

				//if(pacman_x<0){
				//  pacman_x=800;
				//  pacman_y=500;
				// }




				//redraw at every tick of the timer
				redraw = true;
			}
			///////////////////////////////////////////////////////////////////////////////////////////////////////
			else if(ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				break;
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////
			//here's the algorithm that turns key presses into events
			//a "key down" event is when a key is pushed
			//while a "key up" event is when a key is released

			//has something been pressed on the keyboard?
			else if(ev.type == ALLEGRO_EVENT_KEY_DOWN) {

				//"keycode" holds all the different keys on the keyboard
				switch(ev.keyboard.keycode) {

					//if the up key has been pressed
				case ALLEGRO_KEY_UP:
					key[0] = true;
					break;

					//if the down key has been pressed
				case ALLEGRO_KEY_DOWN:
					key[1] = true;
					break;

					//if the left key has been pressed
				case ALLEGRO_KEY_LEFT: 
					key[2] = true;
					break;

					//if the right key has been pressed
				case ALLEGRO_KEY_RIGHT:
					key[3] = true;
					break;
				}
			}
			//has something been released on the keyboard?
			else if(ev.type == ALLEGRO_EVENT_KEY_UP) {
				switch(ev.keyboard.keycode) {
				case ALLEGRO_KEY_UP:
					key[0] = false;
					break;

				case ALLEGRO_KEY_DOWN:
					key[1] = false;
					break;

				case ALLEGRO_KEY_LEFT: 
					key[2] = false;
					break;

				case ALLEGRO_KEY_RIGHT:
					key[3] = false;
					break;

					//kill the program if someone presses escape
				case ALLEGRO_KEY_ESCAPE:
					doexit = true;
					break;
				}
			}

			//if the clock ticked but no other events happened, don't bother redrawing
			if(redraw && al_is_event_queue_empty(event_queue)) {
				redraw = false;

				//paint black over the old screen, so the old pacman dissapears
				al_clear_to_color(al_map_rgb(0,0,0));

				//the algorithm above just changes the x and y coordinates
				//here's where the bitmap is actually drawn somewhere else
				//al_draw_bitmap(pacman, pacman_x, pacman_y, 0);
				if(blinky.isdead()==0)
						blinky.drawGhost();
					blinky.chase(pacman_x,pacman_y,level);

					if(clyde.isdead()==0)
						clyde.drawGhost();
					clyde.chase(pacman_x,pacman_y,level);

					if(inky.isdead()==0)
						inky.drawGhost();
					inky.chase(pacman_x,pacman_y,level);

					if(pinky.isdead()==0)
						pinky.drawGhost();
					pinky.chase(pacman_x,pacman_y,level);
				
					
					al_draw_bitmap_region(pacman, curFrame*frameWidth, 0, frameWidth, frameHeight, pacman_x, pacman_y, 0);





				for(int i = 0; i<20; i++)
					for(int j = 0; j<20; j++){
						if(level[j][i]==1)
							al_draw_bitmap(wall, i*40, j*40,0);                                                                                                                
						else  if(level[j][i]==2)
							al_draw_bitmap(dot, i*40+20, j*40+20,0);
						

					}
					al_draw_textf(font, al_map_rgb(255,255,255), 420, 1,ALLEGRO_ALIGN_CENTRE,"%d", score);
					al_flip_display();
			}
		}

		
		al_destroy_bitmap(pacman);
		al_destroy_bitmap(dot);
		al_destroy_bitmap(wall);
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);

		return 0;
}
int collision(int pacman_x, int pacman_y, int dir, int level[20][20]){

	int xcord = 0;
	int xcord1 = 0;
	int xcord2 = 0;


	int ycord = 0;
	int ycord1 = 0;
	int ycord2 = 0;


	if(dir == RIGHT){ 		// Moving Right
		// Check along the far right side of the sprite, plus 3 (the amount we’re moving)
		xcord = pacman_x + 3 + PACSIZE;
		xcord1 = pacman_x + 3 + PACSIZE;
		xcord2 = pacman_x + 3 + PACSIZE;
		// Check at three point along that edge
		ycord = pacman_y;
		ycord1 = pacman_y+PACSIZE/2;
		ycord2 = pacman_y+PACSIZE;




	} 
	if(dir == UP){
		xcord = pacman_x;
		xcord1 = pacman_x + PACSIZE/2;
		xcord2 = pacman_x + PACSIZE;

		ycord = pacman_y - 3;
		ycord1 = pacman_y - 3;
		ycord2 = pacman_y - 3;
	}

	if(dir == DOWN){
		xcord = pacman_x;
		xcord1 = pacman_x + PACSIZE/2;
		xcord2 = pacman_x + PACSIZE;

		ycord = pacman_y + 3 + PACSIZE;
		ycord1 = pacman_y + 3 + PACSIZE;
		ycord2 = pacman_y + 3 + PACSIZE;
	}

	if(dir == LEFT){
		xcord = pacman_x -3;
		xcord1 = pacman_x - 3;
		xcord2 = pacman_x -3;

		ycord = pacman_y;
		ycord1 = pacman_y + PACSIZE/2;
		ycord2 = pacman_y + PACSIZE;
	}


	int new_cell_x1 = xcord/WALLSIZE;
	int new_cell_x2 = xcord1/WALLSIZE;
	int new_cell_x3 = xcord2/WALLSIZE;
	int new_cell_y1 = ycord/WALLSIZE;
	int new_cell_y2 = ycord1/WALLSIZE;
	int new_cell_y3 = ycord2/WALLSIZE;

	if((level[new_cell_y1][new_cell_x1] == 1)
		||(level[new_cell_y2][new_cell_x2]==1)
		||(level[new_cell_y3][new_cell_x3]==1))




	{
		cout<<"Collision!"<<endl;

		return 1;
	}
	else return 0;
}

ghost::ghost(){
	 hitwall = 0;
     xpos = 0;
     ypos= 0;
     color = 'r';
     direction = 1;
     dead = 0;
     speed = 0;
	ALLEGRO_BITMAP* Blinky = NULL;
	ALLEGRO_BITMAP* Inky = NULL;
	ALLEGRO_BITMAP* Pinky = NULL;
	ALLEGRO_BITMAP* Clyde = NULL;

}

void ghost::drawGhost(){
	//al_draw_filled_rectangle(xpos, ypos, xpos + PACSIZE, ypos + PACSIZE, al_map_rgb(255,0,0));
	if(color =='r'){
			if(direction == 1){
		Blinky = al_load_bitmap("blinky_right.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}
			if(direction == 2){
		Blinky = al_load_bitmap("blinky_left.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}
			if(direction == 3){
		Blinky = al_load_bitmap("blinky_down.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}
			if(direction == 4){
		Blinky = al_load_bitmap("blinky_up.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}

	}
	if(color =='o'){
			if(direction == 1){
		Blinky = al_load_bitmap("clyde_right.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}
			if(direction == 2){
		Blinky = al_load_bitmap("clyde_left.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}
			if(direction == 3){
		Blinky = al_load_bitmap("clyde_down.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}
			if(direction == 4){
		Blinky = al_load_bitmap("clyde_up.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}

	}
	if(color =='p'){
			if(direction == 1){
		Blinky = al_load_bitmap("pinky_right.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}
			if(direction == 2){
		Blinky = al_load_bitmap("pinky_left.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}
			if(direction == 3){
		Blinky = al_load_bitmap("pinky_down.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}
			if(direction == 4){
		Blinky = al_load_bitmap("pinky_up.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}

	}

	if(color =='b'){
			if(direction == 1){
		Blinky = al_load_bitmap("inky_right.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}
			if(direction == 2){
		Blinky = al_load_bitmap("inky_left.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}
			if(direction == 3){
		Blinky = al_load_bitmap("inky_down.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}
			if(direction == 4){
		Blinky = al_load_bitmap("inky_up.png");
			al_draw_bitmap_region(Blinky, curFrame2*frameWidth2, 0, frameWidth2, frameHeight2, xpos, ypos, 0);
}

	}



}

	void ghost::initGhost(int x, int y, char c, int dir, bool dead, int Gspeed){
		xpos = x;
		ypos = y;
		color = c;
		dir = dir;
		dead = dead;
		speed = Gspeed;
	}

	bool ghost::isdead(){
		return dead;
	} 


	//chase function. x and y are pacman's position.
void ghost::chase(int x, int y, int level[20][20]){

	
    /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/


    //this is just for testing
    cout << "state is " << direction << endl;
    if (collision(xpos, ypos, 2, level))
        cout << "there's a wall to the left of me" << endl;
    if (collision(xpos, ypos, 4, level))
        cout << "there's a wall above me" << endl;
    if (collision(xpos, ypos, 1, level))
        cout << "there's a wall to the right of me" << endl;
    if (collision(xpos, ypos, 3, level))
        cout << "there's a wall below me" << endl;

    /////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////


	  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/



    //if we're moving left and there's an opening above and pacman is above, move up
    if ((direction == 2) && !collision(xpos, ypos, 4, level) && y<ypos)
        while (!collision(xpos, ypos, 4, level)){
            cout << "trying to move through hole above!" << endl;
            direction = 4;
            ypos-=4;
            return;
        }

    //if we're moving left and there's an opening below and pacman is below, move down
    if ((direction == 2) && !collision(xpos, ypos, 3, level) && y>ypos)
        while (!collision(xpos, ypos, 3, level)){
            cout << "trying to move through hole below!" << endl;
            direction = 3;
            ypos+=3;
            return;
        }


    if (direction == 2)//left
        while (!collision(xpos, ypos, 2, level)){
            xpos-=4;
            return;
        }


		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    ////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

    //if we're moving up and there's an opening left and pacman is left, move left
    if ((direction == 4) && !collision(xpos, ypos, 2, level) && x<xpos)
        while (!collision(xpos, ypos, 2, level)){
            cout << "trying to move through hole to left!" << endl;
            direction = 2;
            xpos-=3;
            return;
        }
    //if we're moving up and there's an opening right and pacman is right, move right
    if ((direction == 4) && !collision(xpos, ypos, 1, level) && x>xpos)
        while (!collision(xpos, ypos, 1, level)){
            cout << "trying to move through hole to right!" << endl;
            direction = 1;
            xpos+=3;
            return;
        }
    if (direction == 4)//up
        while (!collision(xpos, ypos, 4, level)){
            ypos-=3;
            return;
        }


		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    /////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
    //if we're moving right and there's an opening above and pacman is above, move up
    if ((direction == 1) && !collision(xpos, ypos, 4, level) && y<ypos)
        while (!collision(xpos, ypos, 4, level)){
            cout << "trying to move through hole above!" << endl;
            direction = 4;
            ypos-=3;
            return;
        }

    //if we're moving right and there's an opening below and pacman is below, move down
    if ((direction == 1) && !collision(xpos, ypos, 3, level) && y>ypos)
        while (!collision(xpos, ypos, 3, level)){
            cout << "trying to move through hole below!" << endl;
            direction = 3;
            ypos+=3;
            return;
        }
   
   
    if (direction == 1)//right
        while (!collision(xpos, ypos, 1, level)){
            xpos+=3;
            return;
        }


		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    //////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
    //if we're moving up and there's an opening left and pacman is left, move left
    if ((direction == 3) && !collision(xpos, ypos, 2, level) && x<xpos)
        while (!collision(xpos, ypos, 2, level)){
            cout << "trying to move through hole to left!" << endl;
            direction = 2;
            xpos-=3;
            return;
        }
    //if we're moving up and there's an opening right and pacman is right, move right
    if ((direction == 3) && !collision(xpos, ypos, 1, level) && x>xpos)
        while (!collision(xpos, ypos, 1, level)){
            cout << "trying to move through hole to right!" << endl;
            direction = 1;
            xpos+=3;
            return;
        }

    if (direction == 3)//down
        while (!collision(xpos, ypos, 3, level)){
            ypos+=3;
            return;
        }



		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    ///////////////////////////////////////////////////////////////////////////////////////
    //if pacman is above and there's no wall there, move up
    if ((y<ypos) && !collision(xpos, ypos, 4, level)){
        cout << "direction is up" << endl;
        direction = 4;
        return;
    }


    //if pacman is below and there's no wall there, move down
    if ((y>ypos) && !collision(xpos, ypos, 3, level)){
        direction = 3;
        cout << "direction is down" << endl;
        return;
    }

    //if pacman is right and there's no wall there, move right
    if ((x>xpos) && !collision(xpos, ypos, 1, level)){
        direction = 1;
        cout << "direction is right" << endl;
        return;
    }

    //if pacman is left and there's no wall there, move left
    if ((x<xpos) && !collision(xpos, ypos, 2, level)){
        direction = 2;
        cout << "direction is left" << endl;
        return;

    }

    //if pacman is above and there's no wall there, move up
    if (!collision(xpos, ypos, 4, level)){
        cout << "direction is up" << endl;
        direction = 4;
        return;
    }


    //if pacman is below and there's no wall there, move down
    if (!collision(xpos, ypos, 3, level)){
        direction = 3;
        cout << "direction is down" << endl;
        return;
    }

    //if pacman is right and there's no wall there, move right
    if (!collision(xpos, ypos, 1, level)){
        direction = 1;
        cout << "direction is right" << endl;
        return;
    }

    //if pacman is left and there's no wall there, move left
    if (!collision(xpos, ypos, 2, level)){
        direction = 2;
        cout << "direction is left" << endl;
        return;

    }

}

void ghost::chase2(int x, int y, int level[20][20]){

	
    /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/


    //this is just for testing
    cout << "state is " << direction << endl;
    if (collision(xpos, ypos, 2, level))
        cout << "there's a wall to the left of me" << endl;
    if (collision(xpos, ypos, 4, level))
        cout << "there's a wall above me" << endl;
    if (collision(xpos, ypos, 1, level))
        cout << "there's a wall to the right of me" << endl;
    if (collision(xpos, ypos, 3, level))
        cout << "there's a wall below me" << endl;

    /////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////


	  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/



    //if we're moving left and there's an opening above and pacman is above, move up
    if ((direction == 2) && !collision(xpos, ypos, 4, level) && y<ypos)
        while (!collision(xpos, ypos, 4, level)){
            cout << "trying to move through hole above!" << endl;
            direction = 3;
            ypos-=4;
            return;
        }

    //if we're moving left and there's an opening below and pacman is below, move down
    if ((direction == 2) && !collision(xpos, ypos, 3, level) && y>ypos)
        while (!collision(xpos, ypos, 3, level)){
            cout << "trying to move through hole below!" << endl;
            direction = 2;
            ypos+=3;
            return;
        }


    if (direction == 2)//left
        while (!collision(xpos, ypos, 2, level)){
            xpos-=4;
            return;
        }


		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    ////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

    //if we're moving up and there's an opening left and pacman is left, move left
    if ((direction == 4) && !collision(xpos, ypos, 2, level) && x<xpos)
        while (!collision(xpos, ypos, 2, level)){
            cout << "trying to move through hole to left!" << endl;
            direction = 4;
            xpos-=3;
            return;
        }
    //if we're moving up and there's an opening right and pacman is right, move right
    if ((direction == 4) && !collision(xpos, ypos, 1, level) && x>xpos)
        while (!collision(xpos, ypos, 1, level)){
            cout << "trying to move through hole to right!" << endl;
            direction = 1;
            xpos+=3;
            return;
        }
    if (direction == 4)//up
        while (!collision(xpos, ypos, 4, level)){
            ypos-=3;
            return;
        }


		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    /////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
    //if we're moving right and there's an opening above and pacman is above, move up
    if ((direction == 1) && !collision(xpos, ypos, 4, level) && y<ypos)
        while (!collision(xpos, ypos, 4, level)){
            cout << "trying to move through hole above!" << endl;
            direction = 4;
            ypos-=3;
            return;
        }

    //if we're moving right and there's an opening below and pacman is below, move down
    if ((direction == 1) && !collision(xpos, ypos, 3, level) && y>ypos)
        while (!collision(xpos, ypos, 3, level)){
            cout << "trying to move through hole below!" << endl;
            direction = 3;
            ypos+=3;
            return;
        }
   
   
    if (direction == 1)//right
        while (!collision(xpos, ypos, 1, level)){
            xpos+=3;
            return;
        }


		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    //////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
    //if we're moving up and there's an opening left and pacman is left, move left
    if ((direction == 3) && !collision(xpos, ypos, 2, level) && x<xpos)
        while (!collision(xpos, ypos, 2, level)){
            cout << "trying to move through hole to left!" << endl;
            direction = 2;
            xpos-=3;
            return;
        }
    //if we're moving up and there's an opening right and pacman is right, move right
    if ((direction == 3) && !collision(xpos, ypos, 1, level) && x>xpos)
        while (!collision(xpos, ypos, 1, level)){
            cout << "trying to move through hole to right!" << endl;
            direction = 1;
            xpos+=3;
            return;
        }

    if (direction == 3)//down
        while (!collision(xpos, ypos, 3, level)){
            ypos+=3;
            return;
        }



		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    ///////////////////////////////////////////////////////////////////////////////////////
    //if pacman is above and there's no wall there, move up
    if ((y<ypos) && !collision(xpos, ypos, 4, level)){
        cout << "direction is up" << endl;
        direction = 4;
        return;
    }


    //if pacman is below and there's no wall there, move down
    if ((y>ypos) && !collision(xpos, ypos, 3, level)){
        direction = 3;
        cout << "direction is down" << endl;
        return;
    }

    //if pacman is right and there's no wall there, move right
    if ((x>xpos) && !collision(xpos, ypos, 1, level)){
        direction = 1;
        cout << "direction is right" << endl;
        return;
    }

    //if pacman is left and there's no wall there, move left
    if ((x<xpos) && !collision(xpos, ypos, 2, level)){
        direction = 2;
        cout << "direction is left" << endl;
        return;

    }

    //if pacman is above and there's no wall there, move up
    if (!collision(xpos, ypos, 4, level)){
        cout << "direction is up" << endl;
        direction = 4;
        return;
    }


    //if pacman is below and there's no wall there, move down
    if (!collision(xpos, ypos, 3, level)){
        direction = 3;
        cout << "direction is down" << endl;
        return;
    }

    //if pacman is right and there's no wall there, move right
    if (!collision(xpos, ypos, 1, level)){
        direction = 1;
        cout << "direction is right" << endl;
        return;
    }

    //if pacman is left and there's no wall there, move left
    if (!collision(xpos, ypos, 2, level)){
        direction = 2;
        cout << "direction is left" << endl;
        return;

    }

}

void ghost::chase3(int x, int y, int level[20][20]){

	
    /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/


    //this is just for testing
    cout << "state is " << direction << endl;
    if (collision(xpos, ypos, 2, level))
        cout << "there's a wall to the left of me" << endl;
    if (collision(xpos, ypos, 4, level))
        cout << "there's a wall above me" << endl;
    if (collision(xpos, ypos, 1, level))
        cout << "there's a wall to the right of me" << endl;
    if (collision(xpos, ypos, 3, level))
        cout << "there's a wall below me" << endl;

    /////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////


	  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/



    //if we're moving left and there's an opening above and pacman is above, move up
    if ((direction == 2) && !collision(xpos, ypos, 4, level) && y<ypos)
        while (!collision(xpos, ypos, 4, level)){
            cout << "trying to move through hole above!" << endl;
            direction = 1;
            ypos-=4;
            return;
        }

    //if we're moving left and there's an opening below and pacman is below, move down
    if ((direction == 2) && !collision(xpos, ypos, 3, level) && y>ypos)
        while (!collision(xpos, ypos, 3, level)){
            cout << "trying to move through hole below!" << endl;
            direction = 4;
            ypos+=3;
            return;
        }


    if (direction == 2)//left
        while (!collision(xpos, ypos, 2, level)){
            xpos-=4;
            return;
        }


		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    ////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

    //if we're moving up and there's an opening left and pacman is left, move left
    if ((direction == 4) && !collision(xpos, ypos, 2, level) && x<xpos)
        while (!collision(xpos, ypos, 2, level)){
            cout << "trying to move through hole to left!" << endl;
            direction = 3;
            xpos-=3;
            return;
        }
    //if we're moving up and there's an opening right and pacman is right, move right
    if ((direction == 4) && !collision(xpos, ypos, 1, level) && x>xpos)
        while (!collision(xpos, ypos, 1, level)){
            cout << "trying to move through hole to right!" << endl;
            direction = 1;
            xpos+=3;
            return;
        }
    if (direction == 4)//up
        while (!collision(xpos, ypos, 4, level)){
            ypos-=3;
            return;
        }


		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    /////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
    //if we're moving right and there's an opening above and pacman is above, move up
    if ((direction == 1) && !collision(xpos, ypos, 4, level) && y<ypos)
        while (!collision(xpos, ypos, 4, level)){
            cout << "trying to move through hole above!" << endl;
            direction = 2;
            ypos-=3;
            return;
        }

    //if we're moving right and there's an opening below and pacman is below, move down
    if ((direction == 1) && !collision(xpos, ypos, 3, level) && y>ypos)
        while (!collision(xpos, ypos, 3, level)){
            cout << "trying to move through hole below!" << endl;
            direction = 1;
            ypos+=3;
            return;
        }
   
   
    if (direction == 1)//right
        while (!collision(xpos, ypos, 1, level)){
            xpos+=3;
            return;
        }


		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    //////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
    //if we're moving up and there's an opening left and pacman is left, move left
    if ((direction == 3) && !collision(xpos, ypos, 2, level) && x<xpos)
        while (!collision(xpos, ypos, 2, level)){
            cout << "trying to move through hole to left!" << endl;
            direction = 4;
            xpos-=3;
            return;
        }
    //if we're moving up and there's an opening right and pacman is right, move right
    if ((direction == 3) && !collision(xpos, ypos, 1, level) && x>xpos)
        while (!collision(xpos, ypos, 1, level)){
            cout << "trying to move through hole to right!" << endl;
            direction = 2;
            xpos+=3;
            return;
        }

    if (direction == 3)//down
        while (!collision(xpos, ypos, 3, level)){
            ypos+=3;
            return;
        }



		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    ///////////////////////////////////////////////////////////////////////////////////////
    //if pacman is above and there's no wall there, move up
    if ((y<ypos) && !collision(xpos, ypos, 4, level)){
        cout << "direction is up" << endl;
        direction = 3;
        return;
    }


    //if pacman is below and there's no wall there, move down
    if ((y>ypos) && !collision(xpos, ypos, 3, level)){
        direction = 3;
        cout << "direction is down" << endl;
        return;
    }

    //if pacman is right and there's no wall there, move right
    if ((x>xpos) && !collision(xpos, ypos, 1, level)){
        direction = 1;
        cout << "direction is right" << endl;
        return;
    }

    //if pacman is left and there's no wall there, move left
    if ((x<xpos) && !collision(xpos, ypos, 2, level)){
        direction = 2;
        cout << "direction is left" << endl;
        return;

    }

    //if pacman is above and there's no wall there, move up
    if (!collision(xpos, ypos, 4, level)){
        cout << "direction is up" << endl;
        direction = 4;
        return;
    }


    //if pacman is below and there's no wall there, move down
    if (!collision(xpos, ypos, 3, level)){
        direction = 3;
        cout << "direction is down" << endl;
        return;
    }

    //if pacman is right and there's no wall there, move right
    if (!collision(xpos, ypos, 1, level)){
        direction = 1;
        cout << "direction is right" << endl;
        return;
    }

    //if pacman is left and there's no wall there, move left
    if (!collision(xpos, ypos, 2, level)){
        direction = 2;
        cout << "direction is left" << endl;
        return;

    }

}

void ghost::chase4(int x, int y, int level[20][20]){

	
    /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/


    //this is just for testing
    cout << "state is " << direction << endl;
    if (collision(xpos, ypos, 2, level))
        cout << "there's a wall to the left of me" << endl;
    if (collision(xpos, ypos, 4, level))
        cout << "there's a wall above me" << endl;
    if (collision(xpos, ypos, 1, level))
        cout << "there's a wall to the right of me" << endl;
    if (collision(xpos, ypos, 3, level))
        cout << "there's a wall below me" << endl;

    /////////////////////////////////LEFT STATE (1)//////////////////////////////////////////////////////////////////


	  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/



    //if we're moving left and there's an opening above and pacman is above, move up
    if ((direction == 2) && !collision(xpos, ypos, 4, level) && y<ypos)
        while (!collision(xpos, ypos, 4, level)){
            cout << "trying to move through hole above!" << endl;
            direction = 4;
            ypos-=4;
            return;
        }

    //if we're moving left and there's an opening below and pacman is below, move down
    if ((direction == 2) && !collision(xpos, ypos, 3, level) && y>ypos)
        while (!collision(xpos, ypos, 3, level)){
            cout << "trying to move through hole below!" << endl;
            direction = 3;
            ypos+=3;
            return;
        }


    if (direction == 2)//left
        while (!collision(xpos, ypos, 2, level)){
            xpos-=4;
            return;
        }


		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    ////////////////////////////////UP STATE (2)///////////////////////////////////////////////////////////////

    //if we're moving up and there's an opening left and pacman is left, move left
    if ((direction == 4) && !collision(xpos, ypos, 2, level) && x<xpos)
        while (!collision(xpos, ypos, 2, level)){
            cout << "trying to move through hole to left!" << endl;
            direction = 2;
            xpos-=3;
            return;
        }
    //if we're moving up and there's an opening right and pacman is right, move right
    if ((direction == 4) && !collision(xpos, ypos, 1, level) && x>xpos)
        while (!collision(xpos, ypos, 1, level)){
            cout << "trying to move through hole to right!" << endl;
            direction = 1;
            xpos+=3;
            return;
        }
    if (direction == 4)//up
        while (!collision(xpos, ypos, 4, level)){
            ypos-=3;
            return;
        }


		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    /////////RIGHT CASE (3)/////////////////////////////////////////////////////////////////////////////////////////////////////
    //if we're moving right and there's an opening above and pacman is above, move up
    if ((direction == 1) && !collision(xpos, ypos, 4, level) && y<ypos)
        while (!collision(xpos, ypos, 4, level)){
            cout << "trying to move through hole above!" << endl;
            direction = 4;
            ypos-=3;
            return;
        }

    //if we're moving right and there's an opening below and pacman is below, move down
    if ((direction == 1) && !collision(xpos, ypos, 3, level) && y>ypos)
        while (!collision(xpos, ypos, 3, level)){
            cout << "trying to move through hole below!" << endl;
            direction = 3;
            ypos+=3;
            return;
        }
   
   
    if (direction == 1)//right
        while (!collision(xpos, ypos, 1, level)){
            xpos+=3;
            return;
        }


		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    //////////////DOWN CASE (4)/////////////////////////////////////////////////////////////////////////////////////
    //if we're moving up and there's an opening left and pacman is left, move left
    if ((direction == 3) && !collision(xpos, ypos, 2, level) && x<xpos)
        while (!collision(xpos, ypos, 2, level)){
            cout << "trying to move through hole to left!" << endl;
            direction = 2;
            xpos-=3;
            return;
        }
    //if we're moving up and there's an opening right and pacman is right, move right
    if ((direction == 3) && !collision(xpos, ypos, 1, level) && x>xpos)
        while (!collision(xpos, ypos, 1, level)){
            cout << "trying to move through hole to right!" << endl;
            direction = 1;
            xpos+=3;
            return;
        }

    if (direction == 3)//down
        while (!collision(xpos, ypos, 3, level)){
            ypos+=3;
            return;
        }



		  /* Directions
    1 = left  2
    2 = up    4
    3 = right  1
    4 = down  3*/

    ///////////////////////////////////////////////////////////////////////////////////////
    //if pacman is above and there's no wall there, move up
    if ((y<ypos) && !collision(xpos, ypos, 4, level)){
        cout << "direction is up" << endl;
        direction = 4;
        return;
    }


    //if pacman is below and there's no wall there, move down
    if ((y>ypos) && !collision(xpos, ypos, 3, level)){
        direction = 3;
        cout << "direction is down" << endl;
        return;
    }

    //if pacman is right and there's no wall there, move right
    if ((x>xpos) && !collision(xpos, ypos, 1, level)){
        direction = 1;
        cout << "direction is right" << endl;
        return;
    }

    //if pacman is left and there's no wall there, move left
    if ((x<xpos) && !collision(xpos, ypos, 2, level)){
        direction = 2;
        cout << "direction is left" << endl;
        return;

    }

    //if pacman is above and there's no wall there, move up
    if (!collision(xpos, ypos, 4, level)){
        cout << "direction is up" << endl;
        direction = 4;
        return;
    }


    //if pacman is below and there's no wall there, move down
    if (!collision(xpos, ypos, 3, level)){
        direction = 3;
        cout << "direction is down" << endl;
        return;
    }

    //if pacman is right and there's no wall there, move right
    if (!collision(xpos, ypos, 1, level)){
        direction = 1;
        cout << "direction is right" << endl;
        return;
    }

    //if pacman is left and there's no wall there, move left
    if (!collision(xpos, ypos, 2, level)){
        direction = 2;
        cout << "direction is left" << endl;
        return;

    }

}
