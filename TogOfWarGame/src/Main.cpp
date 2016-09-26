// author : Lewis Ward
// program: PGAG Assignment 1
// date   : 17/11/2014
#include "gl/Program.h"
#include "Menu.h"
#include "Unit.h"
#include "Building.h"
#include "Sound.h"

int main(int argc, char *argv[])
{
	// gameloop when false will quit the program
	bool gameloop = initSDL();
	// setup delta time
	initTimerDT();

	// create window
	Window window;
	// set window title
	window.setTitle("Tog Of War - by Lewis Ward");
	// setup Glew
	initGlew();

	// mouse screen location, set to zero
	math::vec2 mouseScreenPos = math::v2Zero;

	// create shaders
	gls::Shader shaders[] = {
		gls::Shader("shaders/menu.vtx.glsl", gls::sVERTEX), ///< MENU
		gls::Shader("shaders/menu.pix.glsl", gls::sFRAGMENT), ///< MENU
		gls::Shader("shaders/terrain.vtx.glsl", gls::sVERTEX), ///< TERRAIN
		gls::Shader("shaders/terrain.pix.glsl", gls::sFRAGMENT), ///< TERRAIN
		gls::Shader("shaders/sprite.vtx.glsl", gls::sVERTEX), ///< SPRITE
		gls::Shader("shaders/sprite.pix.glsl", gls::sFRAGMENT) ///< SPRITE
	};

	// create program
	gls::Program program;
	gls::Program terrainProgram;
	gls::Program spriteProgram;
	program.create(&shaders[0], &shaders[1]);
	terrainProgram.create(&shaders[2], &shaders[3]);
	spriteProgram.create(&shaders[4], &shaders[5]);
	
	// load textures
	Texture textures[] = {
		("images/MainMenu.jpg"),
		("images/baseBlue.jpg"),
		("images/baseRed.jpg"),
		("images/world.jpg"),
		("images/BackgroundSky.jpg"),
		("images/BackgroundHillsNear.png"),
		("images/BackgroundHillsFar.png"),
		("images/TrainKnightButton.png"),
		("images/KnightSheet.png"),
		("images/GoblinSheet.png"),
		("images/RulesMenu.jpg"),
		("images/Won.jpg"),
		("images/Lose.jpg"),
		("images/RatSheet.png"),
		("images/EliteSheet.png"),

	};

	// create animation cycle data 
	float sheetHeight = 4.0f, sheetWidth = 9.0f;
	std::vector<float> rowAnimation;
	rowAnimation.push_back(8.0f);
	rowAnimation.push_back(6.0f);
	rowAnimation.push_back(5.0f);
	rowAnimation.push_back(9.0f);
	std::vector<float> rowAnimationEvil;
	rowAnimationEvil.push_back(8.0f);
	rowAnimationEvil.push_back(6.0f);
	rowAnimationEvil.push_back(7.0f);
	rowAnimationEvil.push_back(9.0f);

	// create player unit
	std::vector<Sprite*> knight;
	knight.push_back(new Sprite(textures[8], 1, 1, sheetHeight, sheetWidth, rowAnimation));
	knight[0]->state(1);
	float knightCost = 8.0f, knightDrop = 12.0f;
	std::vector<Unit*> unitKnight;
	unitKnight.push_back(new Unit(10.0f, 3.0f, 3.0f, knightDrop, knightCost, *knight[0]));
	unitKnight[0]->point(true);
	
	// Create enemy unit
	std::vector<Sprite*> goblin;
	goblin.push_back(new Sprite(textures[9], 1, 1, sheetHeight, sheetWidth, rowAnimationEvil));
	goblin[0]->state(1);
	float goblinCost = 5.0f, goblinDrop = 8.0f;
	std::vector<Unit*> unitGoblin;
	unitGoblin.push_back(new Unit(7.0f, 2.0f, 3.5f, goblinDrop, goblinCost, *goblin[0]));
	unitGoblin[0]->point(true);

	// create main menu and buttons
	gui::Menu mainMenu(textures[0].texture());
	// play button
	math::vec2 origin(28.0f, 282.0f);
	math::vec2 end(239.0f, 337.0f);
	gui::Button play(origin, end);
	mainMenu.addButton(play);
	// controls button
	origin.x = 273.0f;
	origin.y = 282.0f;
	end.x = 484.0f;
	end.y = 337.0f;
	gui::Button controls(origin, end);
	mainMenu.addButton(controls);
	// quit button
	origin.x = 28.0f;
	origin.y = 382.0f;
	end.x = 484.0f;
	end.y = 437.0f;
	gui::Button quit(origin, end);
	mainMenu.addButton(quit);
	// rules menu
	gui::Menu rulesMenu(textures[10].texture());
	rulesMenu.addButton(quit);
	// pointer for win/lose screen
	gui::Menu* resultMenu = NULL;
	// create main menu and buttons
	gui::Menu ingameGUI(textures[7].texture());
	// play button
	math::vec2 guiorigin(0.0f, 413.0f);
	math::vec2 guiend(264.0f, 512.0f);
	gui::Button build(guiorigin, guiend);
	ingameGUI.addButton(build);
	math::vec2 guioriginE(264.0f, 413.0f);
	math::vec2 guiendE(512.0f, 512.0f);
	gui::Button buildElite(guioriginE, guiendE);
	ingameGUI.addButton(buildElite);

	// load up the world and meshes
	World world("meshes/World.meshes");
	Mesh meshes[] = {
		("meshes/BaseBlue.meshes"),
		("meshes/BaseRed.meshes"),
		("meshes/BackgroundSky.meshes"),
		("meshes/BackgroundHillsFar.meshes"),
		("meshes/BackgroundHillsNear.meshes"),
	};

	// buildings data
	float baseHealth = 50.0f;
	math::vec3 spawnGood(-13.0f, -4.0f, -4.0f);
	math::vec3 spawnEvil(13.0f, -4.0f, -4.0f);
	// create two bases
	Building* bases[2];
	bases[0] = new Building(baseHealth, spawnGood, meshes[0], textures[1], "your base");
	bases[1] = new Building(baseHealth, spawnEvil, meshes[1], textures[2], "enemy base");

	// set mesh matrix data
	math::Mat3 meshModel;
	meshModel.w.x = -14.0f;
	meshModel.w.y = -4.0f;
	meshModel.w.z = -4.0f;
	bases[0]->model()->setMartix(meshModel);
	meshModel.w.x = 14.0f;
	bases[1]->model()->setMartix(meshModel);

	// load in 'plains' for the backgrounds
	meshModel.w.x = 0.0f;
	meshModel.w.y = 4.5f;
	meshes[2].setMartix(meshModel);
	meshModel.w.y = -3.5f;
	meshModel.w.z = -6.0f;
	meshes[3].setMartix(meshModel);
	meshModel.w.y = -5.5f;
	meshModel.w.z = -6.5f;
	meshes[4].setMartix(meshModel);
	
	// set sprite/unit matrix data
	math::Mat3 knightMat;
	math::Mat3 goblinModel;
	knightMat.w.x = -5.0f;
	knightMat.w.y = -3.6f;
	knightMat.w.z = -4.5f;
	knight[0]->matrix(knightMat);
	goblinModel.w.x = 5.0f;
	goblinModel.w.y = -3.6f;
	goblinModel.w.z = -4.5f;
	goblin[0]->matrix(goblinModel);

	// camera transforms
	math::Mat3 camera, projection, model, view, model_view, model_view_projection;
	camera.w.y = -2.0f;
	camera.w.z = 2.0f;

	// create event handler
	EventHandler events;
	// stores delta time
	float dt;
	// what mode (state) is the game in. For example on a menu or in game
	size_t mode = 0;

	// used to stop player 'spamming' out units
	float buildTimer = 0.0f;
	float enemyBuildTimer = 0.0f;
	// has the game be reset since last play
	bool reset = true;

	// clear the console (SDL_Image prints unwanted text to console)
	system("CLS");
	// set gold levels
	float playerGold = 20.0f;
	float enemyGold = 20.0f;
	std::cout << "Your Gold: " << playerGold << std::endl;
	
	// load sound, check file has loaded and play music
	Sound backgroundMusic("sounds/Serpentine_Trek.mp3");
	if (backgroundMusic.state())
		backgroundMusic.play();

	// updating and drawing the game takes place
	while (gameloop)
	{
		//---------------------------------------------- UPDATE ----------------------------------------------//
		{
			// update delta time
			dt = updateTimerDT();

			// update SDL events
			int eventCode = events.update();
			// has the user clicked on the quit button
			gameloop = events.playState();
			// update the mouse
			math::vec2 newMouse = events.mouseUpdate();

			// if in game
			if (mode == 1)
			{
				reset = false;
				// if the mouse is to the right of the screen
				if (newMouse.x > 400 && mouseScreenPos.x < 10.0f)
				{
					// update mouse position
					mouseScreenPos.x += 5 * dt;
					// update camera matrix
					camera.w.x = mouseScreenPos.x;

					// update and translate the backgrounds
					math::Mat3 backgrounds = meshes[3].martix();
					backgrounds.w.x += 3.0f * dt;
					meshes[3].setMartix(backgrounds);
					backgrounds = meshes[4].martix();
					backgrounds.w.x += 2.0f * dt;
					meshes[4].setMartix(backgrounds);
					// update the sky
					backgrounds = meshes[2].martix();
					backgrounds.w.x += 1.0f * dt;
					meshes[2].setMartix(backgrounds);
				}
				// if the mouse is to the left of the screen
				if (newMouse.x < 100 && mouseScreenPos.x > -10.0f)
				{
					// update mouse position
					mouseScreenPos.x -= 5 * dt;
					// update camera matrix
					camera.w.x = mouseScreenPos.x;

					// update and translate the backgrounds
					math::Mat3 backgrounds = meshes[3].martix();
					backgrounds.w.x -= 3.0f * dt;
					meshes[3].setMartix(backgrounds);
					backgrounds = meshes[4].martix();
					backgrounds.w.x -= 2.0f * dt;
					meshes[4].setMartix(backgrounds);
					// update the sky
					backgrounds = meshes[2].martix();
					backgrounds.w.x -= 1.0f * dt;
					meshes[2].setMartix(backgrounds);
				}

				// increase timer and gold
				buildTimer += 1.0f * dt;
				enemyBuildTimer += 1.0f * dt;
				enemyGold += 0.5f * dt;
				playerGold += 0.2f * dt;

				// if left mouse pressed
				if (eventCode == kMDL)
				{
					// find out which button was pressed
					int pressed = ingameGUI.clickButton(newMouse);

					// if it was pressed print result to console and move knight
					if (pressed == 0 && buildTimer >= 2.25f && playerGold >= 8.0f)
					{
						knightCost = 8.0f;
						// create a new knight
						knight.push_back(new Sprite(textures[8], 1, 1, sheetHeight, sheetWidth, rowAnimation));
						knight[knight.size() - 1]->state(1);
						unitKnight.push_back(new Unit(10.0f, 2.5f, 2.2f, knightDrop, knightCost, *knight[knight.size() - 1]));
						
						// set it's starting position
						knightMat.w.x = bases[0]->spawn().x;
						knightMat.w.y = -3.6f;
						knightMat.w.z = -4.5f;
						knight[knight.size() - 1]->matrix(knightMat);
						
						// quick check to see if there are any other ally units alive, if so unit is not on point.
						if (unitKnight.size() == 1)
						{ unitKnight[0]->point(true); }
						else
						{ unitKnight[knight.size() - 1]->point(false); }
						
						// reset the timer
						buildTimer = 0.0f;
						// reduce total gold
						playerGold -= unitKnight[unitKnight.size() - 1]->getGoldCost();
						std::cout <<"Your Gold: " << (int)playerGold << std::endl;
					}
					else if (pressed == 1 && playerGold >= 25.0f)
					{
						knightDrop = 8.0f;
						knightCost = 20.0f;
						// create a new knight
						knight.push_back(new Sprite(textures[14], 1, 1, sheetHeight, sheetWidth, rowAnimation));
						knight[knight.size() - 1]->state(1);
						unitKnight.push_back(new Unit(18.0f, 5.0f, 1.5f, knightDrop, knightCost, *knight[knight.size() - 1]));

						// set it's starting position
						knightMat.w.x = bases[0]->spawn().x;
						knightMat.w.y = -3.6f;
						knightMat.w.z = -4.5f;
						knight[knight.size() - 1]->matrix(knightMat);

						// quick check to see if there are any other ally units alive, if so unit is not on point.
						if (unitKnight.size() == 1)
						{
							unitKnight[0]->point(true);
						}
						else
						{
							unitKnight[knight.size() - 1]->point(false);
						}

						// reset the timer
						buildTimer = 0.0f;
						// reduce total gold
						playerGold -= unitKnight[unitKnight.size() - 1]->getGoldCost();
						std::cout << "Your Gold: " << (int)playerGold << std::endl;
					}
				}

				if (enemyGold >= goblinCost)
				{
					if (unitKnight.size() >= 2 && buildTimer >= 2.25f)
					{
						// create a new unit
						goblin.push_back(new Sprite(textures[9], 1, 1, sheetHeight, sheetWidth, rowAnimationEvil));
						goblin[goblin.size() - 1]->state(1);
						unitGoblin.push_back(new Unit(10.0f, 3.5f, 2.8f, goblinDrop, goblinCost, *goblin[goblin.size() - 1]));
						
						// set it's starting position
						knightMat.w.x = bases[1]->spawn().x;
						knightMat.w.y = -3.6f;
						knightMat.w.z = -4.5f;
						goblin[goblin.size() - 1]->matrix(knightMat);
						
						// quick check to see if there are any other ally units alive, if so unit is not on point.
						if (unitGoblin.size() == 1)
						{
							unitGoblin[0]->point(true);
						}
						else
						{
							unitGoblin[goblin.size() - 1]->point(false);
						}
						// reset the timer
						enemyBuildTimer = 0.0f;
						// reduce total gold
						enemyGold -= goblinCost;
					}
					else if (buildTimer >= 1.75f && unitGoblin.size() < 2)
					{
						for (size_t x = 0; x < 3; ++x*dt)
						{
							// create a new unit
							goblin.push_back(new Sprite(textures[13], 1, 1, sheetHeight, sheetWidth, rowAnimationEvil));
							goblin[goblin.size() - 1]->state(1);
							unitGoblin.push_back(new Unit(3.0f, 4.0f, 4.0f, goblinDrop, goblinCost, *goblin[goblin.size() - 1]));
							
							// set it's starting position
							knightMat.w.x = bases[1]->spawn().x;
							knightMat.w.y = -3.6f;
							knightMat.w.z = -4.5f;
							goblin[goblin.size() - 1]->matrix(knightMat);
							
							// quick check to see if there are any other ally units alive, if so unit is not on point.
							if (unitGoblin.size() == 1)
							{
								unitGoblin[0]->point(true);
							}
							else
							{
								unitGoblin[goblin.size() - 1]->point(false);
							}
						}
						// reset the timer
						enemyBuildTimer = 0.0f;
						// reduce total gold
						enemyGold -= goblinCost;
					}
				}

				bool inCombat;
				bool canMoveForwards;
				
				// cycle all knights
				for (size_t i = 0; i < unitKnight.size(); ++i)
				{
					// index zero will always be on point
					if (unitKnight[i]->getPoint() == true)
					{
						// if there are any enemies check to see if knight can move forwards into empty space
						if (unitGoblin.size())
						{
							canMoveForwards = unitKnight[i]->canMove(*unitGoblin[0]);
						}
						else
						{
							// no enemies to there is empty space
							canMoveForwards = true;
						}
				
						// the unit can move 
						if (canMoveForwards)
						{
							// set to walk state
							unitKnight[i]->getSprite()->state(1);
						}
						else
						{
							// as the unit is on point and can't move, it can attack or be killed
							// if its got health attack otherwise run death animation/death state
							if (unitKnight[i]->getHealth() >= 0.0f)
							{
								unitKnight[i]->getSprite()->state(2);
							}
							else
							{
								// out of health
								unitKnight[i]->getSprite()->state(3);
							}
						}
					}
					// behide someone
					else 
					{
						if (unitKnight.size() > 1)
							// test unit in front to see if there is psace to move into
							canMoveForwards = unitKnight[i]->canMove(*unitKnight[i - 1]);
						else
							canMoveForwards = true;
				
						// the unit can move 
						if (canMoveForwards)
						{
							// set to walk state
							unitKnight[i]->getSprite()->state(1);
						}
						else
						{
							// as the unit is not on point and connot move, go into idle state
							unitKnight[i]->getSprite()->state(0);
						}
					}
				}
				// cycle all enemies
				for (size_t i = 0; i < unitGoblin.size(); ++i)
				{
					// index zero will always be on point
					if (unitGoblin[i]->getPoint() == true)
					{
						// if there are any enemies check to see if unit can move forwards into empty space
						if (unitKnight.size())
						{
							canMoveForwards = unitKnight[i]->canMove(*unitGoblin[0]);
						}
						else
						{
							// no enemies to there is empty space
							canMoveForwards = true;
						}
				
						// the unit can move 
						if (canMoveForwards)
						{
							// set to walk state
							unitGoblin[i]->getSprite()->state(1);
						}
						else
						{
							// as the unit is on point and can't move, it can attack or be killed
							// if its got health attack otherwise run death animation/death state
							if (unitGoblin[i]->getHealth() >= 0.0f)
							{
								unitGoblin[i]->getSprite()->state(2);
							}
							else
							{
								// out of health
								unitGoblin[i]->getSprite()->state(3);
							}
						}
					}
					// behide someone
					else
					{
						// test unit in front to see if there is psace to move into
						canMoveForwards = unitGoblin[i - 1]->canMove(*unitGoblin[i]);
				
						// the unit can move 
						if (canMoveForwards)
						{
							// set to walk state
							unitGoblin[i]->getSprite()->state(1);
						}
						else
						{
							// as the unit is not on point and connot move, go into idle state
							unitGoblin[i]->getSprite()->state(0);
						}
					}
				}
				
				float baseHP;
				for (size_t i = 0; i < unitKnight.size(); ++i)
				{
					// in range of enemy base
					if (unitKnight[i]->getPosition().x >= bases[1]->spawn().x - 2.0f && !unitGoblin.size())
					{
						inCombat = true;
						unitKnight[i]->getSprite()->state(2);
					}

					// do an action based on state
					math::Mat3 tempMat = unitKnight[i]->getSprite()->matrix();	
					switch (unitKnight[i]->getSprite()->getState())
					{
					case 0: break;
					case 1:
						tempMat.w.x += unitKnight[i]->getMove() * dt;
						unitKnight[i]->getSprite()->matrix(tempMat);
						break;
					case 2: 
						// make sure there is a unit in the vector
						if (unitGoblin.size())
							unitsInCombat(*unitKnight[i], *unitGoblin[0], dt);
						else
						{
							baseHP = bases[1]->health();
							baseHP -= unitKnight[i]->getDamage() * dt;
							bases[1]->setHealth(baseHP);
							bases[1]->update();
							// display result screen
							if (baseHP <= 0.0f)
							{
								resultMenu = new gui::Menu(textures[11].texture());
								rulesMenu.addButton(quit);
								mode = 3;
							}
						}
						break;
					case 3:
						if (unitKnight[i]->getSprite()->isDead())
						{
							knight.erase(knight.begin());
							unitKnight.erase(unitKnight.begin());
							// set 'new' index zero element to be on point
							if (unitKnight.size())
								unitKnight[0]->point(true);
						}
						break;
					}
				}
				// cycle over all enemies
				for (size_t i = 0; i < unitGoblin.size(); ++i)
				{
					// in range of enemy base
					if (unitGoblin[i]->getPosition().x <= bases[0]->spawn().x + 2.0f && !unitKnight.size())
					{
						inCombat = true;
						unitGoblin[i]->getSprite()->state(2);
					}
					// do an action based on units' current state
					math::Mat3 tempMat = unitGoblin[i]->getSprite()->matrix();
					switch (unitGoblin[i]->getSprite()->getState())
					{
					case 0: break;
					case 1:
						tempMat.w.x -= unitGoblin[i]->getMove() * dt;
						goblin[i]->matrix(tempMat);
						break;
					case 2: 
						// make sure there is a unit in the vector
						if (unitKnight.size())
						unitsInCombat(*unitGoblin[i], *unitKnight[0], dt); 
						else
						{
							baseHP = bases[0]->health();
							baseHP -= unitGoblin[i]->getDamage() * dt;
							bases[0]->setHealth(baseHP);
							bases[0]->update();
							// display result screen
							if (baseHP <= 0.0f)
							{
								resultMenu = new gui::Menu(textures[12].texture());
								rulesMenu.addButton(quit);
								mode = 3;
							}
						}
						break;
					case 3:
						if (unitGoblin[i]->getSprite()->isDead())
						{
							// increase player gold
							playerGold += unitGoblin[i]->getGoldDrop();
							goblin.erase(goblin.begin());
							unitGoblin.erase(unitGoblin.begin());
							// set 'new' index zero to be on point
							if (unitGoblin.size())
								unitGoblin[0]->point(true);
							std::cout << "Your Gold: " << (int)playerGold << std::endl;
						}
						break;
					}
				}
				// update the sprites matrix and animation
				for (size_t i = 0; i < unitKnight.size(); ++i)
					unitKnight[i]->update(dt, unitKnight[i]->getSprite()->matrix());
				for (size_t i = 0; i < unitGoblin.size(); ++i)
					unitGoblin[i]->update(dt, unitGoblin[i]->getSprite()->matrix());
			}
			// if on the main menu
			else if (mode == 0)
			{
				// if left mouse pressed
				if (eventCode == kMDL)
				{
					// find out which button was pressed
					int pressed = mainMenu.clickButton(newMouse);

					// if it was pressed print result to console
					switch (pressed)
					{
					case 0: mode = 1; break; ///< play game
					case 1: mode = 2; break; ///< controls
					case 2: if (mode == 0) gameloop = false; break; ///< quit
					}
				}
				// reset units, event trackers etc.
				if (reset == false)
				{
					for (size_t i = 0; i < knight.size(); ++i)
					{
						knight[i]->~Sprite();
						unitKnight[i]->~Unit();
					}
					knight.clear();
					unitKnight.clear();
					for (size_t i = 0; i < goblin.size(); ++i)
					{
						goblin[i]->~Sprite();
						unitGoblin[i]->~Unit();
					}
					goblin.clear();
					unitGoblin.clear();
					bases[0]->setHealth(50.0f);
					bases[1]->setHealth(50.0f);
					reset = true;
				}
			}
			else if (mode == 2 || mode == 3)
			{
				// if left mouse pressed
				if (eventCode == kMDL)
				{
					// find out which button was pressed
					int pressed = rulesMenu.clickButton(newMouse);
					// make sure button is pressed
					if (pressed == 0)
						mode = 0;
				}
			}

			//---------------------------------------------- DRAW ----------------------------------------------//
			{
				// enable OpenGL 2D textures and depth testing
				glEnable(GL_TEXTURE_2D);
				glEnable(GL_DEPTH_TEST);		
				glEnable(GL_BLEND);
				// blending function or alpha channels
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

				// clear the colour and depth buffer
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// if on a menu draw that menu
				if (mode == 0)
				{
					// bind the program
					program.bind();
					// shader unifroms
					program.uniform_1i("texture", 0);
					// draw the menu
					mainMenu.draw();
					// unbind program and texture
					program.unbind();
				}
				else if (mode == 1) // if play is pressed
				{
					// store the mvp matrix in an array of floats
					float mvpAsFloats[16];

					// --------------------------------------- WORLD DRAW --------------------------------------- //
					// update model transform				
				  model.w.x = 0.0f;
					model.w.y = -5.0f;
				  model.w.z = -2.0f;

					// compute aspect ratio
					float aspectRatio = float(window.width()) / float(window.height());
					// compute the projection
					projection.rightHandPerspective(90.0f * PI / 180, aspectRatio, 0.1f, 100.0f);
					// inverse the camera transform to get the View martix
					view = inverse(camera);

					// compute Model-View matrix
					model_view = model * view;
					// make the matrix w.w value 1
					addW(model_view);
					// compute Model-View-Projection matrix
					model_view_projection.multiplyMatrix(projection, model_view);

					// bind the program
					terrainProgram.bind();
					// convert mvp matrix to array of floats
					model_view_projection.matrixAsArray(mvpAsFloats);
					textures[3].bind(1);
					// shader unifroms
					terrainProgram.uniform_1i("texture", 1);
					terrainProgram.uniform_4f("ambient", 0.3f, 0.3f, 0.3f, 0.3f);
					terrainProgram.uniform_4f("diffuse", 0.9f, 0.9f, 0.9f, 0.9f);
					terrainProgram.uniform_Matrix4("mvp", 1, false, mvpAsFloats);
					world.draw();
					textures[3].unbind();

					// --------------------------------------- MESHES DRAW --------------------------------------- //
					textures[3].bind(3); ///< world
					textures[4].bind(4); ///< BackgroundSky
					textures[5].bind(5); ///< BackgroundHillsNear
					textures[6].bind(6); ///< BackgroundHillsFar


					// compute Model-View matrix
					model_view = meshes[2].martix() * view;
					// compute Model-View-Projection matrix
					model_view_projection.multiplyMatrix(projection, model_view);
					// convert mvp matrix to array of floats
					model_view_projection.matrixAsArray(mvpAsFloats);

					// shader unifroms
					terrainProgram.uniform_1i("texture", 4);
					terrainProgram.uniform_Matrix4("mvp", 1, false, mvpAsFloats);
					// draw mesh one
					meshes[2].draw();
					
					// compute Model-View matrix
					model_view = meshes[3].martix() * view;
					// compute Model-View-Projection matrix
					model_view_projection.multiplyMatrix(projection, model_view);
					// convert mvp matrix to array of floats
					model_view_projection.matrixAsArray(mvpAsFloats);

					// update a few of the unifroms
					terrainProgram.uniform_1i("texture", 6);
					terrainProgram.uniform_Matrix4("mvp", 1, false, mvpAsFloats);
					meshes[3].draw();

					// compute Model-View matrix
					model_view = meshes[4].martix() * view;
					// compute Model-View-Projection matrix
					model_view_projection.multiplyMatrix(projection, model_view);
					// convert mvp matrix to array of floats
					model_view_projection.matrixAsArray(mvpAsFloats);

					// update a few of the unifroms
					terrainProgram.uniform_1i("texture", 5);
					terrainProgram.uniform_Matrix4("mvp", 1, false, mvpAsFloats);
					meshes[4].draw();

					// compute Model-View matrix
					model_view = bases[0]->model()->martix() * view;
					// compute Model-View-Projection matrix
					model_view_projection.multiplyMatrix(projection, model_view);
					// convert mvp matrix to array of floats
					model_view_projection.matrixAsArray(mvpAsFloats);

					// update a few of the unifroms
					terrainProgram.uniform_1i("texture", 0);
					terrainProgram.uniform_Matrix4("mvp", 1, false, mvpAsFloats);
					bases[0]->draw();


					// compute Model-View matrix
					model_view = bases[1]->model()->martix()* view;
					// compute Model-View-Projection matrix
					model_view_projection.multiplyMatrix(projection, model_view);
					// convert mvp matrix to array of floats
					model_view_projection.matrixAsArray(mvpAsFloats);

					// update a few of the unifroms
					terrainProgram.uniform_Matrix4("mvp", 1, false, mvpAsFloats);
					// draw mesh two
					bases[1]->draw();

					// unbind textures
					textures[3].unbind();
					textures[4].unbind();
					textures[5].unbind();
					textures[6].unbind();

					// unbind the program
					terrainProgram.unbind();

					// bind the program
					spriteProgram.bind();
					for (size_t i = 0; i < unitKnight.size(); ++i)
					{
						// set the model
						knightMat.w.x = unitKnight[i]->getSprite()->matrix().w.x;
						// compute Model-View matrix
						model_view = knightMat * view;
						// compute Model-View-Projection matrix
						model_view_projection.multiplyMatrix(projection, model_view);
						// convert mvp matrix to array of floats
						model_view_projection.matrixAsArray(mvpAsFloats);
						// set the unifroms
						spriteProgram.uniform_1i("texture", 0);
						spriteProgram.uniform_4f("ambient", 0.2f, 0.2f, 0.2f, 0.0f);
						spriteProgram.uniform_4f("diffuse", 1.0f, 1.0f, 1.0f, 1.0f);
						spriteProgram.uniform_Matrix4("mvp", 1, false, mvpAsFloats);
						unitKnight[i]->draw();
					}
					for (size_t i = 0; i < unitGoblin.size(); ++i)
					{
						// set the model
						goblinModel.w.x = unitGoblin[i]->getSprite()->matrix().w.x;
						// compute Model-View matrix
						model_view = goblinModel * view;
						// compute Model-View-Projection matrix
						model_view_projection.multiplyMatrix(projection, model_view);
						// convert mvp matrix to array of floats
						model_view_projection.matrixAsArray(mvpAsFloats);
						// set the unifroms
						spriteProgram.uniform_Matrix4("mvp", 1, false, mvpAsFloats);
						unitGoblin[i]->draw();
					}
					// unbind program
					spriteProgram.unbind();

					// bind the program
					program.bind();
					// shader unifroms
					program.uniform_1i("texture", 0);
					// if still on cool down grey out button
					if (buildTimer < 2.25f)
					{ program.uniform_4f("state", -0.5f, -0.5f, -0.5f, 0.0f); }
					// draw the menu
					ingameGUI.draw();
					// reset to default
					program.uniform_4f("state", 0.0f, 0.0f, 0.0f, 0.0f);
					// unbind program and texture
					program.unbind();
				}
				else if (mode == 2)
				{
					// bind the program
					program.bind();
					// shader unifroms
					program.uniform_1i("texture", 0);
					// draw the menu
					rulesMenu.draw();
					// unbind program and texture
					program.unbind();
				}
				else if (mode == 3)
				{
					// bind the program
					program.bind();
					// shader unifroms
					program.uniform_1i("texture", 0);
					// draw the menu
					resultMenu->draw();
					// unbind program and texture
					program.unbind();
				}

				// disable OpenGL 2D textures and depth testing
				glDisable(GL_TEXTURE_2D);
				glDisable(GL_DEPTH_TEST);
				glDisable(GL_BLEND);

				// swap the SDL window
				SDL_GL_SwapWindow(window.getWindow());
			}
		}

	}
	// delete objects
	mainMenu.~Menu();
	// delete shaders
	size_t arraySize = sizeof(shaders) / sizeof(shaders[0]);
	for (size_t i = 0; i < arraySize; ++i)
		shaders[i].~Shader();
	// delete textures
	arraySize = sizeof(textures) / sizeof(textures[0]);
	for (size_t i = 0; i < arraySize; ++i)
		textures[i].~Texture();
	for (size_t i = 0; i < knight.size(); ++i)
	{
		knight[i]->~Sprite();
		unitKnight[i]->~Unit();
	}
	knight.clear();
	unitKnight.clear();
	for (size_t i = 0; i < goblin.size(); ++i)
	{
		goblin[i]->~Sprite();
		unitGoblin[i]->~Unit();
	}
	
	goblin.clear();
	unitGoblin.clear();
	bases[0]->~Building();
	bases[1]->~Building();
	delete resultMenu;
	window.~Window();
	// quit SDL
	SDL_Quit();
	// quit program
	return 0;
}
