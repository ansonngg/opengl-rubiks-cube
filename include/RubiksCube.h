#ifndef RUBIKS_CUBE_H
#define RUBIKS_CUBE_H

#include <vector>

#include "Shader.h"
#include "Texture.h"

class RubiksCube {
public:
	enum class Rotate {
		X, Y, Z, XP, YP, ZP
	};

	enum class Move {
		F, B, U, D, L, R, M, E, S, F2, B2, U2, D2, L2, R2,
		FP, BP, UP, DP, LP, RP, MP, EP, SP, F2P, B2P, U2P, D2P, L2P, R2P
	};

	RubiksCube(float rotateTime);
	void Initialize();
	void Paint(Shader shader, const glm::mat4 &vpMatrix);
	bool RotateCube(Rotate rotate);
	bool MoveLayer(Move move);

private:
	const std::vector<int> LAYERS_INDICES[15];

	float rotateTime;
	GLuint vao, vbo, ebo;
	Texture textures[27];
	glm::mat4 transMatrices[27];
	glm::mat4 tempTransMatrices[27];
	int cubeIndices[27];
	bool rotating;

	void Model();
	float GetAngleAndAxis(Rotate rotate, glm::vec3 &axis);
	float GetAngleAndAxis(Move move, glm::vec3 &axis);
	void MoveIndices(Rotate rotate);
	void MoveIndices(Move move);
	void RotateOnX(int *arr);
	void RotateOnY(int *arr);
	void RotateOnZ(int *arr);
	void RotateOnXP(int *arr);
	void RotateOnYP(int *arr);
	void RotateOnZP(int *arr);
	void RoundMat4(glm::mat4 &matrix);
};

#endif // RUBIKS_CUBE_H
