#include "shader.h"



void Shader::LoadVsShader(const TCHAR* filename) {
	vshandle = LoadVertexShader(filename);
}

void Shader::LoadPsShader(const TCHAR* filename) {
	pshandle = LoadPixelShader(filename);
}

void Shader::SetShader() {
	SetUseTextureToShader(0,grhandle);
	SetUseVertexShader(vshandle);
    SetUsePixelShader(pshandle);
}

void Shader::MakeVertex(VECTOR pos,COLOR_U8 dif,float u,float v) {
	VERTEX3DSHADER vert;
	vert.pos = pos;
	vert.dif = dif;
	vert.u = u;
	vert.v = v;
	
	VertBuffer.push_back(vert);

}

void Shader::Init(const TCHAR* txfilename, const TCHAR* vsfilename, const TCHAR* psfilename) {
	LoadGraph(txfilename);
	LoadVsShader(vsfilename);
	LoadPsShader(psfilename);
	
}

void Shader::Draw(int polygonnum) {
	DrawPolygon3DToShader(VertBuffer.data(), polygonnum);
}