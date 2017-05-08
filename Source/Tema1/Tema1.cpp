#include "Tema1.h"
#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"
#include "Player.h"

#include <iostream>
#include <stdlib.h>	//random

using namespace std;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}

void Tema1::Init()
{
	auto camera = GetSceneCamera();
	camera->SetPosition(glm::vec3(0, 0, 50));
	camera->SetRotation(glm::vec3(0, 0, 0));
	camera->Update();
	GetCameraInput()->SetActive(false);


	/* Setez inaltimea si latimea la resolutie */
	glm::vec2 gameResolution = window->GetResolution();
	logicSpace.x = 0;		// logic x
	logicSpace.y = 0;		// logic y
	logicSpace.width = gameResolution.x;	// logic width
	logicSpace.height = gameResolution.y;	// logic height


	// Create a new mesh from buffer data
	
	vector<unsigned short> indices =
	{
		0, 1, 2,
		0, 3, 4,
	};

	/* Vom crea obiectele din joc folosind functia CreateMesh din laboratorul 2 */
	vector<VertexFormat> verticesPlayer = setColorPlayer(glm::vec3((float)19 / 255, (float)145 / 255, (float)116 / 255));
	Mesh *meshP = CreateMesh("Player", verticesPlayer, indices);

	/* Tipuri de inamici */
	vector<VertexFormat> verticesEnemy1 = setColorPlayer(glm::vec3((float)51 / 255, (float)51 / 255, 1));
	Mesh *meshE1 = CreateMesh("Enemy1", verticesEnemy1, indices);

	vector<VertexFormat> verticesEnemy2 = setColorPlayer(glm::vec3((float)249 / 255, (float)244 / 255, (float)94 / 255));
	Mesh *meshE2 = CreateMesh("Enemy2", verticesEnemy2, indices);

	vector<VertexFormat> verticesEnemy3 = setColorPlayer(glm::vec3((float)209 / 255, (float)24 / 255, (float)24 / 255));
	Mesh *meshE3 = CreateMesh("Enemy3", verticesEnemy3, indices);
	
	/* Construim un dreptunghi (proiectile sau vieti) */
	vector<VertexFormat> verticesRectangle = setColorRectangle(glm::vec3(1, 1, 0));

	vector<unsigned short> indicesRectangle =
	{
		0, 1, 2,
		1, 3, 2,
	};

	Mesh *meshB = CreateMesh("Rectangle", verticesRectangle, indicesRectangle);

	/* Construim obiectele bonus*/	

	vector<VertexFormat> verticeslife
	{
		VertexFormat(glm::vec3(0, 0, 0), glm::vec3((float)180 / 255, 0, 0)),
		VertexFormat(glm::vec3(0.5f, 0.5f, 0), glm::vec3((float)180 / 255, 0, 0)),
		VertexFormat(glm::vec3(1, 0, 0), glm::vec3((float)180 / 255, 0, 0)),
		VertexFormat(glm::vec3(0, -2, 0), glm::vec3((float)180 / 255, 0, 0)),
		VertexFormat(glm::vec3(-1, 0, 0), glm::vec3((float)180 / 255, 0, 0)),
		VertexFormat(glm::vec3(-0.5f, 0.5f, 0), glm::vec3((float)180 / 255, 0, 0)),
	};

	vector<unsigned short> indiceslife =
	{
		0, 1, 2,
		2, 3, 4,
		4, 5, 0,
	};

	/* Bonus - viata */
	Mesh *meshH = CreateMesh("Life", verticeslife, indiceslife);


	vector<VertexFormat> verticesShield
	{
		VertexFormat(glm::vec3(1, 0, 0), glm::vec3(0, (float)153 / 255, 0)),
		VertexFormat(glm::vec3(0, 0.5f, 0), glm::vec3(0, (float)153 / 255, 0)),
		VertexFormat(glm::vec3(-1, 0, 0), glm::vec3(0, (float)153 / 255, 0)),
		VertexFormat(glm::vec3(0, -2, 0), glm::vec3(0, (float)153 / 255, 0)),
	};

	vector<unsigned short> indicesShield =
	{
		0, 1, 2,
		0, 2, 3,
	};
	
	/* Bonus - scut */
	Mesh *meshS = CreateMesh("Shield", verticesShield, indicesShield);

	/* Player cu scutul activat */
	vector<VertexFormat> verticesPlayerProtected = setColorPlayer(glm::vec3(0, (float)153 / 255, 0));
	Mesh *meshPS = CreateMesh("PlayerProtected", verticesPlayerProtected, indices);
	
	/* Initializari player */
	player.setPosition(glm::vec2(logicSpace.width / 2, logicSpace.height / 2));
	player.setScale(glm::vec2(20, 20));
	player.setRadius(20);
	player.speed = 350;
	player.lives = 3;

	/* Initializari boss */
	boss.setPosition(glm::vec2(logicSpace.width / 2, logicSpace.height - 80));
	boss.setScale(glm::vec2(80, 80));
	boss.setRadius(80);
	boss.speed = 150;
	boss.lives = 80;
	boss.type = 1;
	boss.time = 0.0f;
}

/* Setam culoarea pentru nava */
vector<VertexFormat> Tema1::setColorPlayer(glm::vec3 color) {
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0, 0, 0), color),
		VertexFormat(glm::vec3(-1, -1, 0), color),
		VertexFormat(glm::vec3(-1, 1, 0), color),
		VertexFormat(glm::vec3(1, 1, 0), color),
		VertexFormat(glm::vec3(1, -1, 0), color),

	};
	return vertices;
}

/* Setam culoarea pentru dreptunghi */
vector<VertexFormat> Tema1::setColorRectangle(glm::vec3 color) {
	vector<VertexFormat> vertices
	{
		VertexFormat(glm::vec3(0.5f, 4, 0), color),
		VertexFormat(glm::vec3(0.5f, 0, 0), color),
		VertexFormat(glm::vec3(-0.5f, 4, 0), color),
		VertexFormat(glm::vec3(-0.5f, 0, 0), color),
	};
	return vertices;
};

/* Create mesh - Lab2 */
Mesh* Tema1::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO_ID = 0;
	// Create the VAO and bind it
	glGenVertexArrays(1, &VAO_ID);
	glBindVertexArray(VAO_ID);

	// Create the VBO and bind it
	unsigned int VBO_ID;
	glGenBuffers(1, &VBO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);

	// Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	// Crete the IBO and bind it
	unsigned int IBO_ID;
	glGenBuffers(1, &IBO_ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO_ID);

	// Send indices data into the IBO buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// ========================================================================
	// This is section is strongly linked to how the GPU Shader program treats data
	// It will be learned later, when GLSL shaders will introduces
	// For the moment just think that each property value from our vertex format needs to be send to a certain channel
	// in order to know how to receive it in the GLSL vertex shader

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO_ID, static_cast<unsigned short>(indices.size()));
	return meshes[name];
}

// 2D visualization matrix
glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
	float sx, sy, tx, ty;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	tx = viewSpace.x - sx * logicSpace.x;
	ty = viewSpace.y - sy * logicSpace.y;

	return glm::transpose(glm::mat3(
		sx, 0.0f, tx,
		0.0f, sy, ty,
		0.0f, 0.0f, 1.0f));
}

// uniform 2D visualization matrix (same scale factor on x and y axes)
glm::mat3 Tema1::VisualizationTransf2DUnif(const LogicSpace & logicSpace, const ViewportSpace & viewSpace)
{
	float sx, sy, tx, ty, smin;
	sx = viewSpace.width / logicSpace.width;
	sy = viewSpace.height / logicSpace.height;
	if (sx < sy)
		smin = sx;
	else
		smin = sy;
	tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
	ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

	return glm::transpose(glm::mat3(
		smin, 0.0f, tx,
		0.0f, smin, ty,
		0.0f, 0.0f, 1.0f));
}

void Tema1::SetViewportArea(const ViewportSpace & viewSpace, glm::vec3 colorColor, bool clear)
{
	glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	glEnable(GL_SCISSOR_TEST);
	glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

	// Clears the color buffer (using the previously set color) and depth buffer
	glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glDisable(GL_SCISSOR_TEST);

	GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
	GetSceneCamera()->Update();
}

void Tema1::FrameStart()
{
	// Clears the color buffer (using the previously set color) and depth buffer

	glClearColor(0, 0, 0, 1);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
}

void Tema1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->GetResolution();
	
	// Sets the screen area where to draw - the left half of the window
	viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);

	glm::vec3 color;

	if (gameOver == true) {
		if (resultGame == false) {
			if (player.lives == 0) {
				cout << "Final Score: " << score << "\nGAME OVER!\n";
			}
			else {
				cout << "Final Score: " << score << "\nYOU WON!\n";
			}
			resultGame = true;
		}
		/* Calculam timpul pentru animatie culoare ecran */
		timeBackground += deltaTimeSeconds;
		if (timeBackground > 2.0f) {
			timeBackground = 2.0f;
		}

		/* red = f(time) */
		float red = (float)(255 / 2.0f) * timeBackground;
		red = (float)red / 255;

		color = glm::vec3(red, 0, 0);
		SetViewportArea(viewSpace, color, true);
	}
	else {
		SetViewportArea(viewSpace, glm::vec3(0), true);
	}

	
	// Compute the 2D visualization matrix
	visMatrix = glm::mat3(1);
	visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);

	/* Blocare joc daca s-a terminat sau e pauza */
	if (gameOver == true || pause == true) {
		DrawFinalScene(visMatrix);
	}
	else {
		DrawScene(visMatrix, deltaTimeSeconds);
	}	
}

void Tema1::FrameEnd()
{

}

void Tema1::DrawFinalScene(glm::mat3 visMatrix) {

	/* -------- Afisare vieti player -------- */
	glm::vec2 coord = glm::vec2(logicSpace.width, logicSpace.height - 55);
	for (int i = 0; i < player.lives; i++) {
		modelMatrix = visMatrix * Transform2D::Translate(coord.x - 12 * (i + 1), coord.y);
		modelMatrix *= Transform2D::Scale(5, 10);
		RenderMesh2D(meshes["Rectangle"], shaders["VertexColor"], modelMatrix);
	}


	/* -------- Afisare player -------- */
	modelMatrix = visMatrix * Transform2D::Translate(player.position.x, player.position.y);
	modelMatrix *= Transform2D::Scale(player.scale.x, player.scale.y);
	modelMatrix *= Transform2D::Rotate(player.angle);
	RenderMesh2D(meshes["Player"], shaders["VertexColor"], modelMatrix);


	/* -------- Afisare vector de proiectile -------- */
	for (unsigned i = 0; i < player.Bullets.size(); i++) {
		modelMatrix = visMatrix * Transform2D::Translate(player.Bullets[i].position.x, player.Bullets[i].position.y);
		modelMatrix *= Transform2D::Scale(player.Bullets[i].scale.x, player.Bullets[i].scale.y);
		modelMatrix *= Transform2D::Rotate(player.Bullets[i].angle);
		RenderMesh2D(meshes["Rectangle"], shaders["VertexColor"], modelMatrix);
	}


	/* -------- Afisare enemies -------- */
	for (unsigned i = 0; i < Enemies.size(); i++) {
		modelMatrix = visMatrix * Transform2D::Translate(Enemies[i].position.x, Enemies[i].position.y);

		if (Enemies[i].type == 3) {
			// afisam obiectul scalat (se va scala pana la jumatate si va ramane acolo)
			modelMatrix *= Transform2D::Scale(Enemies[i].relativeScale.x, Enemies[i].relativeScale.y);
		}
		else {
			modelMatrix *= Transform2D::Scale(Enemies[i].scale.x, Enemies[i].scale.y);
		}
		modelMatrix *= Transform2D::Rotate(Enemies[i].angle);

		/* Desenam tipul de enemy dorit */
		typeEnemy = "Enemy" + to_string(Enemies[i].type);
		RenderMesh2D(meshes[typeEnemy], shaders["VertexColor"], modelMatrix);
	}


	/* -------- Afisare BONUS -------- */
	if (bonus.active == true) {
		modelMatrix = visMatrix * Transform2D::Translate(bonus.position.x, bonus.position.y);
		modelMatrix *= Transform2D::Scale(bonus.scale.x, bonus.scale.y);

		if (bonus.life == true) {
			RenderMesh2D(meshes["Life"], shaders["VertexColor"], modelMatrix);
		}
		else if (bonus.shield == true) {
			RenderMesh2D(meshes["Shield"], shaders["VertexColor"], modelMatrix);
		}
	}


	/* -------- Afisare boss --------*/
	if (bossIsHere == true) {
		if (boss.lives > 0) {
			/* Afisam bossul daca nu a fost invins */
			modelMatrix = visMatrix * Transform2D::Translate(boss.position.x, boss.position.y);
			modelMatrix *= Transform2D::Scale(boss.scale.y, boss.scale.y);
			modelMatrix *= Transform2D::Rotate(boss.angle);

			if (boss.shield == false) {
				typeEnemy = "Enemy" + to_string(boss.type);
				RenderMesh2D(meshes[typeEnemy], shaders["VertexColor"], modelMatrix);
			}
			else {
				RenderMesh2D(meshes["PlayerProtected"], shaders["VertexColor"], modelMatrix);
			}
		}
		/* Afisam proiectilele lansate de boss */
		for (unsigned i = 0; i < boss.Bullets.size(); i++) {
			modelMatrix = visMatrix * Transform2D::Translate(boss.Bullets[i].position.x, boss.Bullets[i].position.y);
			modelMatrix *= Transform2D::Scale(boss.Bullets[i].scale.x, boss.Bullets[i].scale.y);
			modelMatrix *= Transform2D::Rotate(boss.Bullets[i].angle);
			RenderMesh2D(meshes["Rectangle"], shaders["VertexColor"], modelMatrix);
		}
	}
}

void Tema1::DrawScene(glm::mat3 visMatrix, float deltaTimeSeconds)
{
	/* -------- Afisare vieti player -------- */
	glm::vec2 coord = glm::vec2(logicSpace.width, logicSpace.height - 55);
	for (int i = 0; i < player.lives; i++) {
		modelMatrix = visMatrix * Transform2D::Translate(coord.x - 12 * (i+1), coord.y);
		modelMatrix *= Transform2D::Scale(5, 10);
		RenderMesh2D(meshes["Rectangle"], shaders["VertexColor"], modelMatrix);
	}


	/* -------- Afisare player -------- */
	modelMatrix = visMatrix * Transform2D::Translate(player.position.x, player.position.y);
	modelMatrix *= Transform2D::Scale(player.scale.x, player.scale.y);
	modelMatrix *= Transform2D::Rotate(player.angle);
	if (player.shield == false) {
		RenderMesh2D(meshes["Player"], shaders["VertexColor"], modelMatrix);
	}
	else {
		RenderMesh2D(meshes["PlayerProtected"], shaders["VertexColor"], modelMatrix);
	}


	/* ----------------   INTERACTIUNI   ---------------- */

	// 1. Proiectile <-> inamic
	/* Verificam daca un glont s-a intersectat cu o nava inamica si stergem nava daca da */
	bool isDeleted = false;
	for (unsigned i = 0; i < Enemies.size(); i++) {
		isDeleted = false;

		for (unsigned j = 0; j < player.Bullets.size(); j++) {
			if (Enemies[i].interact(player.Bullets[j]) == 1) {
				player.Bullets.erase(player.Bullets.begin() + j);
				
				/* Daca e de tipul 2 (are 2 vieti) se va micsora */
				if (Enemies[i].type == 2) {
					Enemies[i].type = 3;
					Enemies[i].minimizing = true;
					Enemies[i].speed = 2 * Enemies[i].speed;
				}
				else {
					Enemies.erase(Enemies.begin() + i);
					isDeleted = true;
					score++;
					cout << "You just have killed an enemy! Score: " << score << "\n";
					if (score == 50) {		// Boss-ul va aparea la score 50
						bossIsHere = true;
						enemy.minimizing = false; // pt a micsora boss-ul
					}
					break;
				}	
			}
		} //endfor player.bullets

		/* Animatie pentru micsorarea navetei */
		if (isDeleted == false && Enemies[i].type == 3 && Enemies[i].minimizing == true) {
			Enemies[i].setNewScale(deltaTimeSeconds);
		}
	}

	
	// 2. Player <-> inamic
	for (unsigned i = 0; i < Enemies.size(); i++) {
		if (player.shield == false && Enemies[i].interact(player) == 1) {
			player.lives--;
			if (player.lives == 0) {
				// Colorez ecranul
				gameOver = true;
			}
			Enemies.erase(Enemies.begin() + i);
		}
	}


	/* -------- Afisare proiectile -------- */
	for (unsigned i = 0; i < player.Bullets.size(); i++){
		modelMatrix = visMatrix * Transform2D::Translate(player.Bullets[i].position.x, player.Bullets[i].position.y);
		modelMatrix *= Transform2D::Scale(player.Bullets[i].scale.x, player.Bullets[i].scale.y);
		modelMatrix *= Transform2D::Rotate(player.Bullets[i].angle);
		RenderMesh2D(meshes["Rectangle"], shaders["VertexColor"], modelMatrix);

		/* Continuam deplasarea proiectilului */
		player.Bullets[i].position += player.Bullets[i].velocity;

		/* Daca a iesit din ecran il stergem din vector */
		if (player.Bullets[i].position.x > logicSpace.width + 10 ||
			player.Bullets[i].position.x < -10 || 
			player.Bullets[i].position.y > logicSpace.height + 10 ||
			player.Bullets[i].position.y < -10) {

			player.Bullets.erase(player.Bullets.begin() + i);
		}
	}


	/* -------- Afisare inamici -------- */
	for (unsigned i = 0; i < Enemies.size(); i++) {
		/* Calculam vectorul viteza pentru pozitia curenta a playerului */
		Enemies[i].setVelocityVector(player.position);

		/* Calculam unchiul de rotatie al inamicului fata de naveta player */
		Enemies[i].setAngle(player.position);

		modelMatrix = visMatrix * Transform2D::Translate(Enemies[i].position.x, Enemies[i].position.y);

		if (Enemies[i].type == 3) {
			modelMatrix *= Transform2D::Scale(Enemies[i].relativeScale.x, Enemies[i].relativeScale.y);
		}
		else {
			modelMatrix *= Transform2D::Scale(Enemies[i].scale.x, Enemies[i].scale.y);
		}
		
		modelMatrix *= Transform2D::Rotate(Enemies[i].angle);
		/* Tipul inamicului */
		typeEnemy = "Enemy" + to_string(Enemies[i].type);
		RenderMesh2D(meshes[typeEnemy], shaders["VertexColor"], modelMatrix);
		
		/* Noua pozitie a inamicului va fi mai aproape de player */
		Enemies[i].position += Enemies[i].velocity;
	}
	
	
	/* -------- Afisare BONUS -------- */
	if (player.interact(bonus) == 1) {
		// viata in plus
		if (bonus.life == true) {
			player.lives++;
			bonus.life = false;
		}
		// scut
		else if (bonus.shield == true) {
			bonus.shield = false;
			player.shield = true;
			player.time = 0.0f;
		}
		bonus.active = false;
		bonus.time = 0.0f;
	}

	/* Daca player a primit scut, devine invincibil 10 sec */
	if (player.shield == true) {
		if (player.time < 10.001f) {
			player.time += deltaTimeSeconds;
		}
		else {
			player.shield = false;
		}
	}
	// Afisam bonusul timp de 10 sec pe ecran 
	if (bonus.active == true) {
		if (bonus.time < 10.001f) {
			bonus.time += deltaTimeSeconds;
			modelMatrix = visMatrix * Transform2D::Translate(bonus.position.x, bonus.position.y);
			modelMatrix *= Transform2D::Scale(bonus.scale.x, bonus.scale.y);

			if (bonus.life == true) {
				RenderMesh2D(meshes["Life"], shaders["VertexColor"], modelMatrix);
			}
			else if (bonus.shield == true) {
				RenderMesh2D(meshes["Shield"], shaders["VertexColor"], modelMatrix);
			}
		}
		else {
			bonus.time = 0.0f;
			bonus.life = false;
			bonus.shield = false;
			bonus.active = false;
		}
	}


	/* -------- Afisare BOSS -------- */
	if (bossIsHere == true) {

		/* Interactiune boss <-> proiectilele navei player */
		for (unsigned i = 0; i < player.Bullets.size(); i++) {
			if (boss.interact(player.Bullets[i]) == 1) {
				player.Bullets.erase(player.Bullets.begin() + i);

				// daca nu are scutul activat va pierde din viata 
				if (boss.shield == false) {
					boss.lives--;
					score++;
					cout << "You just have attacked the BOSS! Scoare: " << score << '\n';
					if (boss.lives == 0) {
						gameOver = true;
						break;
					}

					// Bossul are 80 de vieti. La 40 se micsoreaza la jumatate,
					// iar la 20 inca o data la jumatate printr-o animatie 
					if (boss.lives == 40 || boss.lives == 20) {
						boss.type++;
						
						// vom creste viteza si frecventa de tragere
						boss.speed += boss.speed / 2;
						boss.shoot -= 0.2f;

						// folosim un enemy pentru a calcula scalarea lui boss
						enemy.time = 0.0f;
						enemy.minimizing = true;
					}
				}
			}
		}


		/* Scalarea lui boss. Folosim un enemy ca masca pentru a face micsorarea. 
		(vom retine in scale.x scala initiala, iar in scale.y noua scala) */
			
		if (enemy.minimizing == true && (boss.type == 2 || boss.type == 3)) {
			enemy.setScale(glm::vec2(boss.scale.x, boss.scale.y));
			enemy.setNewScale(deltaTimeSeconds);
			/* salvam noua scala -> animatie scalare  */
			boss.scale.y = enemy.relativeScale.x;

			/* Daca s-a scalat la jumatate, vom seta scalarea drept scalare definitiva */
			if (enemy.minimizing == false && boss.type == 2) {
				boss.scale.x = boss.scale.y;
			}
			//setam si noua raza
			boss.setRadius(enemy.radius);
		}
				

		/* Abilitate boss - 35s fara scut, 10s cu scut */		
		if (boss.shield == false) {
			if (boss.timeShield < 35.001f) {
				boss.timeShield += deltaTimeSeconds;
			}
			else {
				boss.timeShield = 0.0f;
				boss.shield = true;
			}
		}
		else {
			if (boss.timeShield < 10.001f) {
				boss.timeShield += deltaTimeSeconds;
			}
			else {
				boss.timeShield = 0.0f;
				boss.shield = false;
			}
		}


		/* -------- Interactiune boss <-> player -------- */
		if (player.shield == false && boss.shield == false && boss.interact(player) == 1) {
			player.lives--;
			boss.lives--;

			//setez  noua pozitie pt player in josul ecranului 
			player.setPosition(glm::vec2(logicSpace.width / 2, logicSpace.height / 8));
			
			if (player.lives == 0 || boss.lives == 0) {
				gameOver = true;
			}
		}
		

		/* ------- Interactiune player <-> proiectilele bossului -------- */
		for (unsigned i = 0; i < boss.Bullets.size(); i++) {
			if (player.interact(boss.Bullets[i]) == 1) {
				boss.Bullets.erase(boss.Bullets.begin() + i);

				//player nu are scutul activat 
				if (player.shield == false) {
					player.lives--;

					if (player.lives == 0) {
						gameOver = true;
						break;
					}
				}
			}
		}


		/* --------- Desenem inamicul boss --------- */

		boss.setAngle(player.position);
		modelMatrix = visMatrix * Transform2D::Translate(boss.position.x, boss.position.y);

		// Vom folosi doar scalarea relativa, in scale.x retinem scalarea de la care am plecat	
		modelMatrix *= Transform2D::Scale(boss.scale.y, boss.scale.y);
		
		modelMatrix *= Transform2D::Rotate(boss.angle);

		if (boss.shield == false) {
			typeEnemy = "Enemy" + to_string(boss.type);
			RenderMesh2D(meshes[typeEnemy], shaders["VertexColor"], modelMatrix);
		}
		else {
			RenderMesh2D(meshes["PlayerProtected"], shaders["VertexColor"], modelMatrix);
		}

		
		/* --------- Desenem proiectilele inamicului boss --------- */
		for (unsigned i = 0; i < boss.Bullets.size(); i++) {
			modelMatrix = visMatrix * Transform2D::Translate(boss.Bullets[i].position.x, boss.Bullets[i].position.y);
			modelMatrix *= Transform2D::Scale(boss.Bullets[i].scale.x, boss.Bullets[i].scale.y);
			modelMatrix *= Transform2D::Rotate(boss.Bullets[i].angle);
			RenderMesh2D(meshes["Rectangle"], shaders["VertexColor"], modelMatrix);

			/* Continuam deplasarea proiectilului */
			boss.Bullets[i].position += boss.Bullets[i].velocity;

			/* Daca a iesit din ecran il stergem din vector */
			if (boss.Bullets[i].position.x > logicSpace.width + 10 ||
				boss.Bullets[i].position.x < -10 ||
				boss.Bullets[i].position.y > logicSpace.height + 10 ||
				boss.Bullets[i].position.y < -10) {

				boss.Bullets.erase(boss.Bullets.begin() + i);				
			}
		}
	}
	

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{
	/* Daca jocul nu s-a intrerupt, putem sa modifcam obiectele */
	if (gameOver == false && pause == false) {

		/* Mutam playerul pe ecran in functe de butoanele W,A,S,D */
		if (window->KeyHold(GLFW_KEY_W)) {
			player.position.y += deltaTime * player.speed;
			if (player.position.y > logicSpace.height) {
				player.position.y = logicSpace.height;
			}
		}
		if (window->KeyHold(GLFW_KEY_S)) {
			player.position.y -= deltaTime * player.speed;
			if (player.position.y < 0) {
				player.position.y = 0;
			}
		}
		if (window->KeyHold(GLFW_KEY_D)) {
			player.position.x += deltaTime *  player.speed;
			if (player.position.x > logicSpace.width) {
				player.position.x = logicSpace.width;
			}
		}
		if (window->KeyHold(GLFW_KEY_A)) {
			player.position.x -= deltaTime *  player.speed;
			if (player.position.x < 0) {
				player.position.x = 0;
			}
		}


		/* Calculez unghiul de rotatie al navei fata de mouse */
		glm::vec2 mouse = window->GetCursorPosition();
		player.setAngle(glm::vec2(mouse.x, logicSpace.height - mouse.y));
		
		if (deltaTime < 0.5f)

			/* ------------ Crearea INAMICI ------------ */
			if (counter >= timeForEnemy && bossIsHere == false) {
				//micsorarea timpului de la 2s la 0.5s cu o constanta 0.03
				if (timeForEnemy > 0.5f) {
					timeForEnemy -= 0.03;
					if (timeForEnemy <= 0.5f) {
						timeForEnemy = 0.5f;
					}
				}
				counter = 0.0f;

				// Setam prop inamicului  si il adaugam in vectorul de inamici 
				enemy.settingProperties(logicSpace.height);
				Enemies.push_back(enemy);
			}
			else {
				// creste pana la timeForEnemy, astfel se va crea 
				// un nou inamic dupa timeForEnemy secunde
				counter += deltaTime;
			}


			/* ------- Creare BONUS ------- */
			if (bonus.active == false){
				//dupa 30s apare un nou bonus 
				if (deltaTime < 0.5f && bonus.time > 30.001f) {

					bonus.time = 0.0f;
					bonus.active = true;
					
					// calculam care dintre cele 2 bonusuri va fi
					int whatBonus = rand() % 2;
					if (whatBonus == 0) {
						bonus.life = true;
						bonus.shield = false;
					}
					else {
						bonus.life = false;
						bonus.shield = true;
					}

					// setam pozitiile random pe ecran
					int xA = rand() % (int)logicSpace.width + 1;
					int yA = rand() % (int)logicSpace.height + 1;

					bonus.setPosition(glm::vec2(xA, yA));
					bonus.setRadius(15);
					bonus.setScale(glm::vec2(15, 15));
				}
				else {
					bonus.time += deltaTime;
				}
			}


			/* ------- A aparut inamicul boss ---------- */
			if (bossIsHere == true) {

				// Miscarea bossului se face doar pe orizontala (stg - drp, drp - stg)
				boss.position.x += boss.sign * deltaTime * boss.speed;

				if (boss.position.x > logicSpace.width) {
					boss.position.x = logicSpace.width;
					boss.sign = -1;
				}
				else if (boss.position.x < 0) {
					boss.position.x = 0;
					boss.sign = 1;
				}

				// calculam timpul de tragere a bossului
				if (boss.time < boss.shoot + 0.001f) {
					boss.time += deltaTime;
				}
				// va arunca un proiectil
				else {
					boss.time = 0.0f;

					bullet.setPosition(boss.position);
					bullet.speed = 10;

					// setez directia proiectilului spre player 
					bullet.setVelocityVector(player.position);

					bullet.setScale(glm::vec2(3, 3));
					bullet.setRadius(3);
					bullet.setAngle(player.position);

					// adaugam proiectilul navei boss
					boss.Bullets.push_back(bullet);
				}
			}

		} // gameOver == false
}

void Tema1::OnKeyPress(int key, int mods)
{
	// Pauza joc
	if (key == 80) {
		pause = !pause;
	}
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event	
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	/* Cream un proiectil si il lansam  spre directia mouse-ului*/
	
	if (button == 1 && gameOver == false && pause == false) {
		bullet.setPosition(player.position);
		bullet.speed = 10;

		// calculam vectorul de viteza avand viteza 10
		bullet.setVelocityVector(glm::vec2(mouseX, logicSpace.height - mouseY));
		
		bullet.setScale(glm::vec2(3, 3));
		bullet.setRadius(3);
		bullet.setAngle(glm::vec2(mouseX, logicSpace.height - mouseY));

		// adaugam proiectilul navei
		player.Bullets.push_back(bullet);
	}
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	
}