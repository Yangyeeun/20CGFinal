////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;
	m_DogHeadModel = 0;
	m_DogBodyModel = 0;
	m_BackWallModel = 0;
	m_FloorModel = 0;
	m_StageModel = 0;
	m_LightShader = 0;
	m_Light = 0;
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

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 10.0f, -50.0f);
	

	// °­¾ÆÁö ¸ö

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

	// °­¾ÆÁö ¾ó±¼

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

	// ¹Ù´Ú ¸ğµ¨

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

	// º® ¸ğµ¨

	// Create the model object.
	m_BackWallModel = new ModelClass;
	if (!m_BackWallModel)
	{
		return false;
	}

	// Initialize the model object.
	result = m_BackWallModel->Initialize(m_D3D->GetDevice(), "../Engine/data/Wall.obj", L"../Engine/data/Wall.jpg");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the BackWall model object.", L"Error", MB_OK);
		return false;
	}

	// ½ºÅ×ÀÌÁö ¸ğµ¨

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


bool GraphicsClass::Frame()
{
	bool result;
	static float rotation = 0.0f;


	// Update the rotation variable each frame.
	rotation += (float)D3DX_PI * 0.005f;
	if(rotation > 360.0f)
	{
		rotation -= 360.0f;
	}
	
	// Render the graphics scene.
	result = Render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}

void GraphicsClass::MovingCamera(int n)
{
	float speed = 0.2f;
	
	if (n == 1)
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z + speed);
	}
	else if (n == 2)
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x, m_Camera->GetPosition().y, m_Camera->GetPosition().z - speed);
	}
	else if (n == 3)
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x - speed, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
	}
	else if (n == 4)
	{
		m_Camera->SetPosition(m_Camera->GetPosition().x + speed, m_Camera->GetPosition().y, m_Camera->GetPosition().z);
	}
	return;
}


bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix ,tmpMatrix; //¾Æ¿µ
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetWorldMatrix(worldMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);

	// ¸öÅë Á¶Àı
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

	// ¸Ó¸® Á¶Àı
	D3DXMatrixTranslation(&tmpMatrix, 0.0f, 3.4f, 0.0f);
	D3DXMatrixScaling(&worldMatrix, 0.4f, 0.4f, 0.4f);
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

	// ¹Ù´Ú Á¶Àı
	
	D3DXMatrixScaling(&tmpMatrix, 0.7f, 0.7f, 0.7f);
	D3DXMatrixTranslation(&worldMatrix, 40.0f, -3.0f, -40.0f);
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

	// µŞ º® Á¶Àı

	D3DXMatrixScaling(&tmpMatrix, 0.8f, 0.6f, 0.6f);
	D3DXMatrixTranslation(&worldMatrix, 10.0f, 0.0f, 13.0f);
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

	// ½ºÅ×ÀÌÁö Á¶Àı

	D3DXMatrixScaling(&tmpMatrix, 0.8f, 0.6f, 0.6f);
	D3DXMatrixTranslation(&worldMatrix, 10.0f, 0.0f, 13.0f);
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


	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}