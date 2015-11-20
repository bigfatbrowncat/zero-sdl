#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <bgfx/bgfx.h>
#include <bgfx/bgfxplatform.h>
#include <bx/uint32_t.h>
#include <unistd.h>
#include "logo.h"

//#define WINDOW_WIDTH		800
//#define WINDOW_HEIGHT		600

enum EventResult {
	erNoEvent, erProcessed, erExit
};

static EventResult processEvent() {
	bool exit = false;
	SDL_Event event;
	if (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT:
			//m_eventQueue.postExitEvent();
			exit = true;
			break;

		case SDL_MOUSEMOTION:
			/*{
				const SDL_MouseMotionEvent& mev = event.motion;
				m_mx = mev.x;
				m_my = mev.y;

				WindowHandle handle = findHandle(mev.windowID);
				if (isValid(handle) )
				{
					m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_mz);
				}
			}*/
			break;

		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			/*{
				const SDL_MouseButtonEvent& mev = event.button;
				WindowHandle handle = findHandle(mev.windowID);
				if (isValid(handle) )
				{
					MouseButton::Enum button;
					switch (mev.button)
					{
					default:
					case SDL_BUTTON_LEFT:   button = MouseButton::Left;   break;
					case SDL_BUTTON_MIDDLE: button = MouseButton::Middle; break;
					case SDL_BUTTON_RIGHT:  button = MouseButton::Right;  break;
					}

					m_eventQueue.postMouseEvent(handle
						, mev.x
						, mev.y
						, 0
						, button
						, mev.type == SDL_MOUSEBUTTONDOWN
						);
				}
			}*/
			break;

		case SDL_MOUSEWHEEL:
			/*{
				const SDL_MouseWheelEvent& mev = event.wheel;
				m_mz += mev.y;

				WindowHandle handle = findHandle(mev.windowID);
				if (isValid(handle) )
				{
					m_eventQueue.postMouseEvent(handle, m_mx, m_my, m_mz);
				}
			}*/
			break;

		case SDL_TEXTINPUT:
			/*{
				const SDL_TextInputEvent& tev = event.text;
				WindowHandle handle = findHandle(tev.windowID);
				if (isValid(handle) )
				{
					m_eventQueue.postCharEvent(handle, 1, (const uint8_t*)tev.text);
				}
			}*/
			break;

		case SDL_KEYDOWN:
			/*{
				const SDL_KeyboardEvent& kev = event.key;
				WindowHandle handle = findHandle(kev.windowID);
				if (isValid(handle) )
				{
					uint8_t modifiers = translateKeyModifiers(kev.keysym.mod);
					Key::Enum key = translateKey(kev.keysym.scancode);

					// TODO: These keys are not captured by SDL_TEXTINPUT. Should be probably handled by SDL_TEXTEDITING. This is a workaround for now.
					if (key == 1) // Escape
					{
						uint8_t pressedChar[4];
						pressedChar[0] = 0x1b;
						m_eventQueue.postCharEvent(handle, 1, pressedChar);
					}
					else if (key == 2) // Enter
					{
						uint8_t pressedChar[4];
						pressedChar[0] = 0x0d;
						m_eventQueue.postCharEvent(handle, 1, pressedChar);
					}
					else if (key == 5) // Backspace
					{
						uint8_t pressedChar[4];
						pressedChar[0] = 0x08;
						m_eventQueue.postCharEvent(handle, 1, pressedChar);
					}
					else
					{
						m_eventQueue.postKeyEvent(handle, key, modifiers, kev.state == SDL_PRESSED);
					}
				}
			}*/
			break;
		case SDL_KEYUP:
			/*{
				const SDL_KeyboardEvent& kev = event.key;
				WindowHandle handle = findHandle(kev.windowID);
				if (isValid(handle) )
				{
					uint8_t modifiers = translateKeyModifiers(kev.keysym.mod);
					Key::Enum key = translateKey(kev.keysym.scancode);
					m_eventQueue.postKeyEvent(handle, key, modifiers, kev.state == SDL_PRESSED);
				}
			}*/
			break;

		case SDL_WINDOWEVENT:
			{
				const SDL_WindowEvent& wev = event.window;
				switch (wev.event)
				{
				case SDL_WINDOWEVENT_RESIZED:
				case SDL_WINDOWEVENT_SIZE_CHANGED:
/*					width = wev.data1;
					height = wev.data2;
					printf("w: %d, h: %d\n", width, height);*/
					/*{
						WindowHandle handle = findHandle(wev.windowID);
						setWindowSize(handle, wev.data1, wev.data2);

					}*/
					break;

				case SDL_WINDOWEVENT_SHOWN:
				case SDL_WINDOWEVENT_HIDDEN:
				case SDL_WINDOWEVENT_EXPOSED:
				case SDL_WINDOWEVENT_MOVED:
				case SDL_WINDOWEVENT_MINIMIZED:
				case SDL_WINDOWEVENT_MAXIMIZED:
				case SDL_WINDOWEVENT_RESTORED:
				case SDL_WINDOWEVENT_ENTER:
				case SDL_WINDOWEVENT_LEAVE:
				case SDL_WINDOWEVENT_FOCUS_GAINED:
				case SDL_WINDOWEVENT_FOCUS_LOST:
					break;

				case SDL_WINDOWEVENT_CLOSE:
					/*{
						WindowHandle handle = findHandle(wev.windowID);
						if (0 == handle.idx)
						{
							m_eventQueue.postExitEvent();
							exit = true;
						}
					}*/
					exit = true;
					break;
				}
			}
			break;

		case SDL_CONTROLLERAXISMOTION:
			/*{
				const SDL_ControllerAxisEvent& aev = event.caxis;
				GamepadHandle handle = findGamepad(aev.which);
				if (isValid(handle) )
				{
					GamepadAxis::Enum axis = translateGamepadAxis(aev.axis);
					int32_t value = aev.value;
					if (m_gamepad[handle.idx].filter(axis, &value) )
					{
						m_eventQueue.postAxisEvent(defaultWindow, handle, axis, value);
					}
				}
			}*/
			break;

		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERBUTTONUP:
			/*{
				const SDL_ControllerButtonEvent& bev = event.cbutton;
				GamepadHandle handle = findGamepad(bev.which);
				if (isValid(handle) )
				{
					Key::Enum key = translateGamepad(bev.button);
					if (Key::Count != key)
					{
						m_eventQueue.postKeyEvent(defaultWindow, key, 0, event.type == SDL_CONTROLLERBUTTONDOWN);
					}
				}
			}*/
			break;

		case SDL_CONTROLLERDEVICEADDED:
			/*{
				const SDL_ControllerDeviceEvent& cev = event.cdevice;

				GamepadHandle handle = { m_gamepadAlloc.alloc() };
				if (isValid(handle) )
				{
					m_gamepad[handle.idx].create(cev.which);
					m_eventQueue.postGamepadEvent(defaultWindow, handle, true);
				}
			}*/
			break;

		case SDL_CONTROLLERDEVICEREMAPPED:
			{

			}
			break;

		case SDL_CONTROLLERDEVICEREMOVED:
			/*{
				const SDL_ControllerDeviceEvent& cev = event.cdevice;
				GamepadHandle handle = findGamepad(cev.which);
				if (isValid(handle) )
				{
					m_gamepad[handle.idx].destroy();
					m_gamepadAlloc.free(handle.idx);
					m_eventQueue.postGamepadEvent(defaultWindow, handle, false);
				}
			}*/
			break;

		default:
			/*{
				const SDL_UserEvent& uev = event.user;
				switch (uev.type - s_userEventStart)
				{
				case SDL_USER_WINDOW_CREATE:
					{
						WindowHandle handle = getWindowHandle(uev);
						Msg* msg = (Msg*)uev.data2;

						m_window[handle.idx] = SDL_CreateWindow(msg->m_title.c_str()
													, msg->m_x
													, msg->m_y
													, msg->m_width
													, msg->m_height
													, SDL_WINDOW_SHOWN
													| SDL_WINDOW_RESIZABLE
													);

						m_flags[handle.idx] = msg->m_flags;

						void* nwh = sdlNativeWindowHandle(m_window[handle.idx]);
						if (NULL != nwh)
						{
							m_eventQueue.postWindowEvent(handle, nwh);
							m_eventQueue.postSizeEvent(handle, msg->m_width, msg->m_height);
						}

						delete msg;
					}
					break;

				case SDL_USER_WINDOW_DESTROY:
					{
						WindowHandle handle = getWindowHandle(uev);
						if (isValid(handle) )
						{
							m_eventQueue.postWindowEvent(handle);
							SDL_DestroyWindow(m_window[handle.idx]);
							m_window[handle.idx] = NULL;
						}
					}
					break;

				case SDL_USER_WINDOW_SET_TITLE:
					{
						WindowHandle handle = getWindowHandle(uev);
						Msg* msg = (Msg*)uev.data2;
						if (isValid(handle) )
						{
							SDL_SetWindowTitle(m_window[handle.idx], msg->m_title.c_str() );
						}
						delete msg;
					}
					break;

				case SDL_USER_WINDOW_SET_POS:
					{
						WindowHandle handle = getWindowHandle(uev);
						Msg* msg = (Msg*)uev.data2;
						SDL_SetWindowPosition(m_window[handle.idx], msg->m_x, msg->m_y);
						delete msg;
					}
					break;

				case SDL_USER_WINDOW_SET_SIZE:
					{
						WindowHandle handle = getWindowHandle(uev);
						Msg* msg = (Msg*)uev.data2;
						if (isValid(handle) )
						{
							setWindowSize(handle, msg->m_width, msg->m_height);
						}
						delete msg;
					}
					break;

				case SDL_USER_WINDOW_TOGGLE_FRAME:
					{
						WindowHandle handle = getWindowHandle(uev);
						if (isValid(handle) )
						{
							m_flags[handle.idx] ^= ENTRY_WINDOW_FLAG_FRAME;
							SDL_SetWindowBordered(m_window[handle.idx], (SDL_bool)!!(m_flags[handle.idx] & ENTRY_WINDOW_FLAG_FRAME) );
						}
					}
					break;

				case SDL_USER_WINDOW_TOGGLE_FULL_SCREEN:
					{
						WindowHandle handle = getWindowHandle(uev);
						m_fullscreen = !m_fullscreen;
						SDL_SetWindowFullscreen(m_window[handle.idx], m_fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
					}
					break;

				case SDL_USER_WINDOW_MOUSE_LOCK:
					{
						SDL_SetRelativeMouseMode(!!uev.code ? SDL_TRUE : SDL_FALSE);
					}
					break;

				default:
					break;
				}
			}*/
			break;
		}
		if (exit) {
			return erExit;
		} else {
			return erProcessed;
		}
	} else {
		return erNoEvent;
	}
}


SDL_Window* window = NULL;

volatile bool finish = false;
volatile bool renderingStarted = false;
volatile bool renderingFinished = false;

uint32_t my_callbackfunc(Uint32 interval, void *param)
{
	int width = 1280;
	int height = 720;

	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("bgfx x",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		width, height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	renderingStarted = true;

	SDL_GetWindowSize(window, &width, &height);

	uint32_t debug = BGFX_DEBUG_TEXT;
	uint32_t reset = BGFX_RESET_VSYNC;

	bgfx::sdlSetWindow(window);
	bgfx::renderFrame();

	bgfx::init();
	bgfx::reset(width, height, reset);

	// Enable debug text.
	bgfx::setDebug(debug);

	// Set view 0 clear state.
	bgfx::setViewClear(0
		, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
		, 0x303030ff
		, 1.0f
		, 0
		);

	while (!finish) {
		usleep(10000);
		printf("@");fflush(stdout);

		SDL_GetWindowSize(window, &width, &height);

		bgfx::reset(width, height, reset);

		// Set view 0 default viewport.
		bgfx::setViewRect(0, 0, 0, width, height);

		// This dummy draw call is here to make sure that view 0 is cleared
		// if no other draw calls are submitted to view 0.
		bgfx::touch(0);

		// Use debug font to print information about this example.
		bgfx::dbgTextClear();
		bgfx::dbgTextImage(bx::uint16_max(width/2/8, 20)-20
						 , bx::uint16_max(height/2/16, 6)-6
						 , 40
						 , 12
						 , s_logo
						 , 160
						 );
		bgfx::dbgTextPrintf(0, 1, 0x4f, "bgfx/examples/00-helloworld");
		bgfx::dbgTextPrintf(0, 2, 0x6f, "Description: Initialization and debug text.");

		// Advance to next frame. Rendering thread will be kicked to
		// process submitted rendering primitives.
		bgfx::frame();

	}

	bgfx::shutdown();

	SDL_DestroyWindow(window);

	renderingFinished = true;
	return 0;
}

int main(int _argc, char** _argv)
{
	SDL_Init(SDL_INIT_GAMECONTROLLER | SDL_INIT_TIMER);

	SDL_TimerID my_timer_id = SDL_AddTimer(0, my_callbackfunc, NULL);

	// Waiting for the render thread to start
	while (!renderingStarted) { usleep(1); }

	while (processEvent() != erExit)
	{
		printf("!");fflush(stdout);
		usleep(100);
	}

	finish = true;

	// Waiting for the render thread to stop
	while (!renderingFinished) { usleep(1); }

	SDL_Quit();

	//return m_thread.getExitCode();
	return 0;
}
