#pragma once
#include "AppFrame.h"
class Shader {
public:
	void LoadVsShader(const TCHAR* filename);
	void LoadPsShader(const TCHAR* filename);
    void SetShader();
	void MakeVertex(VECTOR pos, COLOR_U8 dif, float u, float v);
	void Init(const TCHAR*txfilename, const TCHAR* vsfilename, const TCHAR* psfilename);
	void Draw(int polygonnum);
private:
	int vshandle;
	int pshandle;
	int grhandle;
	std::vector<VERTEX3DSHADER> VertBuffer;


};
