// Include GLFW
#include <glfw3.h>
//extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::mat4 ModelMatrix;
glm::vec3 position = glm::vec3( 18, 60, -50); // position of follow camera


glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}
glm::mat4 getModelMatrix(){
    return ModelMatrix;
}
glm::vec3 getPosition(){
    return position;
}


// Initial position : on +Z
// Initial horizontal angle : toward -Z
float horizontalAngle = 0.0f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;

float x = 0; //player x position;
float z = 0; //player z position;

void computeMatricesFromInputs(GLFWwindow* window, int width, int height){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();


	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, width / 2, height / 2);
	//std::cout << "****************** " << std::endl;

	//std::cout << "mouseSpeed: " <<  mouseSpeed << std::endl;

	// Compute new orientation 
	horizontalAngle += mouseSpeed * float(width/2 - xpos );
	verticalAngle   += mouseSpeed * float(height/2 - ypos );

	//std::cout << "changes: " << (width / 2 - xpos) << ", " << (height / 2 - ypos) << std::endl;
	//std::cout << "horizontalAngle: " << horizontalAngle << std::endl;
	//std::cout << "verticalAngle: " << verticalAngle << std::endl;


	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
//	std::cout << "direction: " << direction.x << ", " << direction.y << ", " << 
	//	direction.z << std::endl;
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	//std::cout << "right: " << right.x << ", " << right.y << ", " <<
	//	right.z << std::endl;

	// Up vector
	glm::vec3 up = glm::cross( right, direction );
	//std::cout << "position inital: " << position.x << ", " << position.y << ", " << position.z << std::endl;

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		position += direction * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		position -= direction * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
		position += right * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		position -= right * deltaTime * speed;
	}
    
    if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
        x = (x + 0.1);
    }
    // Move backward
    if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
        x = (x - 0.1);
    }
    // Strafe right
    if (glfwGetKey( window, GLFW_KEY_W ) == GLFW_PRESS){
        z = (z + 0.1);
    }
    // Strafe left
    if (glfwGetKey( window, GLFW_KEY_S ) == GLFW_PRESS){
        z = (z - 0.1);
    }
    
	//std::cout << "position after changes: " << position.x << ", " << position.y << ", " << position.z << std::endl;

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.
	
	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 4.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								glm::vec3(x,0,z), // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );
    ModelMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(x,0,z));
	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;

}
