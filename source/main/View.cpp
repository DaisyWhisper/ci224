#include "View.hpp"

View::View(int widtht, int heightt) {
    width = widtht;
    height = heightt;
   
}
View::~View() {
    
}

int View::initialise() {
    
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    

    
    // Open a window and create its OpenGL context
    window = glfwCreateWindow(width, height, "My Game", NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
 
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);  //no cursor
    
     glewExperimental = true;  // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Set the mouse at the center of the screen
    
    glfwPollEvents();
    //we set the cursor at the centre so that it always start on our origin (0,0,0)
    glfwSetCursorPos(window, width / 2, height / 2);
    
    
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    

    
    //std::vector<glm::vec2> uvs; // Won't be used at the moment.
    //std::vector<glm::vec3> normals; // Won't be used at the moment.
    
    std::vector<unsigned short> indices;
    
    std::vector<glm::vec2> indexed_uvs;
    
    std::vector<glm::vec3> indexed_normals;
    
   // bool res = loadAssImp("wallWest.obj", indices, indexed_vertices, indexed_uvs, indexed_normals);
    bool res = loadOBJ("player.obj", playerVertices, indexed_uvs, indexed_normals);
    bool res1 = loadOBJ("wallEast.obj", mazeVertices, indexed_uvs, indexed_normals);
    bool res2 = loadOBJ("wallNorth.obj", mazeVertices, indexed_uvs, indexed_normals);
    bool res3 = loadOBJ("wallSouth.obj", mazeVertices, indexed_uvs, indexed_normals);
    bool res4 = loadOBJ("wallWest.obj", mazeVertices, indexed_uvs, indexed_normals);
    bool res5 = loadOBJ("wallInner1.obj", mazeVertices, indexed_uvs, indexed_normals);
    bool res6 = loadOBJ("wallInner2.obj", mazeVertices, indexed_uvs, indexed_normals);
    bool res7 = loadOBJ("wallInner3.obj", mazeVertices, indexed_uvs, indexed_normals);
    bool res8 = loadOBJ("wallInner4.obj", mazeVertices, indexed_uvs, indexed_normals);
    bool res9 = loadOBJ("wallInner5.obj", mazeVertices, indexed_uvs, indexed_normals);
    bool res10 = loadOBJ("collectable.obj", collectableVertices, indexed_uvs, indexed_normals);
 
   // bool res1 = loadOBJ("wallEast.obj", indexed_vertices, indexed_uvs, indexed_normals);
    //bool res2 = loadAssImp("wallNorth.obj", indices, indexed_vertices, indexed_uvs, indexed_normals);
   // bool res3 = loadAssImp("wallSouth.obj", indices, indexed_vertices, indexed_uvs, indexed_normals);
    //bool res4 = loadAssImp("floor.obj", indices, indexed_vertices, indexed_uvs, indexed_normals);
    //bool res5 = loadAssImp("wallInner1.obj",indices, indexed_vertices, indexed_uvs, indexed_normals);
    //bool res6 = loadAssImp("wallInner2.obj", indices, indexed_vertices, indexed_uvs, indexed_normals);
   // bool res7 = loadAssImp("wallInner3.obj", indices, indexed_vertices, indexed_uvs, indexed_normals);
   // bool res8 = loadAssImp("wallInner4.obj", indices, indexed_vertices, indexed_uvs, indexed_normals);
    //bool res9 = loadAssImp("wallInner5.obj", indices, indexed_vertices, indexed_uvs, indexed_normals);
   // bool res10 = loadAssImp("player.obj", indices, indexed_vertices, indexed_uvs, indexed_normals);
   // bool res11 = loadAssImp("collectable.obj", indices, indexed_vertices, indexed_uvs, indexed_normals);
    
    
    
    glGenBuffers(1, &mazeVertexbuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, mazeVertexbuffer);
    
    glBufferData(GL_ARRAY_BUFFER, mazeVertices.size()*sizeof(glm::vec3), &mazeVertices[0], GL_STATIC_DRAW);
    
    //glGenBuffers(1, &vertexbuffer);
    
    //glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    
    //glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    //glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    glGenBuffers(1, &playerVertexbuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, playerVertexbuffer);
    
    glBufferData(GL_ARRAY_BUFFER, playerVertices.size()*sizeof(glm::vec3), &playerVertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &collectableVertexbuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, collectableVertexbuffer);
    
    glBufferData(GL_ARRAY_BUFFER, collectableVertices.size()*sizeof(glm::vec3), &collectableVertices[0], GL_STATIC_DRAW);
    
    programID = LoadShaders("SimpleVertexShader.hlsl", "SimpleFragmentShader.hlsl");
    MatrixID1 = glGetUniformLocation(programID, "MVP");


    return 1;
}

/*// camera stuff 
glm::mat4 getStaticMVPMatrix() {
glm ::mat4 Projection = glm::perspective(glm::radians(70.0f), //field of view is close up
                                         4.0f/3.0f,
                                         0.1f,
                                         1000.0f);

glm::mat4 View = (mat4) glm::lookAt(glm::vec3(0,50,2), //camera is here
                                    glm::vec3(0,0,0),      //and looks at the origin
                                    glm::vec3(0,1,0));

glm::mat4 Model = glm::mat4(1.0f); // keeping identity matrix to keep geometry where it was placed

glm::mat4 mvp = Projection * View * Model; // matrix multiplication is the other way around

return mvp;

} */

glm::mat4 getMVPMatrix(glm::mat4 ProjectionMatrix, glm::mat4 ViewMatrix, glm::mat4 ModelMatrix) {
    
    
    
    
    
    
    
    glm::mat4 Projection = ProjectionMatrix;
    
    glm::mat4 View = ViewMatrix;

    glm::mat4 Model = ModelMatrix;
    
    glm::mat4 mvp = Projection * View * Model; // Remember, matrix multiplication is the other way around
    
    
    
    return mvp;
    
    
    
    
    
    
    
}

void View::update() {
    MatrixID1 = glGetUniformLocation(programID, "MVP");
    do{
        // Clear the screen. It's not mentioned before Tutorial 02, but it can cause flickering, so it's there nonetheless.
        glClear( GL_COLOR_BUFFER_BIT );
        
        glUseProgram(programID);
        
        computeMatricesFromInputs(window, width, height);
        
        glm::mat4 mvp1 = getMVPMatrix(getProjectionMatrix(),getViewMatrix(), glm::mat4(1.0f));
        
        glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp1 [0][0]);

        glEnableVertexAttribArray(0);
        
        glBindBuffer(GL_ARRAY_BUFFER, mazeVertexbuffer);
        
        glVertexAttribPointer(
                              
                              0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                              
                              3,                  // size
                              
                              GL_FLOAT,           // type
                              
                              GL_FALSE,           // normalized?
                              
                              0,                  // stride
                              
                              (void*)0            // array buffer offset
                              
                              );
        
        
        
        // Draw the triangles
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        // glDrawArrays(GL_TRIANGLES, 0, vertices.size() * sizeof(glm::vec3));
        
        std::cout << mazeVertices.size() << std::endl;
        glDrawArrays(GL_TRIANGLES, 0, mazeVertices.size() );
  
        glBindBuffer(GL_ARRAY_BUFFER, collectableVertexbuffer);
        
        glVertexAttribPointer(
                              
                              0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                              
                              3,                  // size
                              
                              GL_FLOAT,           // type
                              
                              GL_FALSE,           // normalized?
                              
                              0,                  // stride
                              
                              (void*)0            // array buffer offset
                              
                              );
        
        glDrawArrays(GL_TRIANGLES, 0, collectableVertices.size());
        
        glm::mat4 mvp2 = getMVPMatrix(getProjectionMatrix(),getViewMatrix(),getModelMatrix());
        
        glUniformMatrix4fv(MatrixID1, 1, GL_FALSE, &mvp2 [0][0]);
        
        
        
        glBindBuffer(GL_ARRAY_BUFFER,playerVertexbuffer);
        
        glVertexAttribPointer(
                              
                              0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                              
                              3,                  // size
                              
                              GL_FLOAT,           // type
                              
                              GL_FALSE,           // normalized?
                              
                              0,                  // stride
                              
                              (void*)0            // array buffer offset
                              
                              );
        
        glDrawArrays(GL_TRIANGLES, 0, playerVertices.size());
        glDisableVertexAttribArray(0);
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
}

