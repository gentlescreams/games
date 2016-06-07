#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#include"glut.h"
#include "model.h"


Model::Model(const char *file_name)//初期化
{
	nVertices = 0;
	iFaces = 0;
	nTex = 0;

	char buf[256];

	FILE *pFile = fopen(
		file_name,
		"r");
	assert(pFile != NULL);

	while (fscanf(pFile, "%s", buf) > 0)
	{

		if (strcmp(buf, "Mesh") == 0)
		{

			fscanf(pFile, "%*2s");
			fscanf(pFile, "%u", &nVertices);
			printf("nVertices %u\n", nVertices);
			fscanf(pFile, "%*1s");
			//頂点のメモリ確保
			vetices = (glm::vec3*)malloc(sizeof(glm::vec3) * nVertices);//頂点1個×頂点数

			for (int i = 0; i < nVertices; i++)
			{
				// 100/6000: 1.00, 1.00, 1.000
				fscanf(pFile, "%f", &vetices[i].x);
				fscanf(pFile, "%*1s");
				fscanf(pFile, "%f", &vetices[i].y);
				fscanf(pFile, "%*1s");
				fscanf(pFile, "%f", &vetices[i].z);
				fscanf(pFile, "%*2s");



			}


			//インデックス配列

			fscanf(pFile, "%u", &iFaces);
			printf("iFaces:%u\n", iFaces);
			fscanf(pFile, "%*1s");
			faces = (uivec3*)malloc(sizeof(uivec3)* iFaces);

			for (int i = 0; i < iFaces; i++)
			{
				fscanf(pFile, "%*2s");
				fscanf(pFile, "%u", &faces[i].x);
				fscanf(pFile, "%*1s");
				fscanf(pFile, "%u", &faces[i].y);
				fscanf(pFile, "%*1s");
				fscanf(pFile, "%u", &faces[i].z);
				fscanf(pFile, "%*2s");
			}
			//面の法線のバッファ
			glm::vec3 *faceNormals;
			faceNormals = new glm::vec3[iFaces];

			nomals = new glm::vec3[nVertices];
			//面の数だけ回す
			for (int i = 0; i < iFaces; i++)
			{
				//面の何番めの
				glm::vec3 v0 = vetices[faces[i].x];
				glm::vec3 v1 = vetices[faces[i].y];
				glm::vec3 v2 = vetices[faces[i].z];

				//ベクトルの計算
				glm::vec3 v01 = v1 - v0;
				glm::vec3 v02 = v2 - v0;

				//法線の計算
				glm::vec3 n = cross(v01, v02);
				n = normalize(n);//正規化
								 //法線をいれる
				faceNormals[i] = n;

				nomals[faces[i].x] = n;
				nomals[faces[i].y] = n;
				nomals[faces[i].z] = n;

			}


		}
		if (strcmp(buf, "MeshTextureCoords") == 0)
		{
			fscanf(pFile, "%*1s");
			fscanf(pFile, "%u", &nTex);
			printf("tex :%u\n", nTex);
			fscanf(pFile, "%*1s");

			tex = (glm::vec2*)malloc(sizeof(glm::vec2)*nTex);

			for (int i = 0; i < nTex; i++)
			{
				fscanf(pFile, "%f", &tex[i].x);
				fscanf(pFile, "%*1s");
				fscanf(pFile, "%f", &tex[i].y);
				fscanf(pFile, "%*2s");
			}

		}

	}

}

void Model::Draw(GLuint id) {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,id);

	glEnableClientState(GL_VERTEX_ARRAY);	// GLenum array
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(
		2,			//GLint size, ,
		GL_FLOAT,	// GLenum type
		0,			//GLsizei stride,
		tex);			//const GLvoid *pointer)

	glVertexPointer(
		3,          // GLint size
		GL_FLOAT,   // GLenum type
		0,          // GLsizei stride
		vetices);         // const GLvoid *pointer

	glNormalPointer(
		GL_FLOAT,
		0,
		(float*)nomals);


	glDrawArrays(
		GL_POINTS,   // GLenum mode
		0,              // GLint first
		nVertices);             // GLsizei count

	glDrawElements(
		GL_TRIANGLES,       // glenum mode
		iFaces * 3,                  // glsizei count
		GL_UNSIGNED_INT,   // glenum type
		faces);           // const glvoid *indices
	glDisable(GL_TEXTURE_2D);
}

