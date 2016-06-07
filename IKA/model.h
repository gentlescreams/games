#ifndef MODEL_H_
#define MODEL_H_
#include"glm\glm.hpp"
#include"util.h"

typedef struct
{
	unsigned int x, y, z;
}uivec3;



class Model
{
public:
	Model() {}
	Model(const char *file_name);
	
	~Model() {}
	void Draw(GLuint id);

private:

	unsigned int nVertices;
	unsigned int iFaces;
	unsigned int nTex;
	glm::vec3 *nomals;
	glm::vec3 *vetices;
	uivec3 *faces;
	glm::vec2 *tex;
};



#endif MODEL_H_
