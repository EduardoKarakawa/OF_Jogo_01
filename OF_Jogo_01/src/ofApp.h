#pragma once

#include "ofMain.h"

#define VEL 9
#define VEL_SHOOT 50
#define SPEED_SHOOT 1


struct Player {
	float posX, posY, prox_posX;
	float velX = 0, velY = 0;
	float radius = 15.0f;
	float speed = 0.5f;
	float atrito = 0.1f;
	int r, g, b;
	int time = 0;
	bool vivo;
};

struct Shoot {
	float posX, posY;
	float velY = 0;
	float speed = SPEED_SHOOT;
	bool vivo;
};

struct InputPlayer {
	bool up, down, left, right;
	bool space;
};


class ofApp : public ofBaseApp{

	string game_state;
	Player p1;
	Player enemy[5];
	Shoot shoot[10];
	InputPlayer inp_key;
	int fps = 0;

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
};
