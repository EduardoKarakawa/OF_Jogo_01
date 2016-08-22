#include "ofApp.h"
#include <iostream>
#include <time.h>


int ShootFree(Shoot *shoot_temp) {
	int i = 0;
	while ((i < 10) && shoot_temp[i].vivo) {
		i++;
	}
	return i;
}

void StartShoot(Shoot *shoot_temp, Player *p1_temp, int pos) {
	shoot_temp[pos].posX = p1_temp->posX - 2.5f;
	shoot_temp[pos].posY = p1_temp->posY - 35;
	shoot_temp[pos].speed = SPEED_SHOOT;
	shoot_temp[pos].vivo = true;
}

void MovShoot(Shoot *shoot_temp) {
	for (int i = 0; i < 10; i++) {
		if (shoot_temp[i].vivo) {
			if (shoot_temp[i].velY < VEL_SHOOT) {
				shoot_temp[i].velY += shoot_temp[i].speed;
			}

			shoot_temp[i].posY -= shoot_temp[i].velY;

			if (shoot_temp[i].posY < 0) {
				shoot_temp[i].velY = 0;
				shoot_temp[i].vivo = false;
			}
		}
	}
}

int SeeTotalEnemyLive(Player *enemy_temp) {
	int cont = 0;
	int i = 0, f = 4;
	while (i <= f){
		if ((enemy_temp + i)->vivo || (enemy_temp + i)->vivo) {
			cont++;
		}
		i++;
		f--;
	}
	return cont;
}

void SpawEnemy(Player *enemy_temp) {
	for (int i = 0; i < 5; i++) {
		(enemy_temp + i)->posX = 30 + rand() % 934;
		(enemy_temp + i)->posY = - rand() % 90;
		(enemy_temp + i)->prox_posX = 30 + rand() % 934;
		(enemy_temp + i)->speed = 0.01f;
		(enemy_temp + i)->vivo = true;
		(enemy_temp + i)->r = rand() % 255;
		(enemy_temp + i)->g = rand() % 255;
		(enemy_temp + i)->b = rand() % 255;
	}
}

void MovEnemy(Player *enemy_t) {
	if (enemy_t->velX < 3) {
		enemy_t->velX += enemy_t->speed;
	}

	if (enemy_t->velY < 0.7) {
		enemy_t->velY += enemy_t->speed;
	}

	if (enemy_t->posX > enemy_t->prox_posX) {
		enemy_t->posX -= enemy_t->velX;
		if (enemy_t->posX <= enemy_t->prox_posX)
			enemy_t->prox_posX = 30 + rand() % 934;
	}

	if (enemy_t->posX < enemy_t->prox_posX) {
		enemy_t->posX += enemy_t->velX;
		if (enemy_t->posX >= enemy_t->prox_posX)
			enemy_t->prox_posX = 30 + rand() % 934;
	}

	if (enemy_t->posY > 780) {
		enemy_t->vivo = false;
	}
	
	enemy_t->posY += enemy_t->velY;
}

void ControlEnemy(Player *enemy_temp) {
	if (SeeTotalEnemyLive(enemy_temp) == 0) {
		SpawEnemy(enemy_temp);
	}

	else {
		for (int i = 0; i < 5; i++) {
			if ((enemy_temp + i)->vivo) {
				MovEnemy(&enemy_temp[i]);
			}
		}
	}
}

void Atrito(Player *p) {
	if (p->velX > 0) {
		p->velX -= p->atrito;
		if (p->velX < 0)
			p->velX = 0;
	}
	if (p->velX < 0) {
		p->velX += p->atrito;
		if (p->velX > 0)
			p->velX = 0;
	}
	if (p->velY > 0) {
		p->velY -= p->atrito;
		if (p->velY < 0)
			p->velY = 0;
	}
	if (p->velY < 0) {
		p->velY += p->atrito;
		if (p->velY > 0)
			p->velY = 0;
	}
}

void VerSeApertou(InputPlayer *key_temp, Player *p_temp) {
	if (key_temp->right && p_temp->velX < VEL)
		p_temp->velX = p_temp->velX + p_temp->speed;

	if (key_temp->left && p_temp->velX > -VEL)
		p_temp->velX = p_temp->velX - p_temp->speed;

	if (key_temp->up && p_temp->velY > -VEL)
		p_temp->velY = p_temp->velY - p_temp->speed;

	if (key_temp->down && p_temp->velY < VEL)
		p_temp->velY = p_temp->velY + p_temp->speed;
}

void ControlPlayer(Player *p_temp, InputPlayer *key_temp) {
	//atualiza movimentação
	p_temp->posX += p_temp->velX;
	p_temp->posY += p_temp->velY;


	//regras de atrito
	if (!key_temp->down && !key_temp->left && !key_temp->right && !key_temp->up) {
		Atrito(p_temp);
	}

	//verifica se ta apertado
	VerSeApertou(key_temp, p_temp);


}

void ColisionEnemyToShoot(Player *enemy_temp, Shoot *shoot_temp) {
	for (int i = 0; i < 10; i++) {
		if ((shoot_temp + i)->vivo) {
			for (int j = 0; j < 5; j++) {
				if (((shoot_temp + i)->posX >= (enemy_temp + j)->posX - 20) && ((shoot_temp + i)->posX <= (enemy_temp + j)->posX + 20)) {
					if (((shoot_temp + i)->posY - 10 >= (enemy_temp + j)->posY - 12) && ((shoot_temp + i)->posY - 10 <= (enemy_temp + j)->posY + 12)) {
						(enemy_temp + j)->vivo = false;
						(shoot_temp + i)->vivo = false;
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::setup() {
	srand(time(NULL));

//estado do jogo
	game_state = "game";

//inicia a posição do player
	p1.posX = 400;
	p1.posY = 400;
	p1.vivo = true;

}

//--------------------------------------------------------------
void ofApp::update() { // executa a 60fps

//contagem de fps
	if (fps < 120)
		fps++;
	else {
		fps = 0;
	}

	

//Controlar o player
	ControlPlayer(&p1, &inp_key);



//Controla inimigo
	ControlEnemy(enemy);


	
//reflete ao atintegir limite de tela
	if ((p1.posX <= (p1.radius)) || (p1.posX >= (1024 - p1.radius)))
		p1.velX = -p1.velX;

	if ((p1.posY <= p1.radius) || (p1.posY >= (768 - p1.radius)))
		p1.velY = -p1.velY;


		
//time para tiro
	if(p1.time <= 20)
		p1.time++;



//Verifica se tem algum tiro na tela e movimenta ele
	if (inp_key.space && (p1.time >= 20)){
		p1.time = 0;
		StartShoot(shoot, &p1, ShootFree(shoot));
	}
	MovShoot(shoot);

//Colisao de tiro com inimigo
	ColisionEnemyToShoot(enemy, shoot);


	
	
		

}


//--------------------------------------------------------------
void ofApp::draw() {
//Cor de fundo
	ofBackground(6, 8, 26);
	

//Imprime os tiros
	for (int i = 0; i < 10; i++) {
		if (shoot[i].vivo) {
			ofSetColor(225, 168, 00);
			ofDrawRectangle(shoot[i].posX, shoot[i].posY, 5, 20);
		}
	}

//Imprime os inimigos
	for (int i = 0; i < 5; i++) {
		if (enemy[i].vivo) {
			ofSetColor(enemy[i].r, enemy[i].g, enemy[i].b);
			ofDrawRectangle(enemy[i].posX, enemy[i].posY, 40, 24);
		}
	}


//Imprime o personagem
	ofSetColor(140, 135, 130);
	ofDrawTriangle(p1.posX-15, p1.posY, p1.posX+15, p1.posY, p1.posX, p1.posY - 30);

	ofSetColor(10, 127, 250);
	ofDrawCircle(p1.posX, p1.posY, p1.radius);
	
	
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (game_state == "game") {

		if (key == OF_KEY_LEFT)
			inp_key.left = true;
		if (key == OF_KEY_RIGHT)
			inp_key.right = true;
		if (key == OF_KEY_UP)
			inp_key.up = true;
		if (key == OF_KEY_DOWN)
			inp_key.down = true;
		if (key == ' ')
			inp_key.space = true;
	}
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (game_state == "game") {
		if (key == OF_KEY_LEFT)
			inp_key.left = false;
		if (key == OF_KEY_RIGHT)
			inp_key.right = false;
		if (key == OF_KEY_UP)
			inp_key.up = false;
		if (key == OF_KEY_DOWN)
			inp_key.down = false;
		if (key == ' ')
			inp_key.space = false;
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
