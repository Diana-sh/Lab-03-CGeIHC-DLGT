#include <stdio.h>
#include <glew.h>
#include <glfw3.h>
//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;
float rojo, verde, azul = 0.0f;

int main()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow *mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "PRACTICA 1 Ejercicio 1", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);
	printf("Version de Opengl: %s \n",glGetString(GL_VERSION));
	printf("Marca: %s \n", glGetString(GL_VENDOR));
	printf("Renderer: %s \n", glGetString(GL_RENDERER));
	printf("Shaders: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		
		//Variable para obtener el tiempo actual
		double timeActual = glfwGetTime();
		//Variable para tiempo para cambiar color
		static double cambiarColor = 0;

		glClearColor(rojo, verde, azul, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(mainWindow);

		if (timeActual - cambiarColor > 3) {
			cambiarColor = timeActual;

			// Cambia el color de fondo rojo -> verde -> azul
			if (rojo == 1.0f && verde == 0.0f && azul == 0.0f) {
			// Cambiar a verde
				rojo = 0.0f;
				verde = 1.0f;
				azul = 0.0f;
			}
			// Cambia a azul
			else if (rojo == 0.0f && verde == 1.0f && azul == 0.0f) {
				rojo = 0.0f;
				verde = 0.0f;
				azul = 1.0f;
			}
			// Cambiar a rojo
			else {
				rojo = 1.0f;
				verde = 0.0f;
				azul = 0.0f;
			}
		}
	}

	return 0;
}