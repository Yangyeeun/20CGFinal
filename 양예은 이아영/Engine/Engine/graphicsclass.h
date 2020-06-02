////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "lightshaderclass.h"
#include "lightclass.h"
#include "textclass.h"


/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	void Shutdown();
	bool Frame(int, int, float);
	void MovingCamera(int, float);
	int PolygonUsed();//¾Æ¿µ

private:
	bool Render(float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;

	/*Models*/
	ModelClass* m_DogBodyModel;
	ModelClass* m_DogHeadModel;
	ModelClass* m_FloorModel;
	ModelClass* m_BackWallModel;
	ModelClass* m_LeftWallModel;
	ModelClass* m_RightWallModel;
	ModelClass* m_BarColModel;
	ModelClass* m_BarRowModel;
	ModelClass* m_StageModel;
	ModelClass* m_TableModel;
	ModelClass* m_GirlModel;
	ModelClass* m_PianoModel;
	ModelClass* m_StoolModel;
	ModelClass* m_CoffeeGrinderModel;
	ModelClass* m_BookShelfModel;
	ModelClass* m_FrameModel;

	LightShaderClass* m_LightShader;
	LightClass* m_Light;
	TextClass* m_Text;

	int polygon_used;
};

#endif