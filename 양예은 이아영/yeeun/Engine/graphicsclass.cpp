////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
	m_Camera = 0;

	m_planeModel = 0;
	m_planeModelBack = 0;
	m_planeModelRight = 0;
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
	m_Camera->SetPosition(0.0f, 50.0f, -250.0f);
	m_Camera->SetRotation(20.0f, 0.0f, 0.0f);
	
	m_planeModel = new ModelClass;
	if (!m_planeModel)
	{
		return false;
	}
	result = m_planeModel->Initialize(m_D3D->GetDevice(), "../Engine/data/realplane.obj", L"../Engine/data/Floor.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	m_planeModelBack = new ModelClass;
	if (!m_planeModelBack)
	{
		return false;
	}
	result = m_planeModelBack->Initialize(m_D3D->GetDevice(), "../Engine/data/realplane.obj", L"../Engine/data/Floor.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	m_planeModelRight = new ModelClass;
	if (!m_planeModelRight)
	{
		return false;
	}
	result = m_planeModelRight->Initialize(m_D3D->GetDevice(), "../Engine/data/realplane.obj", L"../Engine/data/Floor.dds");
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	// Initialize the model object.
	//¾Æ¿µ
	
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}
	// Initialize the texture shader object.
	result = m_TextureShader->Initialize(m_D3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	
	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	
	if (m_planeModel)
	{
		m_planeModel->Shutdown();
		delete m_planeModel;
		m_planeModel = 0;
	}
	
		if (m_planeModelBack)
		{
			m_planeModelBack->Shutdown();
			delete m_planeModelBack;
			m_planeModelBack = 0;
		}
		if (m_planeModelRight)
		{
			m_planeModelRight->Shutdown();
			delete m_planeModelRight;
			m_planeModelRight = 0;
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
	rotation += (float)D3DX_PI * 0.01f;
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


bool GraphicsClass::Render(float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_Camera->GetViewMatrix(viewMatrix);

	

	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			////////////////////
			// Reset the world matrix.
			m_D3D->GetWorldMatrix(worldMatrix);
			m_D3D->GetProjectionMatrix(projectionMatrix);

			// Translate to where the model will be rendered.


			D3DXMatrixTranslation(&worldMatrix, -5.0f + 0.3f*i, 0.0f, -20.0f + 0.5f*j);
			D3DXMatrixScaling(&translateMatrix, 10.0f, 5.0f, 10.0f);
			D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

			// Put the wall model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			m_planeModel->Render(m_D3D->GetDeviceContext());


			result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_planeModel->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_planeModel->GetTexture());
			if (!result)
			{
				return false;
			}
		}	
	}
		
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			////////////////////
			// Reset the world matrix.
			m_D3D->GetWorldMatrix(worldMatrix);
			m_D3D->GetProjectionMatrix(projectionMatrix);

			// Translate to where the model will be rendered.


			D3DXMatrixTranslation(&worldMatrix, -5.0f + 0.5f*j, 10.0f-0.5f*i, -0.0f);
			D3DXMatrixScaling(&translateMatrix, 10.0f, 5.0f, 10.0f);
			D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

			// Put the wall model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			m_planeModelBack->Render(m_D3D->GetDeviceContext());


			result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_planeModelBack->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_planeModelBack->GetTexture());
			if (!result)
			{
				return false;
			}
		}
	}
	
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			////////////////////
			// Reset the world matrix.
			m_D3D->GetWorldMatrix(worldMatrix);
			m_D3D->GetProjectionMatrix(projectionMatrix);

			// Translate to where the model will be rendered.


			D3DXMatrixTranslation(&worldMatrix, -5.0f + 0.5f*j, 10.0f - 0.5f*i, -0.0f );
			D3DXMatrixScaling(&translateMatrix, 10.0f, 5.0f, 10.0f);
			D3DXMatrixMultiply(&worldMatrix, &worldMatrix, &translateMatrix);

			// Put the wall model vertex and index buffers on the graphics pipeline to prepare them for drawing.
			m_planeModelRight->Render(m_D3D->GetDeviceContext());


			result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_planeModelRight->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix,
				m_planeModelRight->GetTexture());
			if (!result)
			{
				return false;
			}
		}
	}

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}
