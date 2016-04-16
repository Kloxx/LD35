#include "Input.h"

std::ofstream input_log("input_log.txt", std::ofstream::out | std::ofstream::trunc);

Input::Input() :
    m_mouseX(0), m_mouseY(0), m_mouseRelX(0), m_mouseRelY(0),
    m_numGameControllers(0),
    m_terminate(false)
{
    // Keyboard & mouse
    for(int i(0); i<SDL_NUM_SCANCODES; i++)
        m_keys[i] = false;

    for(int i(0); i<8; i++)
        m_mouseButtons[i] = false;
		
    // GameControllers
    for(int i(0); i<4; i++)
    {
        m_gameControllers[i] = NULL;
        for(int j(0); j<13; j++)
            m_gameControllerButtons[i][j] = false;
        for(int j(0); j<6; j++)
            m_gameControllerAxis[i][j] = 0;
        m_gameControllerHat[i] = SDL_HAT_CENTERED;
    }
	
}

Input::~Input()
{}

void Input::openGameControllers()
{
    m_numGameControllers = SDL_NumJoysticks();
    if(m_numGameControllers > 4)
        m_numGameControllers = 4; // Sets maximum GameControllers to 4

    if(SDL_GameControllerAddMappingsFromFile("gamecontrollerdb.txt") == -1)
        input_log << "Cannot load gamecontroller database : " << SDL_GetError() << std::endl;

    if(m_numGameControllers)
        input_log << "Found " << m_numGameControllers << " controllers" << std::endl;

    for(int i(0); i<m_numGameControllers; i++)
    {
        if(SDL_IsGameController(i) == SDL_TRUE)
        {
            m_gameControllers[i] = SDL_GameControllerOpen(i); // Open GameControllers
            if(SDL_GameControllerGetAttached(m_gameControllers[i]))
                input_log << "Controller #" << i << " OK  : " << SDL_GameControllerName(m_gameControllers[i]) << std::endl;
				input_log << SDL_GameControllerMapping(m_gameControllers[i]) << std::endl;
        }
        else
            input_log << "Controller #" << i << " is not supported." << std::endl;
    }
	
    SDL_GameControllerEventState(SDL_ENABLE);
}

void Input::closeGameControllers()
{
    for(int i(0); i<m_numGameControllers; i++)
        if(m_gameControllers[i])
            SDL_GameControllerClose(m_gameControllers[i]); // Close GameControllers
    /*
    /!\ There might be an error if a device is removed during game session /!\
     TODO : - close GameControllers if SDL_JOYDEVICEREMOVED in events
            - update m_numGameControllers
            - re-open m_gameControllers
    */
}

void Input::updateEvents()
{
    m_mouseRelX = 0;
    m_mouseRelY = 0;

    while(SDL_PollEvent(&m_events))
    {
        switch(m_events.type)
        {
        // Keyboard events
        case SDL_KEYDOWN:
            m_keys[m_events.key.keysym.scancode] = true;
            break;

        case SDL_KEYUP:
            m_keys[m_events.key.keysym.scancode] = false;
            break;

        // Mouse events
        case SDL_MOUSEBUTTONDOWN:
            m_mouseButtons[m_events.button.button] = true;
            break;

        case SDL_MOUSEBUTTONUP:
            m_mouseButtons[m_events.button.button] = false;
            break;

        case SDL_MOUSEMOTION:
            m_mouseX = m_events.motion.x;
            m_mouseY = m_events.motion.y;

            m_mouseRelX = m_events.motion.xrel;
            m_mouseRelY = m_events.motion.yrel;
            break;

        // GameController events
        case SDL_CONTROLLERBUTTONDOWN:
            /*  --- FOR DEBUG PURPOSE ---
			
			input_log << "DOWN ";
            input_log << "which : " << m_events.cbutton.which << std::endl;
            input_log << "button : " << (int) m_events.cbutton.button << std::endl;
            switch(m_events.cbutton.button)
            {
            case SDL_CONTROLLER_BUTTON_A:
                input_log << "A"; break;
            case SDL_CONTROLLER_BUTTON_B:
                input_log << "B"; break;
            case SDL_CONTROLLER_BUTTON_BACK:
                input_log << "Back"; break;
            case SDL_CONTROLLER_BUTTON_DPAD_DOWN:
                input_log << "Dpad Down"; break;
            case SDL_CONTROLLER_BUTTON_DPAD_LEFT:
                input_log << "Dpad Left"; break;
            case SDL_CONTROLLER_BUTTON_DPAD_RIGHT:
                input_log << "Dpad Right"; break;
            case SDL_CONTROLLER_BUTTON_DPAD_UP:
                input_log << "Dpad Up"; break;
            case SDL_CONTROLLER_BUTTON_GUIDE:
                input_log << "Guide"; break;
            case SDL_CONTROLLER_BUTTON_LEFTSHOULDER:
                input_log << "LB"; break;
            case SDL_CONTROLLER_BUTTON_LEFTSTICK:
                input_log << "LS"; break;
            case SDL_CONTROLLER_BUTTON_RIGHTSHOULDER:
                input_log << "RB"; break;
            case SDL_CONTROLLER_BUTTON_RIGHTSTICK:
                input_log << "RS"; break;
            case SDL_CONTROLLER_BUTTON_START:
                input_log << "Start"; break;
            case SDL_CONTROLLER_BUTTON_X:
                input_log << "X"; break;
            case SDL_CONTROLLER_BUTTON_Y:
                input_log << "Y"; break;
            default:
                break;
            }*/
            //input_log << std::endl << std::endl;
            m_gameControllerButtons[m_events.cbutton.which][m_events.cbutton.button] = true;
            break;

        case SDL_CONTROLLERBUTTONUP:
            m_gameControllerButtons[m_events.cbutton.which][m_events.cbutton.button] = false;
            break;

        case SDL_CONTROLLERAXISMOTION:
            m_gameControllerAxis[m_events.caxis.which][m_events.caxis.axis] = m_events.caxis.value;
            break;

        case SDL_CONTROLLERDEVICEADDED:
            break;

        case SDL_CONTROLLERDEVICEREMOVED:
            break;

        // Window events
        case SDL_WINDOWEVENT:
            if(m_events.window.event == SDL_WINDOWEVENT_CLOSE)
                m_terminate = true;
            break;

        default:
            break;
        }
    }
}

bool Input::terminate() const
{
    return m_terminate;
}

bool Input::getKey(const SDL_Scancode key) const
{
    return m_keys[key];
}

bool Input::getMouseButton(const Uint8 button) const
{
    return m_mouseButtons[button];
}

bool Input::mouseMotion() const
{
    return m_mouseRelX || m_mouseRelY;
}

int Input::getMouseX() const
{
    return m_mouseX;
}

int Input::getMouseY() const
{
    return m_mouseY;
}

int Input::getMouseRelX() const
{
    return m_mouseRelX;
}

int Input::getMouseRelY() const
{
    return m_mouseRelY;
}

bool Input::getControllerButton(const int gameControllerNumber, const Uint8 button) const
{
    return m_gameControllerButtons[gameControllerNumber][button];
}

int Input::getControllerAxis(const int gameControllerNumber, const Uint8 axis) const
{
    return m_gameControllerAxis[gameControllerNumber][axis];
}

Uint8 Input::getControllerHat(const int gameControllerNumber) const
{
    return m_gameControllerHat[gameControllerNumber];
}

void Input::afficherPtr(bool response) const
{
    if(response)
        SDL_ShowCursor(SDL_ENABLE);
    else
        SDL_ShowCursor(SDL_DISABLE);
}

void Input::capturePtr(bool response) const
{
    if(response)
        SDL_SetRelativeMouseMode(SDL_TRUE);
    else
        SDL_SetRelativeMouseMode(SDL_FALSE);
}
