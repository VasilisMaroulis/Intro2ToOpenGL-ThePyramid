// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include <Windows.h>
#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3(10, 10, 30);

// Initial Field of View
float initialFoV = 45.0f;

float speed = 4.0f; // 3 units / second

void computeMatricesFromInputs(){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	
															

	// Direction
	glm::vec3 direction(0.0f, 0.0f, -1.0f);
	
	// Right vector
	glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);
	

	// left
	 glm::vec3 left = glm::vec3(-1.0f,0.0f,0.0f);

	// Up vector
	 glm::vec3 up = glm::cross(right, direction);

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_KP_ADD ) == GLFW_PRESS ){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_KP_SUBTRACT ) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}
	  // RIGHT
	if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS && (GetKeyState(VK_CAPITAL) & 0x0001) == 0){
		position +=  right * deltaTime * speed;
	}
	
	// left
	if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS && (GetKeyState(VK_CAPITAL) & 0x0001) == 0){
		position += left  * deltaTime * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && (GetKeyState(VK_CAPITAL) & 0x0001) == 0 ) {
		position += up * deltaTime * speed;
	}

	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS && (GetKeyState(VK_CAPITAL) & 0x0001) == 0) {
		position -= up * deltaTime * speed;
	}


		float FoV = initialFoV;
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	
	// Camera matrix
	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		glm::vec3(0.0f, 0.0f, 0.0f),  // and looks here : at the same position
		up
	);
	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
	
}