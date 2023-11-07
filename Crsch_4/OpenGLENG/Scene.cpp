#include "Scene.h"
#include "ShaderFuncs.h"
#include "Primitives.h"
namespace OpenGLENG {
    void OpenGLENG::Scene::draw(int WinWidth,int WinHeight)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        glUseProgram(shader_programme);
        for (int i = 0; i < objects.size();i++) {
            glm::mat4 prsp = glm::perspective(glm::radians(fov), (float)WinWidth / WinHeight,bfc, bhc);
            glm::vec3 cameraDir = { 1.0f*cos(0)*cos(cameraPitch),1.0f * sin(cameraPitch),1.0 * sin(0) * cos(cameraPitch) };
            glm::mat4 cam = glm::lookAt(cameraPos, cameraPos+cameraDir, glm::vec3(0.0f, 1.0f, 0.0f));
            objects[i]->draw(prsp, cam, objectTrf[i],lights,cameraPos, shader_programme);
        }
    }
    OpenGLENG::Scene::Scene()
    {
        vs = LoadShader("OpenGLENG/VertexShader.glsl", GL_VERTEX_SHADER);
        fs = LoadShader("OpenGLENG/FragmentShader.glsl", GL_FRAGMENT_SHADER);
        shader_programme = glCreateProgram();
        glAttachShader(shader_programme, vs);
        glAttachShader(shader_programme, fs);
        glBindAttribLocation(shader_programme, 0, "vertex_position");
        glBindAttribLocation(shader_programme, 1, "vertex_colour");
        glLinkProgram(shader_programme);
        cameraPos = { 0.0f,0.0f,0.0f };
        cameraYaw = 0;
        cameraPitch = 0;
        fov = 30.0f;
        bfc = 0.01f;
        bhc = 100.0f;
        //OpenGLENG::Object* pl = OpenGLENG::Object::LoadFromOBJ("P.obj");
        std::vector<GLuint> indices = { 0,1,2,3 };
        std::vector<glm::vec3> points = { { 0.0f,1.0f,-0.8f },
            { 0.0f,1.0f,0.8f },
            { 0.0f,-1.0f,-1.0f },
            { 0.0f,-1.0f,1.0f },
        };
        std::vector<glm::vec2> textures = { { 0.0f,0.0f},
            { 1.0f,0.0f },
            { 0.0f,1.0f },
            { 1.0f,1.0f },
        };
        std::vector<glm::vec3> normals = { { 1.0f,0.0f,0.0f },
            { 1.0f,0.0f,0.0f },
            { 1.0f,0.0f,0.0f },
            { 1.0f,0.0f,0.0f },
        };
        Material material;
     
        material.shininess = 0.5f;
        Object* o = new Object(indices, points, textures, normals, material, "kv.jpg","x.jpg");
        objects.push_back(o);
        glm::mat4 trm = glm::mat4(1.0f);
        trm = glm::translate(trm, { 4.0f,0.0f,0.0f });
        objectTrf.push_back(trm);
        lights.numPLights =0;
        lights.numSLights =0;
        lights.dirLight.ambient = { 0.8f,0.8f,0.8f };
        lights.dirLight.diffuse = { 0.8f,0.8f,0.8f };
        lights.dirLight.direction = { 1.0f,0.0f,0.0f };
        lights.dirLight.specular = { 0.2f,0.2f,0.2f };
    }

    OpenGLENG::Scene::~Scene()
    {
        for (Object* o : objects)
            delete o;
        glDeleteShader(vs);
        glDeleteShader(fs);
        glDeleteShader(shader_programme);
    }
    void Scene::moveCam(glm::vec3 mv){
        glm::vec3 mvv = {mv.z * cos(cameraYaw) * cos(cameraPitch),mv.z * sin(cameraPitch),mv.z * sin(cameraYaw) * cos(cameraPitch) };
        cameraPos += mvv;
        mvv = { mv.x * sin(cameraYaw) * cos(cameraPitch),mv.x * sin(cameraPitch),mv.x * cos(cameraYaw) * cos(cameraPitch) };
        cameraPos += mvv;
    }
    void Scene::rotateCam(GLfloat yaw, GLfloat pitch) {
        objectTrf[0] = glm::rotate(objectTrf[0], glm::radians(cameraYaw), glm::vec3(0.0, 1.0, 0.0));
        //objectTrf[0] = glm::rotate(objectTrf[0], glm::vec3(0, yaw, 0));
        cameraYaw += yaw;
        //cameraPitch += pitch;
    }
}
