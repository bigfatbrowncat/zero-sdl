#include "common.h"
#include "event_handler.h"

EventResult processEvents() {
	bool exit = false;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
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
			break;
		}
		if (exit) {
			return erExit;
		}
	}
	return erProcessed;
}