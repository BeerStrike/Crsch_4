#include "SubObject.h"

SubObject::SubObject(std::vector<glm::vec3>* points, std::vector<glm::vec2>* textures, std::vector<glm::vec3>* normals,Material *mtr) {
	coords_vbo = 0;
	normals_vbo = 0;
	tex_vbo = 0;
	vao = 0;
	material = mtr;
	vertex_num = points->size();
	glGenBuffers(1, &coords_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
	glBufferData(GL_ARRAY_BUFFER, points->size() * sizeof(glm::vec3), &(points->at(0)), GL_STATIC_DRAW);
	glGenBuffers(1, &tex_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
	glBufferData(GL_ARRAY_BUFFER, textures->size() * sizeof(glm::vec2), &(textures->at(0)), GL_STATIC_DRAW);
	glGenBuffers(1, &normals_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	glBufferData(GL_ARRAY_BUFFER, normals->size() * sizeof(glm::vec3), &(normals->at(0)), GL_STATIC_DRAW);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, coords_vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, normals_vbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	glBindBuffer(GL_ARRAY_BUFFER, tex_vbo);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}

void SubObject::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model, glm::vec3 campos, LightsInfo lights, GLuint shader_programme) {
	glUseProgram(shader_programme);
	GLuint u = glGetUniformLocation(shader_programme, "projection");
	glUniformMatrix4fv(u, 1, GL_FALSE, &projection[0][0]);
	u = glGetUniformLocation(shader_programme, "view");
	glUniformMatrix4fv(u, 1, GL_FALSE, &view[0][0]);
	u = glGetUniformLocation(shader_programme, "model");
	glUniformMatrix4fv(u, 1, GL_FALSE, &model[0][0]);
	u = glGetUniformLocation(shader_programme, "material.haveTexture");
	glUniform1i(u, material->haveTexture);
	u = glGetUniformLocation(shader_programme, "material.shininess");
	glUniform1f(u, material->shininess);
	u = glGetUniformLocation(shader_programme, "material.ambient");
	glUniform3fv(u, 1, &(material->ambient[0]));
	u = glGetUniformLocation(shader_programme, "material.diffuse");
	glUniform3fv(u, 1, &(material->diffuse[0]));
	u = glGetUniformLocation(shader_programme, "material.specular");
	glUniform3fv(u, 1, &(material->specular[0]));
	u = glGetUniformLocation(shader_programme, "lights.numPLights");
	glUniform1i(u, lights.numPLights);
	u = glGetUniformLocation(shader_programme, "lights.numSLights");
	glUniform1i(u, lights.numSLights);
	for (int i = 0; i < lights.numPLights; i++) {
		std::string s = "lights.pointLights[" + std::to_string(i) + "].constant";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform1f(u, lights.pointLights[i].constant);
		s = "lights.pointLights[" + std::to_string(i) + "].linear";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform1f(u, lights.pointLights[i].linear);
		s = "lights.pointLights[" + std::to_string(i) + "].quadratic";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform1f(u, lights.pointLights[i].quadratic);
		s = "lights.pointLights[" + std::to_string(i) + "].position";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform3fv(u, 1, &(lights.pointLights[i].position[0]));
		s = "lights.pointLights[" + std::to_string(i) + "].ambient";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform3fv(u, 1, &(lights.pointLights[i].ambient[0]));
		s = "lights.pointLights[" + std::to_string(i) + "].diffuse";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform3fv(u, 1, &(lights.pointLights[i].diffuse[0]));
		s = "lights.pointLights[" + std::to_string(i) + "].specular";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform3fv(u, 1, &(lights.pointLights[i].specular[0]));
	}
	for (int i = 0; i < lights.numSLights; i++) {
		std::string s = "lights.spotLights[" + std::to_string(i) + "].constant";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform1f(u, lights.spotLights[i].constant);
		s = "lights.spotLights[" + std::to_string(i) + "].linear";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform1f(u, lights.spotLights[i].linear);
		s = "lights.spotLights[" + std::to_string(i) + "].quadratic";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform1f(u, lights.spotLights[i].quadratic);
		s = "lights.spotLights[" + std::to_string(i) + "].cutOff";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform1f(u, lights.spotLights[i].cutOff);
		s = "lights.spotLights[" + std::to_string(i) + "].outerCutOff";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform1f(u, lights.spotLights[i].outerCutOff);
		s = "lights.spotLights[" + std::to_string(i) + "].position";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform3fv(u, 1, &(lights.spotLights[i].position[0]));
		s = "lights.spotLights[" + std::to_string(i) + "].ambient";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform3fv(u, 1, &(lights.spotLights[i].ambient[0]));
		s = "lights.spotLights[" + std::to_string(i) + "].diffuse";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform3fv(u, 1, &(lights.spotLights[i].diffuse[0]));
		s = "lights.spotLights[" + std::to_string(i) + "].specular";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform3fv(u, 1, &(lights.spotLights[i].specular[0]));
		s = "lights.spotLights[" + std::to_string(i) + "].direction";
		u = glGetUniformLocation(shader_programme, s.c_str());
		glUniform3fv(u, 1, &(lights.spotLights[i].direction[0]));
	}
	u = glGetUniformLocation(shader_programme, "lights.dirLight.ambient");
	glUniform3fv(u, 1, &(lights.dirLight.ambient[0]));
	u = glGetUniformLocation(shader_programme, "lights.dirLight.diffuse");
	glUniform3fv(u, 1, &(lights.dirLight.diffuse[0]));
	u = glGetUniformLocation(shader_programme, "lights.dirLight.specular");
	glUniform3fv(u, 1, &(lights.dirLight.specular[0]));
	u = glGetUniformLocation(shader_programme, "lights.dirLight.direction");
	glUniform3fv(u, 1, &(lights.dirLight.direction[0]));
	u = glGetUniformLocation(shader_programme, "campos");
	glUniform3fv(u, 1, &(campos[0]));
	glBindVertexArray(vao);
	if (material->haveTexture) {	
		GLuint mtx = glGetUniformLocation(shader_programme, "material.texture");
		glUniform1i(mtx, 0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, material->texture);
	}
	glDrawArrays(GL_TRIANGLES, 0, vertex_num);
}

SubObject::~SubObject(){
	glDeleteBuffers(1, &coords_vbo);
	glDeleteBuffers(1, &normals_vbo);
	glDeleteBuffers(1, &tex_vbo);
	glDeleteVertexArrays(1, &vao);
}

