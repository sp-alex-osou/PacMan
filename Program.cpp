#include "Program.h"
#include "Application.h"

#include <ClanLib/application.h>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/sound.h>
#include <ClanLib/gl.h>

CL_ClanApplication application(&Program::main);

int Program::main(const std::vector<CL_String> &args)
{
	// Initialize ClanLib base components
	CL_SetupCore setupCore;

	// Initialize the ClanLib display component
	CL_SetupDisplay setupDisplay;

	// Initialize the OpenGL drivers
	CL_SetupGL setupGL;

	// Initialize the Sound drivers
	CL_SetupSound setupSound;

	// Start the Application
	Application application;

	int returnValue = application.main(args);

	return returnValue;
}
