#include "Application.h"
#include "World.h"

#include <ClanLib/application.h>
#include <ClanLib/core.h>
#include <ClanLib/display.h>
#include <ClanLib/sound.h>
#include <ClanLib/gl.h>

int Application::main(const std::vector<CL_String> &args)
{
	try
	{		
		// Create a window
		CL_DisplayWindowDescription desc;
		desc.set_title("PacMan");
		desc.set_allow_resize(false);
		desc.set_size(CL_Size(800, 600), true);
		CL_DisplayWindow window(desc);

		CL_GraphicContext gc = window.get_gc();

		//CL_SoundOutput output(44100);

		// Create world
		World world(window);

		world.run();
	}
	catch(CL_Exception &exception)
	{
		// Create a console window for text-output if not available
		CL_ConsoleWindow console("Console", 80, 160);
		CL_Console::write_line("Exception caught: " + exception.get_message_and_stack_trace());
		console.display_close_message();

		return -1;
	}

	return 0;
}