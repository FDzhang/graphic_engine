#include "../Render/GLES2Render/CSwapChain.h"


EGLNativeWindowType	eglWindow;


#ifdef WIN32
bool TestEGLError(HWND hWnd, char* pszLocation)
{
	/*
		eglGetError returns the last error that has happened using egl,
		not the status of the last called function. The user has to
		check after every single egl call or at least once every frame.
	*/
	EGLint iErr = eglGetError();
	if (iErr != EGL_SUCCESS)
	{
		TCHAR pszStr[256];
		//_stprintf(pszStr, _T("%s failed (%d).\n"), pszLocation, iErr);
		//MessageBox(hWnd, pszStr, _T("Error"), MB_OK|MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}
#endif
#ifdef LINUX_J6

extern EGLDisplay my_display;
extern EGLContext my_context;
extern EGLSurface my_surf;

#endif
#ifdef WIN_32
bool XrCreateDeviceContextAndSwapChain(int width, int height, int context, CRenderContext** ppCContext, CRenderDevice** ppCDevice, CSwapChain** ppCSwapChain, int type)
{
	HWND hWnd = (HWND)context;
	CRenderDevice* pXrRenderDevice = new CRenderDevice;
	CRenderContext* pXrRenderContext = new CRenderContext;
	CSwapChain* pXrSwapChain = new CSwapChain;

	eglWindow = (EGLNativeWindowType)context;
	    GLint temp;
	// Get the associated device context
	HDC hDC = GetDC((HWND)context);
	if (!hDC)
	{
		//MessageBox(0, _T("Failed to create the device context"), _T("Error"), MB_OK|MB_ICONEXCLAMATION);
		goto cleanup;
	}

	/*
		Step 1 - Get the default display.
		EGL uses the concept of a "display" which in most environments
		corresponds to a single physical screen. Since we usually want
		to draw to the main screen or only have a single screen to begin
		with, we let EGL pick the default display.
		Querying other displays is platform specific.
	*/
	pXrSwapChain->eglDisplay = eglGetDisplay(hDC);

    if(pXrSwapChain->eglDisplay == EGL_NO_DISPLAY)
         pXrSwapChain->eglDisplay = eglGetDisplay((EGLNativeDisplayType) EGL_DEFAULT_DISPLAY);
	/*
		Step 2 - Initialize EGL.
		EGL has to be initialized with the display obtained in the
		previous step. We cannot use other EGL functions except
		eglGetDisplay and eglGetError before eglInitialize has been
		called.
		If we're not interested in the EGL version number we can just
		pass NULL for the second and third parameters.
	*/

	EGLint iMajorVersion, iMinorVersion;
	if (!eglInitialize(pXrSwapChain->eglDisplay, &iMajorVersion, &iMinorVersion))
	{
		//MessageBox(0, _T("eglInitialize() failed."), _T("Error"), MB_OK|MB_ICONEXCLAMATION);
		goto cleanup;
	}

	/*
		Step 3 - Make OpenGL ES the current API.
		EGL provides ways to set up OpenGL ES and OpenVG contexts
		(and possibly other graphics APIs in the future), so we need
		to specify the "current API".
	*/

	/*
		Step 4 - Specify the required configuration attributes.
		An EGL "configuration" describes the pixel format and type of
		surfaces that can be used for drawing.
		For now we just want to use the default Windows surface,
		i.e. it will be visible on screen. The list
		has to contain key/value pairs, terminated with EGL_NONE.
	 */
	   // Get configs
	int tw;
   if ( !eglGetConfigs(pXrSwapChain->eglDisplay, NULL, 0, &tw) )
   {
      return EGL_FALSE;
   }
	const EGLint pi32ConfigAttribs[] =
	{
		////EGL_LEVEL,				0,
		//EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
		//EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
		//EGL_NATIVE_RENDERABLE,	EGL_FALSE,
		////EGL_DEPTH_SIZE,			EGL_DONT_CARE,
	//	EGL_DEPTH_SIZE,			8,
			   EGL_RED_SIZE,       8,
       EGL_GREEN_SIZE,     8,
       EGL_BLUE_SIZE,      8,
       EGL_ALPHA_SIZE,     8,
       EGL_DEPTH_SIZE,     24,
       EGL_STENCIL_SIZE,   8,
       EGL_SAMPLE_BUFFERS, 1,
        EGL_SAMPLES, 8,
		EGL_NONE
	};

	/*
		Step 5 - Find a config that matches all requirements.
		eglChooseConfig provides a list of all available configurations
		that meet or exceed the requirements given as the second
		argument. In most cases we just want the first config that meets
		all criteria, so we can limit the number of configs returned to 1.
	*/
	EGLint iConfigs;
	EGLConfig			eglConfig;
	if (!eglChooseConfig(pXrSwapChain->eglDisplay, pi32ConfigAttribs, &eglConfig, 1, &iConfigs) || (iConfigs != 1))
	{
		//MessageBox(0, _T("eglChooseConfig() failed."), _T("Error"), MB_OK|MB_ICONEXCLAMATION);
		goto cleanup;
	}
	/*
		Step 6 - Create a surface to draw to.
		Use the config picked in the previous step and the native window
		handle when available to create a window surface. A window surface
		is one that will be visible on screen inside the native display (or
		fullscreen if there is no windowing system).
		Pixmaps and pbuffers are surfaces which only exist in off-screen
		memory.
	*/
	pXrSwapChain->eglSurface = eglCreateWindowSurface(pXrSwapChain->eglDisplay, eglConfig, eglWindow, NULL);

    if(pXrSwapChain->eglSurface == EGL_NO_SURFACE)
    {
        eglGetError(); // Clear error
        pXrSwapChain->eglSurface = eglCreateWindowSurface(pXrSwapChain->eglDisplay, eglConfig, NULL, NULL);
	}
	if (!TestEGLError(hWnd, "eglCreateWindowSurface"))
	{
		goto cleanup;
	}

	/*
		Step 7 - Create a context.
		EGL has to create a context for OpenGL ES. Our OpenGL ES resources
		like textures will only be valid inside this context
		(or shared contexts)
	*/
	EGLint ai32ContextAttribs[] ={ EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };
	pXrSwapChain->eglContext = eglCreateContext(pXrSwapChain->eglDisplay, eglConfig, NULL, ai32ContextAttribs);
	if (!TestEGLError(hWnd, "eglCreateContext"))
	{
		goto cleanup;
	}
	eglBindAPI(EGL_OPENGL_ES_API);
	
	if (!TestEGLError(hWnd, "eglBindAPI"))
	{
		goto cleanup;
	}
	/*
		Step 8 - Bind the context to the current thread and use our
		window surface for drawing and reading.
		Contexts are bound to a thread. This means you don't have to
		worry about other threads and processes interfering with your
		OpenGL ES application.
		We need to specify a surface that will be the target of all
		subsequent drawing operations, and one that will be the source
		of read operations. They can be the same surface.
	*/
	eglMakeCurrent(pXrSwapChain->eglDisplay, pXrSwapChain->eglSurface, pXrSwapChain->eglSurface, pXrSwapChain->eglContext);
	if (!TestEGLError(hWnd, "eglMakeCurrent"))
	{
		goto cleanup;
	}


	if (ppCContext) *ppCContext = pXrRenderContext;
	if (ppCDevice) *ppCDevice = pXrRenderDevice;
	if (ppCSwapChain) *ppCSwapChain = pXrSwapChain;

	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &(*ppCSwapChain)->fbid);
	
	(*ppCSwapChain)->m_width = width;
	(*ppCSwapChain)->m_height = height;

	return true;

cleanup:
	eglMakeCurrent(pXrSwapChain->eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglTerminate(pXrSwapChain->eglDisplay);

	return false;
}
#endif
#ifdef LINUX_J6
bool XrCreateDeviceContextAndSwapChain(int width, int height, int context, CRenderContext** ppCContext, CRenderDevice** ppCDevice, CSwapChain** ppCSwapChain, int type)
{
    #ifdef WINDOWS32
	HWND hWnd = (HWND)context;
	#endif
	CRenderDevice* pXrRenderDevice = new CRenderDevice;
	CRenderContext* pXrRenderContext = new CRenderContext;
	CSwapChain* pXrSwapChain = new CSwapChain;
	const EGLint pi32ConfigAttribs[] =
	{
		EGL_LEVEL,				0,
		EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE,	EGL_OPENGL_ES2_BIT,
		EGL_NATIVE_RENDERABLE,	EGL_FALSE,
		//EGL_DEPTH_SIZE,			EGL_DONT_CARE,
		EGL_DEPTH_SIZE,			8,
		EGL_NONE
	};
	EGLint ai32ContextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE };

	eglWindow = (EGLNativeWindowType)context;
#ifdef WINDOWS32
   
	// Get the associated device context
	HDC hDC = GetDC((HWND)context);
	if (!hDC)
	{
		//MessageBox(0, _T("Failed to create the device context"), _T("Error"), MB_OK|MB_ICONEXCLAMATION);
		goto cleanup;
	}

	/*
		Step 1 - Get the default display.
		EGL uses the concept of a "display" which in most environments
		corresponds to a single physical screen. Since we usually want
		to draw to the main screen or only have a single screen to begin
		with, we let EGL pick the default display.
		Querying other displays is platform specific.
	*/
	pXrSwapChain->eglDisplay = eglGetDisplay(hDC);
#else
	pXrSwapChain->eglDisplay =my_display;
printf("\r\n pXrSwapChain->eglDisplay = 0x%x",pXrSwapChain->eglDisplay);
#endif

    if(pXrSwapChain->eglDisplay == EGL_NO_DISPLAY)
         pXrSwapChain->eglDisplay = eglGetDisplay((EGLNativeDisplayType) EGL_DEFAULT_DISPLAY);
	/*
		Step 2 - Initialize EGL.
		EGL has to be initialized with the display obtained in the
		previous step. We cannot use other EGL functions except
		eglGetDisplay and eglGetError before eglInitialize has been
		called.
		If we're not interested in the EGL version number we can just
		pass NULL for the second and third parameters.
	*/
#ifdef WINDOWS32
	EGLint iMajorVersion, iMinorVersion;
	if (!eglInitialize(pXrSwapChain->eglDisplay, &iMajorVersion, &iMinorVersion))
	{
		//MessageBox(0, _T("eglInitialize() failed."), _T("Error"), MB_OK|MB_ICONEXCLAMATION);
		goto cleanup;
	}
	#endif

	/*
		Step 3 - Make OpenGL ES the current API.
		EGL provides ways to set up OpenGL ES and OpenVG contexts
		(and possibly other graphics APIs in the future), so we need
		to specify the "current API".
	*/
	eglBindAPI(EGL_OPENGL_ES_API);
	#ifdef WINDOWS32
	if (!TestEGLError(hWnd, "eglBindAPI"))
	{
		goto cleanup;
	}
	/*
		Step 4 - Specify the required configuration attributes.
		An EGL "configuration" describes the pixel format and type of
		surfaces that can be used for drawing.
		For now we just want to use the default Windows surface,
		i.e. it will be visible on screen. The list
		has to contain key/value pairs, terminated with EGL_NONE.
	 */


	/*
		Step 5 - Find a config that matches all requirements.
		eglChooseConfig provides a list of all available configurations
		that meet or exceed the requirements given as the second
		argument. In most cases we just want the first config that meets
		all criteria, so we can limit the number of configs returned to 1.
	*/
	EGLint iConfigs;
	EGLConfig			eglConfig;
	if (!eglChooseConfig(pXrSwapChain->eglDisplay, pi32ConfigAttribs, &eglConfig, 1, &iConfigs) || (iConfigs != 1))
	{
		//MessageBox(0, _T("eglChooseConfig() failed."), _T("Error"), MB_OK|MB_ICONEXCLAMATION);
		goto cleanup;
	}

	/*
		Step 6 - Create a surface to draw to.
		Use the config picked in the previous step and the native window
		handle when available to create a window surface. A window surface
		is one that will be visible on screen inside the native display (or
		fullscreen if there is no windowing system).
		Pixmaps and pbuffers are surfaces which only exist in off-screen
		memory.
	*/
	pXrSwapChain->eglSurface = eglCreateWindowSurface(pXrSwapChain->eglDisplay, eglConfig, eglWindow, NULL);

    if(pXrSwapChain->eglSurface == EGL_NO_SURFACE)
    {
        eglGetError(); // Clear error
        pXrSwapChain->eglSurface = eglCreateWindowSurface(pXrSwapChain->eglDisplay, eglConfig, NULL, NULL);
	}
    #ifdef WINDOWS32
	if (!TestEGLError(hWnd, "eglCreateWindowSurface"))
	{
		goto cleanup;
	}
    #endif
	/*
		Step 7 - Create a context.
		EGL has to create a context for OpenGL ES. Our OpenGL ES resources
		like textures will only be valid inside this context
		(or shared contexts)
	*/
	pXrSwapChain->eglContext = eglCreateContext(pXrSwapChain->eglDisplay, eglConfig, NULL, ai32ContextAttribs);
    #ifdef WINDOWS32
	if (!TestEGLError(hWnd, "eglCreateContext"))
	{
		goto cleanup;
	}
	#endif

	/*
		Step 8 - Bind the context to the current thread and use our
		window surface for drawing and reading.
		Contexts are bound to a thread. This means you don't have to
		worry about other threads and processes interfering with your
		OpenGL ES application.
		We need to specify a surface that will be the target of all
		subsequent drawing operations, and one that will be the source
		of read operations. They can be the same surface.
	*/
	eglMakeCurrent(pXrSwapChain->eglDisplay, pXrSwapChain->eglSurface, pXrSwapChain->eglSurface, pXrSwapChain->eglContext);
    #ifdef WINDOWS32
	if (!TestEGLError(hWnd, "eglMakeCurrent"))
	{
		goto cleanup;
	}
    #endif
	
#endif
	pXrSwapChain->eglSurface=my_surf;
	pXrSwapChain->eglContext=my_context;
	printf("\r\n pXrSwapChain->eglSurface = 0x%x",pXrSwapChain->eglSurface);
	printf("\r\n pXrSwapChain->eglContext = 0x%x",pXrSwapChain->eglContext);

	if (ppCContext) *ppCContext = pXrRenderContext;
	if (ppCDevice) *ppCDevice = pXrRenderDevice;
	if (ppCSwapChain) *ppCSwapChain = pXrSwapChain;

	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &(*ppCSwapChain)->fbid);
	(*ppCSwapChain)->m_width = width;
	(*ppCSwapChain)->m_height = height;

	return true;

cleanup:
	eglMakeCurrent(pXrSwapChain->eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglTerminate(pXrSwapChain->eglDisplay);

	return false;
}
#endif
