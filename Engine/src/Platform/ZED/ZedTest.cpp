#include "enpch.h"


#include "ZedTest.h"
#include <opencv2/opencv.hpp>


#include "Platform/OpenGl/GL.h"

#include <cuda_gl_interop.h>		//after glut init!!

ZedTest::ZedTest()
{
}

ZedTest::~ZedTest()
{
	// Exit
	zed.close();
}

void ZedTest::Init(int width, int height)
{
	//init zed camera
	std::cout << "starting test" << std::endl;


	sl::InitParameters init_params;
	init_params.sdk_verbose = false;

	sl::ERROR_CODE err = zed.open();
	if (err != sl::SUCCESS)
	{
		std::cout << toString(err) << std::endl;
		zed.close();
		exit(-1); // Quit if an error occurred
	}

	int zed_serial = zed.getCameraInformation().serial_number;
	std::cout << "ZED camera initialized: " << zed_serial << std::endl;

	//get window paremeters
	m_CamWidth = zed.getResolution().width * 2;
	m_CamHeight = zed.getResolution().height;

	m_VRWidth = width;
	m_VRHeight = height;

	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &imageTex);
	glBindTexture(GL_TEXTURE_2D, imageTex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_CamWidth, m_CamHeight, 0, GL_BGRA, GL_UNSIGNED_BYTE, NULL);
	glBindTexture(GL_TEXTURE_2D, 0);
	cudaError_t err1 = cudaGraphicsGLRegisterImage(&cuda_gl_ressource, imageTex, GL_TEXTURE_2D, cudaGraphicsRegisterFlagsWriteDiscard);
	if (err1 != cudaError::cudaSuccess)
		return;

	// Create GLSL image Shader
	shader_image = new ZedShader((GLchar*)IMAGE_VERTEX_SHADER, (GLchar*)IMAGE_FRAGMENT_SHADER);
	
	texID = glGetUniformLocation(1, "texImage");

	// Create Frame Buffer for offline rendering
	// Here we render the composition of the image and the projection of the mesh on top of it in a texture (using FBO - Frame Buffer Object)
	
	glGenFramebuffers(1, &fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Generate a render texture (which will contain the image and mesh in wireframe overlay)
	
	glGenTextures(1, &renderedTexture);
	glBindTexture(GL_TEXTURE_2D, renderedTexture);

	// Give an empty image to OpenGL ( the last "0" as pointer )
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_VRWidth, m_VRHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	// Set "renderedTexture" as our color attachment #0
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, renderedTexture, 0);

	// Set the list of draw buffers.
	GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };
	glDrawBuffers(1, DrawBuffers);

	// Always check that our framebuffer is ok
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		std::cout << "invalid FrameBuffer" << std::endl;
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Generate the Quad for showing the image in a full viewport
	static const GLfloat g_quad_vertex_buffer_data[] = {
		-1.0f, -1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f };

	// Generate a buffer to handle vertices for the GLSL shader
	
	glGenBuffers(1, &quad_vb);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_quad_vertex_buffer_data), g_quad_vertex_buffer_data, GL_STATIC_DRAW);
}

void ZedTest::Update()
{

	if (zed.grab() == sl::SUCCESS)
	{
		//retrieve the image and store it on GPU memory
		zed.retrieveImage(image, sl::VIEW_SIDE_BY_SIDE, sl::MEM_GPU);

		// CUDA - OpenGL interop : copy the GPU buffer to a CUDA array mapped to the texture.
		cudaArray_t ArrIm;
		cudaGraphicsMapResources(1, &cuda_gl_ressource, 0);
		cudaGraphicsSubResourceGetMappedArray(&ArrIm, cuda_gl_ressource, 0, 0);
		cudaMemcpy2DToArray(ArrIm, 0, 0, image.getPtr<sl::uchar1>(sl::MEM_GPU), image.getStepBytes(sl::MEM_GPU), image.getPixelBytes() * image.getWidth(), image.getHeight(), cudaMemcpyDeviceToDevice);
		cudaGraphicsUnmapResources(1, &cuda_gl_ressource, 0);
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);

	glViewport(0, 0, m_VRWidth, m_VRHeight);

	// Render image and wireframe mesh into a texture using frame buffer
	// Bind the frame buffer and specify the viewport (full screen)
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Render the ZED view (Left) in the framebuffer
	glUseProgram(shader_image->getProgramId());
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, imageTex);
	glUniform1i(texID, 0);
	//invert y axis and color for this image (since its reverted from cuda array)
	glUniform1i(glGetUniformLocation(shader_image->getProgramId(), "revert"), 1);
	glUniform1i(glGetUniformLocation(shader_image->getProgramId(), "rgbflip"), 1);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vb);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glUseProgram(0);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Render the texture to the screen
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glUseProgram(shader_image->getProgramId());
	glBindTexture(GL_TEXTURE_2D, renderedTexture);
	glUniform1i(texID, 0);
	glUniform1i(glGetUniformLocation(shader_image->getProgramId(), "revert"), 0);
	glUniform1i(glGetUniformLocation(shader_image->getProgramId(), "rgbflip"), 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, quad_vb);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(0);
	glUseProgram(0);
	glDisable(GL_TEXTURE_2D);

	///*vr::Texture_t leftEyeTexture = { (void*)(uintptr_t)(renderedTexture, vr::TextureType_OpenGL, vr::ColorSpace_Gamma) };
	//vr::VRCompositor()->Submit(vr::Eye_Left, &leftEyeTexture);

	//vr::Texture_t rightEyeTexture = { (void*)(uintptr_t)(renderedTexture, vr::TextureType_OpenGL, vr::ColorSpace_Gamma) };
	//vr::VRCompositor()->Submit(vr::Eye_Right, &rightEyeTexture);*/

	////vrSettings.UpdateHMDMatrixPose();
}