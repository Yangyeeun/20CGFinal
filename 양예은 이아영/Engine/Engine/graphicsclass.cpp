////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include <math.h>


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;

	m_DogHeadModel = 0;
	m_DogBodyModel = 0;
	m_BackWallModel = 0;
	m_LeftWallModel = 0;
	m_RightWallModel = 0;
	m_BarColModel = 0;
	m_BarRowModel = 0;
	m_FloorModel = 0;
	m_StageModel = 0;
	m_TableModel = 0;
	m_PianoModel = 0;
	m_StoolModel = 0;
	m_CoffeeGrinderModel = 0;
	m_BookShelfModel = 0;

	m_LightShader = 0;
	m_Light = 0;
	m_Text = 0;

	polygon_used = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;
	D3DXMATRIX baseViewMatrix;



	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Initialize a base view matrix with the camera for 2D user interface rendering. 
	m_Camera->SetPosition(0.0f, 0.0f, -1.0f);
	m_Camera->Render();
	m_Camera->GetViewMatrix(baseViewMatrix);

	// Create the text object.
	m_Text = new TextClass;
	if (!m_Text)
	{
		return false;
	}

	// Initialize the text object. 
	result = m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), hwnd, screenWidth, screenHeight, baseViewMatrix);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the text object.", L"Error", MB_OK); return false;
	}


	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 20.0f, -50.0f);
	m_Camera->SetRotation(20.0f, 0.0f, 0.0f);
	

	// Girl

	// Create the model object.
	m_GirlModel = new ModelClass;
	if (!m_GirlModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_GirlModel->Initialize(m_D3D->GetDevice(), "../Engine/data/Girl.obj", L"../Engine/data/Girl.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the dog body model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_GirlModel->GetFaceCount();

	// 강아지 몸

	// Create the model object.
	m_DogBodyModel = new ModelClass;
	if(!m_DogBodyModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_DogBodyModel->Initialize(m_D3D->GetDevice(), "../Engine/data/DogBody.obj", L"../Engine/data/DogBody.png");
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the dog body model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_DogBodyModel->GetFaceCount();

	// 강아지 얼굴

	// Create the model object.
	m_DogHeadModel = new ModelClass;
	if (!m_DogHeadModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_DogHeadModel->Initialize(m_D3D->GetDevice(), "../Engine/data/DogHead.obj", L"../Engine/data/DogHead.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the dog head model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_DogHeadModel->GetFaceCount();

	// 바닥 모델

	// Create the model object.
	m_FloorModel = new ModelClass;
	if (!m_FloorModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_FloorModel->Initialize(m_D3D->GetDevice(), "../Engine/data/Floor.obj", L"../Engine/data/Floor.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the floor model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_FloorModel->GetFaceCount();

	// 벽 모델

	// Create the model object.
	m_BackWallModel = new ModelClass;
	if (!m_BackWallModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_BackWallModel->Initialize(m_D3D->GetDevice(), "../Engine/data/Wall.obj", L"../Engine/data/Wall.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the BackWall model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_BackWallModel->GetFaceCount();


	m_LeftWallModel = new ModelClass;
	if (!m_LeftWallModel)
	{
		return false;
	}
	// Initialize the model object.
	result = m_LeftWallModel->Initialize(m_D3D->GetDevice(), "../Engine/data/Wall.obj", L"../Engine/data/Wall.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the BackWall model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_LeftWallModel->GetFaceCount();

	m_RightWallModel = new ModelClass;
	if (!m_RightWallModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_RightWallModel->Initialize(m_D3D->GetDevice(), "../Engine/data/Wall.obj", L"../Engine/data/Wall.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the BackWall model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_RightWallModel->GetFaceCount();

	

	// 스테이지 모델

	// Create the model object.
	m_StageModel = new ModelClass;
	if (!m_StageModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_StageModel->Initialize(m_D3D->GetDevice(), "../Engine/data/Stage.obj", L"../Engine/data/Stage.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Stage model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_StageModel->GetFaceCount();

	// 바 모델

	// Create the model object.
	m_BarColModel = new ModelClass;
	if (!m_BarColModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_BarColModel->Initialize(m_D3D->GetDevice(), "../Engine/data/Stage.obj", L"../Engine/data/Stage.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Stage model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_BarColModel->GetFaceCount();

	
		// Create the model object.
	m_BarRowModel = new ModelClass;
	if (!m_BarRowModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_BarRowModel->Initialize(m_D3D->GetDevice(), "../Engine/data/Stage.obj", L"../Engine/data/Stage.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the Stage model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_BarRowModel->GetFaceCount();

	// 테이블

	// Create the model object.
	m_TableModel = new ModelClass;
	if (!m_TableModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_TableModel->Initialize(m_D3D->GetDevice(), "../Engine/data/Table.obj", L"../Engine/data/Table.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the dog head model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_TableModel->GetFaceCount();

	// Piano

	// Create the model object.
	m_PianoModel = new ModelClass;
	if (!m_PianoModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_PianoModel->Initialize(m_D3D->GetDevice(), "../Engine/data/Piano.obj", L"../Engine/data/Piano.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the dog body model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_PianoModel->GetFaceCount();

	// Stool

	// Create the model object.
	m_StoolModel = new ModelClass;
	if (!m_StoolModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_StoolModel->Initialize(m_D3D->GetDevice(), "../Engine/data/Stool.obj", L"../Engine/data/Stool.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the dog body model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_StoolModel->GetFaceCount();

	// 커피그라인더 모델

	// Create the model object.
	m_CoffeeGrinderModel = new ModelClass;
	if (!m_CoffeeGrinderModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_CoffeeGrinderModel->Initialize(m_D3D->GetDevice(), "../Engine/data/CoffeeGrinder.obj", L"../Engine/data/CoffeeGrinder.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the CoffeeGrinder model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_CoffeeGrinderModel->GetFaceCount();

	// 바 모델

	// Create the model object.
	m_BookShelfModel = new ModelClass;
	if (!m_BookShelfModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_BookShelfModel->Initialize(m_D3D->GetDevice(), "../Engine/data/BookShelf_.obj", L"../Engine/data/BookShelf.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the bookshelf model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_BookShelfModel->GetFaceCount();

	// Frame

	// Create the model object.
	m_FrameModel = new ModelClass;
	if (!m_FrameModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_FrameModel->Initialize(m_D3D->GetDevice(), "../Engine/data/Frame.obj", L"../Engine/data/Frame.png");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the dog body model object.", L"Error", MB_OK);
		return false;
	}

	polygon_used += m_FrameModel->GetFaceCount();

	//////////라이트
	// Create the light shader object.
	m_LightShader = new LightShaderClass;
	if(!m_LightShader)
	{
		return false;
	}

	// Initialize the light shader object.
	result = m_LightShader->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader object.", L"Error", MB_OK);
		return false;
	}


	// Create the light object.
	m_Light = new LightClass;
	if(!m_Light)
	{
		return false;
	}

	// Initialize the light object.
	m_Light->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_Light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetDirection(0.0f, -10.0f, 5.0f);
	m_Light->SetSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_Light->SetSpecularPower(16.0f);

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the light object.
	if(m_Light)
	{
		delete m_Light;
		m_Light = 0;
	}

	// Release the light shader object.
	if(m_LightShader)
	{
		m_LightShader->Shutdown();
		delete m_LightShader;
		m_LightShader = 0;
	}

	// Releasing Models

	// Release the model object.
	if(m_DogBodyModel)
	{
		m_DogBodyModel->Shutdown();
		delete m_DogBodyModel;
		m_DogBodyModel = 0;
	}
	// Release the model object.
	if (m_DogHeadModel)
	{
		m_DogHeadModel->Shutdown();
		delete m_DogHeadModel;
		m_DogHeadModel = 0;
	}

	// Release the text object.
	if (m_Text)
	{
		m_Text->Shutdown();
		delete m_Text;
		m_Text = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::Frame(int fps, int cpu, float frameTime)
{
	bool result;
	static float rotation = 0.0f;
	static bool rotation_direction = true;//위

	// Set the frames per second.
	result = m_Text->SetFps(fps, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	// Set the cpu usage.
	result = m_Text->SetCpu(cpu, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}

	
	
	// Set the polygon usage.
	result = m_Text->SetPolygon(polygon_used, m_D3D->GetDeviceContext());
	if (!result)
	{
		return false;
	}
	
	


	// Update the rotation variable each frame.
	if (rotation_direction == true)
	{
		rotation += (float)D3DX_PI * 0.002f;
		if (rotation > 0.1f)
		{
			rotation_direction = false;
		}
	}
	else if (rotation_direction == false)
	{
		rotation += (float)D3DX_PI * 0.002f*(-1);
		if (rotation < -0.1f)
		{
			rotation_direction = true;
		}
	}
	
	
	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}

void GraphicsClass::MovingCamera(int n, float rotation_y)
{
	float speed = 0.2f;
	D3DXMATRIX viewMatrix;
	if (n == 1)
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x+speed*m_Camera->GetMLookAt().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z+ speed * m_Camera->GetMLookAt().z);
	}
	else if (n == 2)
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x - speed * m_Camera->GetMLookAt().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z - speed * m_Camera->GetMLookAt().z);
	}
	else if (n == 3)
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x - speed * m_Camera->GetMLookAt().z, m_Camera->GetPosition().y, m_Camera->GetPosition().z + speed * m_Camera->GetMLookAt().x);
	}
	else if (n == 4)
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x + speed * m_Camera->GetMLookAt().z, m_Camera->GetPosition().y, m_Camera->GetPosition().z - speed * m_Camera->GetMLookAt().x);
	}
	else if (n == 5)
	{
		m_Camera->SetRotation(m_Camera->GetRotation().x, m_Camera->GetRotation().y-rotation_y, m_Camera->GetRotation().z);
	}
	else if (n == 6)
	{
		m_Camera->SetRotation(m_Camera->GetRotation().x, m_Camera->GetRotation().y+rotation_y, m_Camera->GetRotation().z);
	}
	return;
}


bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix ,tmpMatrix, orthoMatrix; //아영
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// 몸통 조절
	//D3DXMatrixRotationY(&worldMatrix, rotation);
	D3DXMatrixScaling(&worldMatrix, 0.5f, 0.5f, 0.5f);
	//D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_DogBodyModel->Render(m_D3D->GetDeviceContext());
	

	// Render the model using the light shader.
	
	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_DogBodyModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
								   m_DogBodyModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(), 
								   m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if(!result)
	{
		return false;
	}

	// 머리 조절
	D3DXMatrixTranslation(&tmpMatrix, 0.0f, 3.4f, 0.0f);
	D3DXMatrixScaling(&worldMatrix, 0.4f, 0.4f, 0.4f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);
	D3DXMatrixRotationX(&tmpMatrix, rotation);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);
	


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_DogHeadModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_DogHeadModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_DogHeadModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// 바닥 조절
	
	D3DXMatrixScaling(&tmpMatrix, 0.7f, 0.7f, 1.0f);
	D3DXMatrixTranslation(&worldMatrix, 10.0f, -5.5f, -30.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_FloorModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_FloorModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_FloorModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// 뒷 벽 조절

	D3DXMatrixScaling(&tmpMatrix, 1.2f, 0.6f, 0.6f);
	D3DXMatrixTranslation(&worldMatrix, 20.0f, -5.5f, 13.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_BackWallModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_BackWallModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_BackWallModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// left 벽 조절

	D3DXMatrixScaling(&tmpMatrix, 0.02f, 0.6f, 15.0f);
	D3DXMatrixTranslation(&worldMatrix, -1002.0f, -5.5f, -3.4f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_LeftWallModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_LeftWallModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_LeftWallModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// right 벽 조절

		D3DXMatrixScaling(&tmpMatrix, 0.02f, 0.6f, 15.0f);
		D3DXMatrixTranslation(&worldMatrix, 2502.0f, -5.5f, -3.4f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_RightWallModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_RightWallModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_RightWallModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}
	
	// 스테이지 조절

	D3DXMatrixScaling(&tmpMatrix, 0.8f, 0.6f, 1.0f);
	D3DXMatrixTranslation(&worldMatrix, -7.0f, -5.5f, -10.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_StageModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_StageModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_StageModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}
	// 바 조절

	D3DXMatrixScaling(&tmpMatrix, 0.1f, 2.0f, 1.0f);
	D3DXMatrixTranslation(&worldMatrix,300.0f, -2.5f, -10.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_BarColModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_BarColModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_BarColModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}


	D3DXMatrixScaling(&tmpMatrix, 0.5f, 2.0f, 0.15f);
	D3DXMatrixTranslation(&worldMatrix, 80.0f, -2.5f, -118.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_BarRowModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_BarRowModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_BarRowModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Table 1 조절

	D3DXMatrixScaling(&tmpMatrix, 0.9f, 0.9f, 0.9f);
	D3DXMatrixTranslation(&worldMatrix, 0.0f, -4.0f, -50.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);
	


	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_TableModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_TableModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_TableModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Table 2 조절

	D3DXMatrixScaling(&tmpMatrix, 0.9f, 0.9f, 0.9f);
	D3DXMatrixTranslation(&worldMatrix, 25.0f, -4.0f, -50.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);



	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_TableModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_TableModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_TableModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Girl 조절

	D3DXMatrixScaling(&tmpMatrix, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&worldMatrix, 55.0f, 4.0f, -110.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);



	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_GirlModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_GirlModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_GirlModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Frame 조절

	D3DXMatrixScaling(&tmpMatrix, 0.3f, 0.3f, 0.3f);
	D3DXMatrixTranslation(&worldMatrix, 60.0f, 23.0f, 22.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);



	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_FrameModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_FrameModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_FrameModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// 피아노 조절

	D3DXMatrixScaling(&tmpMatrix, 0.7f, 0.7f, 0.7f);
	D3DXMatrixTranslation(&worldMatrix, -20.0f, -1.4f, 6.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);



	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_PianoModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_PianoModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_PianoModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Stool1 조절

	D3DXMatrixScaling(&tmpMatrix, 0.7f, 0.7f, 0.7f);
	D3DXMatrixTranslation(&worldMatrix, 33.0f, -5.0f, 0.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);



	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_StoolModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_StoolModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_StoolModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Stool2 조절

	D3DXMatrixScaling(&tmpMatrix, 0.7f, 0.7f, 0.7f);
	D3DXMatrixTranslation(&worldMatrix, 33.0f, -5.0f, -15.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);



	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_StoolModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_StoolModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_StoolModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Stool3 조절

	D3DXMatrixScaling(&tmpMatrix, 0.7f, 0.7f, 0.7f);
	D3DXMatrixTranslation(&worldMatrix, 33.0f, -5.0f, -30.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);



	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_StoolModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_StoolModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_StoolModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Coffee Grinder 조절

	D3DXMatrixScaling(&tmpMatrix, 0.2f, 0.2f, 0.2f);
	D3DXMatrixTranslation(&worldMatrix, 150.0f, 15.0f, 0.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);



	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_CoffeeGrinderModel->Render(m_D3D->GetDeviceContext());

	 
	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_CoffeeGrinderModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_CoffeeGrinderModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// bookshelf 조절

	D3DXMatrixScaling(&tmpMatrix, 0.7f, 0.7f, 0.7f);
	D3DXMatrixTranslation(&worldMatrix, 65.0f, -6.0f, -60.0f);
	D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &tmpMatrix);



	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	m_BookShelfModel->Render(m_D3D->GetDeviceContext());


	// Render the model using the light shader.

	result = m_LightShader->Render(m_D3D->GetDeviceContext(), m_BookShelfModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
		m_BookShelfModel->GetTexture(), m_Light->GetDirection(), m_Light->GetAmbientColor(), m_Light->GetDiffuseColor(),
		m_Camera->GetPosition(), m_Light->GetSpecularColor(), m_Light->GetSpecularPower());
	if (!result)
	{
		return false;
	}

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);
	m_D3D->GetOrthoMatrix(orthoMatrix);

	// Turn off the Z buffer to begin all 2D rendering. 
	m_D3D->TurnZBufferOff();
	// Turn on the alpha blending before rendering the text. 
	m_D3D->TurnOnAlphaBlending();

	// Render the text strings. 
	result = m_Text->Render(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	if (!result)
	{
		return false;
	}

	// Turn off alpha blending after rendering the text. 
	m_D3D->TurnOffAlphaBlending();
	// Turn the Z buffer back on now that all 2D rendering has completed.
	m_D3D->TurnZBufferOn();




	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}

int GraphicsClass::PolygonUsed()
{


	return polygon_used;
}