#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION

#include "BaseObject.h"

void BaseObject::LoadFromOBJ(std::string filename, std::vector<SubObject*>* so, std::vector<Material>* mtrs) {

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string warn;
	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str(), NULL, true);
	//if (!ret)
		//TODO: обработать
 	for (int i = 0; i < materials.size(); i++) {
		Material nwmtr;
		nwmtr.shininess = materials[i].shininess;
		nwmtr.ambient = { materials[i].ambient[0], materials[i].ambient[1], materials[i].ambient[2] };
		nwmtr.diffuse = { materials[i].diffuse[0], materials[i].diffuse[1], materials[i].diffuse[2] };
		nwmtr.specular = { materials[i].specular[0], materials[i].specular[1], materials[i].specular[2] };
		if (materials[i].ambient_texname == "") {
			if(materials[i].diffuse_texname == "")
				nwmtr.haveTexture = false;
			else {
				nwmtr.haveTexture = true;
				int texWigth, texHeight, nrChannel;
				unsigned char* data = stbi_load(materials[i].diffuse_texname.c_str(), &texWigth, &texHeight, &nrChannel, STBI_default);
				//if (!data)
					//TODO: обработать
				glGenTextures(1, &nwmtr.texture);
				glBindTexture(GL_TEXTURE_2D, nwmtr.texture);
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWigth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				glGenerateMipmap(GL_TEXTURE_2D);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
				delete data;
			}
		}
		else {
			nwmtr.haveTexture = true;
			int texWigth, texHeight, nrChannel;
			unsigned char* data = stbi_load(materials[i].ambient_texname.c_str() , &texWigth, &texHeight, &nrChannel, STBI_default);
			//if (!data)
				//TODO: обработать
			glGenTextures(1, &nwmtr.texture);
			glBindTexture(GL_TEXTURE_2D, nwmtr.texture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWigth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			delete data;
		}

		mtrs->push_back(nwmtr);
	}
	for (int j = 0; j < shapes.size(); j++) {
		int mid = shapes[j].mesh.material_ids[0];
		std::vector<glm::vec3> p;
		std::vector<glm::vec2> t;
		std::vector<glm::vec3> n;
		for (int i = 0; i < shapes[j].mesh.indices.size(); i++) {
			if (shapes[j].mesh.material_ids[i/3] == mid) {
				p.push_back({ attrib.vertices[shapes[j].mesh.indices[i].vertex_index * 3] ,
					attrib.vertices[shapes[j].mesh.indices[i].vertex_index * 3 + 1],
					attrib.vertices[shapes[j].mesh.indices[i].vertex_index * 3 + 2]
					});
				t.push_back({ attrib.texcoords[shapes[j].mesh.indices[i].texcoord_index * 2] ,
					1 - attrib.texcoords[shapes[j].mesh.indices[i].texcoord_index * 2 + 1],
					});
				n.push_back({ attrib.normals[shapes[j].mesh.indices[i].normal_index * 3] ,
					attrib.normals[shapes[j].mesh.indices[i].normal_index * 3 + 1],
					attrib.normals[shapes[j].mesh.indices[i].normal_index * 3 + 2]
					});
			} else {
				so->push_back(new SubObject(&p, &t, &n, &(mtrs->at(mid))));
				mid = shapes[j].mesh.material_ids[i/3];
				i--;
			}
		}
		so->push_back(new SubObject(&p, &t, &n, &(mtrs->at(mid))));
	}
}

void BaseObject::draw(glm::mat4 projection, glm::mat4 view, glm::vec3 campos, LightsInfo lights, GLuint shader_programme){
	for (int i = 0; i < subObjects->size(); i++)
		subObjects->at(i)->draw(projection,view,mytrf,campos,lights,shader_programme);
}

glm::vec3 BaseObject::getPos()
{
	return mypos;
}

BaseObject::~BaseObject(){
}
