/*
Práctica 5: Optimización y Carga de Modelos
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_m.h"
#include "Camera.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
Model CGoddard;
Model Cabeza;
Model Colita;
Model Mandibulita;
Model PatitaDel_Dere;
Model PatitaAtr_Dere;
Model PatitaDel_Izqu;
Model PatitaAtr_Izqu;
Model Goddard_M;

//MODELOS PARA EL COCHE
Model CARRITO;
Model COFRE;
Model LlantaDelDER;
Model LlantaTraDER;
Model LlantaDelIZQ;
Model LlantaTraIZQ;


Skybox skybox;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_m.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_m.frag";





void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};


	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}



int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.5f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 1.0f);

	CGoddard = Model();
	CGoddard.LoadModel("Models/Cuerpecito.obj");
	Cabeza = Model();
	Cabeza.LoadModel("Models/Cabeza.obj");
	Colita = Model();
	Colita.LoadModel("Models/Colita.obj");
	Mandibulita = Model();
	Mandibulita.LoadModel("Models/Mandibulita.obj");
	PatitaDel_Dere = Model();
	PatitaDel_Dere.LoadModel("Models/PataDelante_Dere.obj");
	PatitaAtr_Dere = Model();
	PatitaAtr_Dere.LoadModel("Models/PataAtras_Dere.obj");
	PatitaDel_Izqu = Model();
	PatitaDel_Izqu.LoadModel("Models/PataDelante_Izqu.obj");
	PatitaAtr_Izqu = Model();
	PatitaAtr_Izqu.LoadModel("Models/PataAtras_Izqu.obj");

	Goddard_M = Model();
	Goddard_M.LoadModel("Models/goddard_base.obj");

	//MODELOS PARA EL COCHE
	CARRITO = Model();
	CARRITO.LoadModel("Models/CARRITO.obj");
	COFRE = Model();
	COFRE.LoadModel("Models/COFRE.obj");
	LlantaDelDER = Model();
	LlantaDelDER.LoadModel("Models/LlantaDelDER.obj");
	LlantaTraDER = Model();
	LlantaTraDER.LoadModel("Models/LlantaTraDER.obj");
	LlantaDelIZQ = Model();
	LlantaDelIZQ.LoadModel("Models/LlantaDelIZQ.obj");
	LlantaTraIZQ = Model();
	LlantaTraIZQ.LoadModel("Models/LlantaTraIZQ.obj");


	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);


	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::mat4 modelaux2(1.0);

	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Se dibuja el Skybox
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		float angulo1 = glm::clamp(mainWindow.getarticulacion1(), 0.0f, 45.0f);
		float angulo2 = glm::clamp(mainWindow.getarticulacion2(), 0.0f, 45.0f);
		float angulo3 = glm::clamp(mainWindow.getarticulacion3(), 0.0f, 45.0f);
		float angulo4 = glm::clamp(mainWindow.getarticulacion4(), 0.0f, 45.0f);
		float angulo5 = glm::clamp(mainWindow.getarticulacion5(), 0.0f, 45.0f);
		float angulo6 = glm::clamp(mainWindow.getarticulacion6(), 0.0f, 45.0f);
		float angulo7 = glm::clamp(mainWindow.getarticulacion7(), 0.0f, 45.0f);
		float angulo8 = glm::clamp(mainWindow.getarticulacion8(), 0.0f, 45.0f);
		float angulo9 = glm::clamp(mainWindow.getarticulacion9(), 0.0f, 45.0f);
		float angulo10 = glm::clamp(mainWindow.getarticulacion10(), 0.0f, 45.0f);


		float adelante = mainWindow.getarticulacion1() * 0.05f;    
		float atras = mainWindow.getarticulacion2() * 0.05f;  
		float movimiento = adelante - atras;  //Traslación


		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		// INICIA DIBUJO DEL PISO
		color = glm::vec3(0.5f, 0.5f, 0.5f); //piso de color gris
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[2]->RenderMesh();

		//------------------------------COCHE--------------------------------------------
		//CARRITO
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.6f, 0.0f));
		//Traslacion del coche
		model = glm::translate(model, glm::vec3(movimiento, 0.0f, 0.0f));
		modelaux = model;
		color = glm::vec3(0.5f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CARRITO.RenderModel();

		//Llanta Delantera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(5.8f, -1.0f, 1.621f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(0.0f, 0.0f, -1.0f));
		color = glm::vec3(0.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantaDelDER.RenderModel();

		//Llanta Trasera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-6.0f, -1.0f, 1.621f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantaTraDER.RenderModel();

		//Llanta Delantera Izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(5.8f, -1.0f, -0.9f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantaDelIZQ.RenderModel();

		//Llanta Trasera Izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(-5.8f, -1.0f, -0.9f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		LlantaTraIZQ.RenderModel();

		//COFRE
		model = modelaux;
		model = glm::translate(model, glm::vec3(4.495f, 1.22f, 0.42f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacionC()), glm::vec3(0.0f, 0.0f, 1.0f));
		color = glm::vec3(1.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		COFRE.RenderModel();

		
		/*
		//------------*INICIA DIBUJO DE NUESTROS DEMÁS OBJETOS-------------------*
		//Goddard
		color = glm::vec3(0.0f, 0.0f, 0.0f); //modelo de goddard de color negro

		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.64f, 0.0f));
		modelaux = model;
		color = glm::vec3(0.0f, 0.0f, 0.5f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CGoddard.RenderModel();
		//En sesión se separara una parte del modelo de Goddard y se unirá por jeraquía al cuerpo

		//Cabeza
		model = modelaux;
		model = glm::translate(model, glm::vec3(1.5f, 0.5f, 0.0f));
		modelaux2 = model;
		color = glm::vec3(0.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza.RenderModel();

		//Mandibula
		model = modelaux2;
		model = glm::translate(model, glm::vec3(1.75f, 0.3f, 0.0f));
		model = glm::rotate(model, glm::radians(angulo1), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(angulo2), glm::vec3(0.0f, 0.0f, -1.0f));
		color = glm::vec3(1.0f, 1.0f, 0.0f); //modelo de goddard de color negro                                    
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mandibulita.RenderModel();

		//Colita
		model = modelaux;
		model = glm::translate(model, glm::vec3(-1.7f, -0.3f, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Colita.RenderModel();

		//pata delantera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(1.1f, -0.3f, 0.6f));
		model = glm::rotate(model, glm::radians(angulo3), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(angulo4), glm::vec3(0.0f, 0.0f, -1.0f));
		color = glm::vec3(0.0f, 0.0f, 0.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PatitaDel_Dere.RenderModel();//modificar para la pata delantera derecha 

		// pata delantera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(1.1f, -0.35f, -0.6f));
		model = glm::rotate(model, glm::radians(angulo5), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(angulo6), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PatitaDel_Izqu.RenderModel();

		//pata trasera derecha
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.5f, -1.0f, 0.6f));
		model = glm::rotate(model, glm::radians(angulo7), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(angulo8), glm::vec3(0.0f, 0.0f, -1.0f));
		color = glm::vec3(1.0f, 0.0f, 0.5f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PatitaAtr_Dere.RenderModel();//modificar por Pata trasera Izquierda

		//pata trasera izquierda
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.5f, -1.15f, -0.6f));
		model = glm::rotate(model, glm::radians(angulo9), glm::vec3(0.0f, 0.0f, 1.0f));
		model = glm::rotate(model, glm::radians(angulo10), glm::vec3(0.0f, 0.0f, -1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		PatitaAtr_Izqu.RenderModel();//modificar para Pata trasera Izquierda
		*/

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}