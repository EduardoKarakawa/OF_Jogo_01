#include "ofApp.h"

string game_state;

struct Player {
	float posX, posY;
	float velX, velY;
	float radius = 15.0f;
	float speed = 0.01f;
	float atrito = 0.003f;

	bool key_up, key_down, key_left, key_right;
};

Player p1;

//--------------------------------------------------------------
void ofApp::setup() {
	//estado do jogo
	game_state = "game";

	//inicia a posição do player
	p1.posX = 400;
	p1.posY = 400;


	//velocidade do player
}

//--------------------------------------------------------------
void ofApp::update() { // executa a 60fps

					   //reflete ao atintegir limite de tela
	if ((p1.posX <= (p1.radius)) || (p1.posX >= (1024 - p1.radius)))
		p1.velX = -p1.velX;

	if ((p1.posY <= p1.radius) || (p1.posY >= (768 - p1.radius)))
		p1.velY = -p1.velY;


	//atualiza movimentação
	p1.posX += p1.velX;
	p1.posY += p1.velY;


	//verifica se ta apertado
	if (p1.key_right && p1.velX < 1)
		p1.velX = p1.velX + p1.speed;
	if (p1.key_left && p1.velX > -1)
		p1.velX = p1.velX - p1.speed;
	if (p1.key_up && p1.velY > -1)
		p1.velY = p1.velY - p1.speed;
	if (p1.key_down && p1.velY < 1)
		p1.velY = p1.velY + p1.speed;

	//atrito
	if (!p1.key_down && !p1.key_left && !p1.key_right && !p1.key_up) {
		if (p1.velX > 0) {
			p1.velX -= p1.atrito;
			if (p1.velX < 0)
				p1.velX = 0;
		}
		if (p1.velX < 0) {
			p1.velX += p1.atrito;
			if (p1.velX > 0)
				p1.velX = 0;
		}
		if (p1.velY > 0) {
			p1.velY -= p1.atrito;
			if (p1.velY < 0)
				p1.velY = 0;
		}
		if (p1.velY < 0) {
			p1.velY += p1.atrito;
			if (p1.velY > 0)
				p1.velY = 0;
		}
	}

	//parando o player
	/*if (!p1.key_right && !p1.key_left)
	p1.velX = 0;
	if (!p1.key_up && !p1.key_down)
	p1.velY = 0;*/
}

//--------------------------------------------------------------
void ofApp::draw() {
	ofDrawCircle(p1.posX, p1.posY, p1.radius);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (game_state == "game") {

		if (key == OF_KEY_LEFT)
			p1.key_left = true;
		if (key == OF_KEY_RIGHT)
			p1.key_right = true;
		if (key == OF_KEY_UP)
			p1.key_up = true;
		if (key == OF_KEY_DOWN)
			p1.key_down = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (game_state == "game") {
		if (key == OF_KEY_LEFT)
			p1.key_left = false;
		if (key == OF_KEY_RIGHT)
			p1.key_right = false;
		if (key == OF_KEY_UP)
			p1.key_up = false;
		if (key == OF_KEY_DOWN)
			p1.key_down = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
