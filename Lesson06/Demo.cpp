#include "Demo.h"



Demo::Demo() {

}

Demo::~Demo() {
}

void Demo::Init() {
	// build and compile our shader program
	// ------------------------------------
	shaderProgram = BuildShader("vertexShader.vert", "fragmentShader.frag", nullptr);

	BuildColoredCube();

	BuildColoredPlane();
}

void Demo::DeInit() {
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO2);
	glDeleteBuffers(1, &VBO2);
	glDeleteBuffers(1, &EBO2);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Demo::ProcessInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}



}

void Demo::Update(double deltaTime) {
	angle += (float)((deltaTime * 1.5f) / 1000);
}

void Demo::Render() {
	glViewport(0, 0, this->screenWidth, this->screenHeight);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(255.0/255.0f, 160.0/255.0f, 122.0/255.0f, 1.0f);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_DEPTH_TEST);

	// Pass perspective projection matrix
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)this->screenWidth / (GLfloat)this->screenHeight, 0.1f, 100.0f);
	GLint projLoc = glGetUniformLocation(this->shaderProgram, "projection");
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	// LookAt camera (position, target/direction, up)
	glm::mat4 view = glm::lookAt(glm::vec3(0, 5, 12), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	GLint viewLoc = glGetUniformLocation(this->shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));

	// set lighting attribute
	GLint lightPosLoc = glGetUniformLocation(this->shaderProgram, "lightPos");
	glUniform3f(lightPosLoc, 0, 1, 0);
	GLint viewPosLoc = glGetUniformLocation(this->shaderProgram, "viewPos");
	glUniform3f(viewPosLoc, 0, 2, 3);
	GLint lightColorLoc = glGetUniformLocation(this->shaderProgram, "lightColor");
	glUniform3f(lightColorLoc, 1.0f, 1.0f, 1.0f);
	
	//DrawColoredCube();
	//DrawColoredCubee();
	DrawBuilding();
	DrawTree();
	DrawStreet();
	DrawBuildingPutih();
	DrawBuildingBelakang();
	DrawBuildingDepan();
	DrawColoredPlane();

	glDisable(GL_DEPTH_TEST);
}

void Demo::BuildColoredCube() {
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// format position, tex coords
		// front
		-0.5, -0.5, 0.5,  0.0f,  0.0f,  1.0f, // 0
		0.5, -0.5, 0.5,   0.0f,  0.0f,  1.0f, // 1
		0.5,  0.5, 0.5,   0.0f,  0.0f,  1.0f, // 2
		-0.5,  0.5, 0.5,  0.0f,  0.0f,  1.0f, // 3

		// right
		0.5,  0.5,  0.5, 1.0f,  0.0f,  0.0f, // 4
		0.5,  0.5, -0.5, 1.0f,  0.0f,  0.0f, // 5
		0.5, -0.5, -0.5, 1.0f,  0.0f,  0.0f, // 6
		0.5, -0.5,  0.5, 1.0f,  0.0f,  0.0f, // 7

		// back
		-0.5, -0.5, -0.5, 0.0f,  0.0f,  -1.0f, // 8 
		0.5,  -0.5, -0.5, 0.0f,  0.0f,  -1.0f, // 9
		0.5,   0.5, -0.5, 0.0f,  0.0f,  -1.0f, // 10
		-0.5,  0.5, -0.5, 0.0f,  0.0f,  -1.0f, // 11

		// left
		-0.5, -0.5, -0.5, -1.0f,  0.0f,  0.0f, // 12
		-0.5, -0.5,  0.5, -1.0f,  0.0f,  0.0f, // 13
		-0.5,  0.5,  0.5, -1.0f,  0.0f,  0.0f, // 14
		-0.5,  0.5, -0.5, -1.0f,  0.0f,  0.0f, // 15

		// upper
		0.5, 0.5,  0.5, 0.0f,  1.0f,  0.0f, // 16
		-0.5, 0.5, 0.5, 0.0f,  1.0f,  0.0f, // 17
		-0.5, 0.5, -0.5,0.0f,  1.0f,  0.0f, // 18
		0.5, 0.5, -0.5, 0.0f,  1.0f,  0.0f, // 19

		// bottom
		-0.5, -0.5, -0.5, 0.0f,  -1.0f,  0.0f, // 20
		0.5, -0.5, -0.5,  0.0f,  -1.0f,  0.0f, // 21
		0.5, -0.5,  0.5,  0.0f,  -1.0f,  0.0f, // 22
		-0.5, -0.5,  0.5, 0.0f,  -1.0f,  0.0f, // 23
	};

	unsigned int indices[] = {
		0,  1,  2,  0,  2,  3,   // front
		4,  5,  6,  4,  6,  7,   // right
		8,  9,  10, 8,  10, 11,  // back
		12, 14, 13, 12, 15, 14,  // left
		16, 18, 17, 16, 19, 18,  // upper
		20, 22, 21, 20, 23, 22   // bottom
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// define position pointer layout 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);

	// define normal pointer layout 2
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);

	// remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

//void Demo::DrawColoredCube()
//{
//	UseShader(shaderProgram);
//
//	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//
//	GLint objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
//	glUniform3f(objectColorLoc, 0.0f, 0.0f, 0.0f);
//
//	glm::mat4 model;
//	model = glm::translate(model, glm::vec3(0, 0, 0));
//	//model = glm::rotate(model,angle, glm::vec3(0, 1, 0));
//	model = glm::scale(model, glm::vec3(0.7, 1.1, 0.5));
//
//	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//
//	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	//kaki
//	for (int i = 0;i < 4;i++) {
//		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
//		glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.0f);
//
//		glm::mat4 model2;
//		model2 = glm::translate(model2, glm::vec3(0, 0.5 + i * 0.2, 0));
//		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
//		model2 = glm::scale(model2, glm::vec3(0.7, 0.2, 0.5));
//
//		glGetUniformLocation(this->shaderProgram, "model");
//		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
//
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//	}
//	//badan
//	for (int i = 0;i < 10;i++) {
//		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
//		glUniform3f(objectColorLoc, 0.0f, 0.5f, 0.0f);
//
//		glm::mat4 model2;
//		model2 = glm::translate(model2, glm::vec3(0.5, 1.3 + i * 0.2, 0));
//		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
//		model2 = glm::scale(model2, glm::vec3(1.7, 0.2, 0.5));
//
//		glGetUniformLocation(this->shaderProgram, "model");
//		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
//
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//	}
//	//kepala
//	for (int i = 0;i < 2;i++) {
//		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
//		glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.0f);
//
//		glm::mat4 model2;
//		model2 = glm::translate(model2, glm::vec3(0.5, 3.4 + i * 0.2, 0));
//		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
//		model2 = glm::scale(model2, glm::vec3(1.2, 0.4, 0.6));
//
//		glGetUniformLocation(this->shaderProgram, "model");
//		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
//
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//	}
//	//mata
//	for (int i = 0;i < 1;i++) {
//		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
//		glUniform3f(objectColorLoc, 0.0f, 0.0f, 0.0f);
//
//		glm::mat4 model2;
//		model2 = glm::translate(model2, glm::vec3(1, 4 + i * 0.2, 0));
//		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0)); 
//		model2 = glm::scale(model2, glm::vec3(0.2, 0.2, 0.2));
//
//		glGetUniformLocation(this->shaderProgram, "model");
//		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
//
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//	}
//	glBindVertexArray(0);
//}
//
//void Demo::DrawColoredCubee()
//{
//	UseShader(shaderProgram);
//
//	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//
//	GLint objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
//	glUniform3f(objectColorLoc, 0.0f, 0.0f, 0.0f);
//
//	glm::mat4 model;
//	model = glm::translate(model, glm::vec3(1, 0, 0));
//	//model = glm::rotate(model,angle, glm::vec3(0, 1, 0));
//	model = glm::scale(model, glm::vec3(0.7, 1.1, 0.5));
//
//	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
//	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//
//	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//	glBindTexture(GL_TEXTURE_2D, 0);
//	//kaki
//	for (int i = 0;i < 4;i++) {
//		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
//		glUniform3f(objectColorLoc, 1.0f, 0.5f, 0.0f);
//
//		glm::mat4 model2;
//		model2 = glm::translate(model2, glm::vec3(1, 0.5 + i * 0.2, 0));
//		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
//		model2 = glm::scale(model2, glm::vec3(0.7, 0.2, 0.5));
//
//		glGetUniformLocation(this->shaderProgram, "model");
//		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
//
//		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
//	}
//	//lengan
//	//tangan
//
//	glBindVertexArray(0);
//}

void Demo::DrawBuilding()
{
	UseShader(shaderProgram);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	GLint objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
	glUniform3f(objectColorLoc, 135.0 / 255.0f, 206.0 / 255.0f, 250.0 / 255.0f);

	//bikin jendela 1
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(2,2.5,0));
	//model = glm::rotate(model,angle, glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(0, 0.5, 0.5));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	//bangunan kanan
	for (int i = 0;i < 4;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 160.0/255.0f, 82.0/255.0f, 45.0/255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(3, 0.5+ i * 0.2, 0));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(2, 4, 2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//jendela 2
	for (int i = 0;i < 3;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 135.0/255.0f, 206.0/255.0f, 250.0/255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(1.8, 0.9 + i * 0.6, 1));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0, 0.5, 0.5));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//BALKON
	for (int i = 0;i < 3;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 240.0/255.0f, 230.0/255.0f, 140.0/255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(2.7, 1 + i * 0.9, 2.2));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(1.8, 0.4, 0.3));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//ATAP
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 189.0/255.0f, 183.0/255.0f, 107.0/255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(3, 3.2, 0));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(2, 0.2, 2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//cerobong
	for (int i = 0;i < 3;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 255.0/255.0f, 228.0/255.0f, 181.0/255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(3.3 - i * 0.4, 3.4, 1));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.1, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//bangunan kiri
	for (int i = 0;i < 4;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 32.0/255.0f, 178.0/255.0f, 170.0/255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-3, 0.5 + i * 0.2, 0.5));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(2.5, 4.5, 3));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//Balkon
	for (int i = 0;i < 3;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 1.0f, 1.0f, 1.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-3, 0.8 + i * 1, 0.5));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(2.7, 0.4, 3.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//ATAP
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0 / 255.0f, 250.0 / 255.0f, 154.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-3, 3.4, 0.5));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(2.5, 0.2, 3));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//Jendela
	for (int i = 0;i < 5;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0 / 255.0f, 191.0 / 255.0f, 255.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-2 -i * 0.4, 1.7, 3));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.2, 0));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//Jendela
	for (int i = 0;i < 5;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0 / 255.0f, 191.0 / 255.0f, 255.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-2 - i * 0.4, 2.5, 3));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.2, 0));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//tembok bawah
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 169.0 / 255.0f, 169.0 / 255.0f, 169.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-3, -0.4, 0.5));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(2.6, 1, 3.1));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	
	//RUMPUT
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0f, 1.0f, 0.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-5, -0.4, -0.2));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(20, 0, 17));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
}

void Demo::DrawBuildingPutih()
{
	UseShader(shaderProgram);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	GLint objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
	glUniform3f(objectColorLoc, 1.0f, 1.0f, 1.0f);

	
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(4, 1, 4));
	//model = glm::rotate(model,angle, glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(1.5, 3, 1.5));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//RUMPUT
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0f, 1.0f, 0.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(5, -0.2 , 0));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(20, 0, 17));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//ATAP
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.8f, 0.8f, 0.8f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(4, 2.6, 4));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(1.5, 0.2, 1.5));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//cerobong
	for (int i = 0;i < 2;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.9f, 0.9f, 0.9f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(4.2 - i * 0.4, 2.8, 4.4));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.1, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	//JENDELA
	for (int i = 0;i < 3;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0f, 1.0f, 0.9f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(3, 2, 5-i *0.4));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0, 1, 0.3));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	//JENDELA
	for (int i = 0;i < 3;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0f, 1.0f, 0.9f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(4.1 - i * 0.4, 2, 5.2));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.3, 1, 0));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	//JENDELA
	for (int i = 0;i < 3;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0f, 1.0f, 0.9f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(4.1 - i * 0.4, 1 - i * 0.2, 5.2));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.2, 0));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}

void Demo::DrawBuildingBelakang()
{
	UseShader(shaderProgram);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	GLint objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
	glUniform3f(objectColorLoc, 101.0/255.0f, 67.0/255.0f, 33.0/255.0f);


	glm::mat4 model;
	model = glm::translate(model, glm::vec3(-8, 1, -2));
	//model = glm::rotate(model,angle, glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(2.5, 4, 2.5));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//ATAP
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 150.0/255.0f, 75.0/255.0f, 0.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-8, 3, -2));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(2.5, 0.2, 2.5));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//cerobong
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 240.0 / 255.0f, 230.0 / 255.0f, 140.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-7, 3.2, -1.5));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.1, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//JENDELA
	for (int i = 0;i < 5;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0f, 1.0f, 0.9f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-6.7 - i * 0.4, 2.5, 0));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.3, 1, 0));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//JENDELA
	for (int i = 0;i < 4;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0f, 1.0f, 0.9f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-6.8 - i * 0.5, 1.2, 0));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.4, 0.4, 0));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//JENDELA
	for (int i = 0;i < 5;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0f, 1.0f, 0.9f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-6, 2.5, 0.4 - i * 0.4));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0, 1, 0.3));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//JENDELA
	for (int i = 0;i < 4;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0f, 1.0f, 0.9f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-6, 1.2, 0.3 - i * 0.5));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0, 0.4, 0.4));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
}

void Demo::DrawBuildingDepan()
{
	UseShader(shaderProgram);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	GLint objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
	glUniform3f(objectColorLoc, 240.0 / 255.0f, 230.0 / 255.0f, 140.0 / 255.0f);


	glm::mat4 model;
	model = glm::translate(model, glm::vec3(-3, 1, 6));
	//model = glm::rotate(model,angle, glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(1, 2, 1.5));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//BANGUNAN
	for (int i = 0;i < 2;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 255.0 / 255.0f, 140.0 / 255.0f, 0.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-3, 0.8, 7 - i * 2.2));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.8, 1.5, 1));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//ATAP
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 255.0 / 255.0f, 140.0 / 255.0f, 0.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-3, 2.1, 6));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(1, 0.2, 1.5));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//ATAP
	for (int i = 0;i < 2;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 220.0/255.0f, 20.0/255.0f, 60.0/255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-3, 1.6, 7 - i * 2.2));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.8, 0.2, 1));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//JENDELA
	for (int i = 0;i < 2;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0f, 1.0f, 0.9f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-2.5, 1, 7.3 - i * 2.2));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0, 0.4, 0.6));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//JENDELA
	for (int i = 0;i < 2;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0f, 1.0f, 0.9f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-2.8 - i * 0.3, 1, 7.6));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.2, 0));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//PINTU
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 220.0 / 255.0f, 20.0 / 255.0f, 60.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-2.3, 0.7, 6.4));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0, 0.6, 0.4));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//BANGUNAN KANAN
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 178.0 / 255.0f, 34.0 / 255.0f, 34.0/255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(3, 0.8, 7));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.8, 2, 1.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 233.0 / 255.0f, 150.0 / 255.0f, 122.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(2.7, 0.2, 7));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.8, 1.6, 0.8));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//ATAP
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 205.0/255.0f, 92.0/255.0f, 92.0/255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(2.7, 1.1, 7));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.8, 0.2, 0.8));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//ATAP
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 255.0 / 255.0f, 160.0 / 255.0f, 122.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(3, 1.9, 7));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.8, 0.2, 1.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//PINTU
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 255.0 / 255.0f, 69.0 / 255.0f, 0.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(2.3, 0.2, 7));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.01, 0.8, 0.4));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//JENDELA
	for (int i = 0;i < 2;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0f, 1.0f, 0.9f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(2.9 - i * 0.3, 1.5, 8));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.9, 0));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//JENDELA
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0f, 1.0f, 0.9f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(2.4, 1.8, 7.4));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0, 0.2, 0.9));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);
}

void Demo::DrawTree()
{
	UseShader(shaderProgram);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	GLint objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
	glUniform3f(objectColorLoc, 1.0f, 0.4f, 0.0f);

	//bikin batang
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(1.8, 0, 3));
	//model = glm::rotate(model,angle, glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(0.2, 1.4, 0.2));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(1.8, 0.6 + i * 0.2, 3));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.8, 0.2, 0.6));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(1.8, 0.8 + i * 0.2, 3));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.6, 0.2, 0.4));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(1.8, 0.9 + i * 0.2, 3));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.4, 0.2, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(1.8, 1 + i * 0.2, 3));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.2, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//batang kanan depan
	for (int i = 0;i < 4;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 1.0f, 0.4f, 0.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(1.8, 0.1 +i * 0.2, 6));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.4, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(1.8, 0.8 + i * 0.2, 6));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.8, 0.2, 0.6));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(1.8, 0.9 + i * 0.2, 6));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.6, 0.2, 0.4));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(1.8, 1 + i * 0.2, 6));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.4, 0.2, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(1.8, 1.1 + i * 0.2, 6));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.2, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//batang kiri
	for (int i = 0;i < 4;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 1.0f, 0.4f, 0.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-0.9, 0.6 + i * 0.2, -1));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.4, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-0.9, 1.2 + i * 0.2, -1));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.8, 0.2, 0.6));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-0.9, 1.4 + i * 0.2, -1));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.6, 0.2, 0.4));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-0.9, 1.6 + i * 0.2, -1));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.4, 0.2, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-0.9, 1.7 + i * 0.2, -1));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.2, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//batang depan
	for (int i = 0;i < 4;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 1.0f, 0.4f, 0.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-1, 0.6 + i * 0.2, 4.8));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.4, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-1, 1.2 + i * 0.2, 4.8));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.8, 0.2, 0.6));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-1, 1.4 + i * 0.2, 4.8));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.6, 0.2, 0.4));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-1, 1.6 + i * 0.2, 4.8));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.4, 0.2, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-1, 1.7 + i * 0.2, 4.8));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.2, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//batang paling depan
	for (int i = 0;i < 4;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 1.0f, 0.4f, 0.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-1, 0.6 + i * 0.2, 8));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.4, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-1, 1.2 + i * 0.2, 8));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.8, 0.2, 0.6));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-1, 1.4 + i * 0.2, 8));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.6, 0.2, 0.4));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-1, 1.6 + i * 0.2, 8));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.4, 0.2, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//daun
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 107.0 / 255.0f, 142.0 / 255.0f, 35.0 / 255.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-1, 1.7 + i * 0.2, 8));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.2, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
}

void Demo::DrawStreet()
{
	UseShader(shaderProgram);

	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	GLint objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
	glUniform3f(objectColorLoc, 0.0f, 0.0f, 0.0f);

	
	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.2, 0, 1));
	//model = glm::rotate(model,angle, glm::vec3(0, 1, 0));
	model = glm::scale(model, glm::vec3(1.8, 0.1, 20));

	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glBindTexture(GL_TEXTURE_2D, 0);

	//garis
	for (int i = 0;i < 14;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 255.0/255.0f, 215.0/255.0f, 0.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(0.2, 0.6, 8-i));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.1, 0, 0.6));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//garis
	for (int i = 0;i < 40;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 255.0 / 255.0f, 215.0 / 255.0f, 0.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(14 - i * 0.7, 0.6, -5.5));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.6, 0, 0.2));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//jalan horizontal
	for (int i = 0;i < 1;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 0.0f, 0.0f, 0.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(0.2, 0, -7));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(30, 1.3, 0.1));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//penyebrangan kiri
	for (int i = 0;i < 3;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 1.0f, 1.0f, 1.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(-1.4, 0.6, - 4.5 - i));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.6, 0, 0.3));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//penyebrangan kanan
	for (int i = 0;i < 3;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 1.0f, 1.0f, 1.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(2.2, 0.6, -4.5 - i));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.6, 0, 0.3));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}
	//penyebrangan belakang
	for (int i = 0;i < 4;i++) {
		objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
		glUniform3f(objectColorLoc, 1.0f, 1.0f, 1.0f);

		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(0.8 - i * 0.4, 0, -2.5));
		//model2 = glm::rotate(model2, angle, glm::vec3(0, 1, 0));
		model2 = glm::scale(model2, glm::vec3(0.2, 0.8, 0));

		glGetUniformLocation(this->shaderProgram, "model");
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);
}

void Demo::BuildColoredPlane()
{
	// Build geometry
	GLfloat vertices[] = {
		// format position, tex coords
		// bottom
		-50.0, -0.5, -50.0,  0.0f,  1.0f,  0.0f,
		 50.0, -0.5, -50.0,  0.0f,  1.0f,  0.0f,
		 50.0, -0.5,  50.0,  0.0f,  1.0f,  0.0f,
		-50.0, -0.5,  50.0,  0.0f,  1.0f,  0.0f,


	};

	GLuint indices[] = { 0,  2,  1,  0,  3,  2 };

	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);

	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO
}

void Demo::DrawColoredPlane()
{
	UseShader(shaderProgram);

	glBindVertexArray(VAO2); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

	GLint objectColorLoc = glGetUniformLocation(this->shaderProgram, "objectColor");
	glUniform3f(objectColorLoc, 0.0/255.0f, 255.0/255.0f, 255.0/255.0f);

	glm::mat4 model; 
	GLint modelLoc = glGetUniformLocation(this->shaderProgram, "model");
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

int main(int argc, char** argv) {
	RenderEngine &app = Demo();
	app.Start("Basic Lighting: Phong Lighting Model", 800, 600, false, false);
}