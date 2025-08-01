﻿#include "pch.h"
#include "Input.h"
#include "../Datas/EngineData.h"

float Input::MouseX = 0.0f;
float Input::MouseY = 0.0f;
float Input::MouseDeltaX = 0.0f;
float Input::MouseDeltaY = 0.0f;

int Input::wheelDelta = 0.0f;
bool Input::leftButtonDown = false;
bool Input::rightButtonDown = false;
bool Input::middleButtonDown = false;

bool Input::IsTrackingMouse = false;
bool Input::IsMouseInside = false;

void Input::Update() 
{
    memcpy_s(prevState, sizeof(prevState), currState, sizeof(currState));
    for (int i = 0; i < 256; i++) {
        currState[i] = GetAsyncKeyState(i);
    }
}

bool Input::IsKeyDown(int vKey) 
{
    return (currState[vKey] & 0x8000) != 0;
}

bool Input::IsKeyPressed(int vKey) 
{
    return (!(prevState[vKey] & 0x8000) && (currState[vKey] & 0x8000));
}

bool Input::IsKeyReleased(int vKey) 
{
    return ((prevState[vKey] & 0x8000) && !(currState[vKey] & 0x8000));
}

bool Input::IsMouseDown(MouseButton button)
{
    
    switch (button)
    {
    case Left: return leftButtonDown;
    case Right: return rightButtonDown;
    case Middle: return middleButtonDown;
    }

    return false;
}

void Input::ResetMouseEventFrameState()
{
    Input::MouseDeltaX = 0.0f;
    Input::MouseDeltaY = 0.0f;
    Input::wheelDelta = 0.0f;
}

void Input::ProcessMouseMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    if (!IsTrackingMouse && message == WM_MOUSEMOVE)
    {
        TRACKMOUSEEVENT tme = {};
        tme.cbSize = sizeof(tme);
        tme.dwFlags = TME_LEAVE;
        tme.hwndTrack = hwnd;
        TrackMouseEvent(&tme);
        IsTrackingMouse = true;
        IsMouseInside = true;
    }

    if (message == WM_MOUSEMOVE)
    {
        int newMouseX = LOWORD(lParam);
        int newMouseY = HIWORD(lParam);
        Input::MouseDeltaX = newMouseX - Input::MouseX;
        Input::MouseDeltaY = newMouseY - Input::MouseY;
        Input::MouseX = newMouseX;
        Input::MouseY = newMouseY;
    }

    switch (message)
    {
    case WM_LBUTTONDOWN: leftButtonDown = true; break;      // 왼쪽 버튼 누름
    case WM_LBUTTONUP:   leftButtonDown = false; break;     // 왼쪽 버튼 땜
    case WM_RBUTTONDOWN: rightButtonDown = true; break;     // 오른쪽 버튼 누름
    case WM_RBUTTONUP:   rightButtonDown = false; break;    // 오른쪽 버튼 땜
    case WM_MBUTTONDOWN: middleButtonDown = true; break;    // 가운데 버튼 누름
    case WM_MBUTTONUP:   middleButtonDown = false; break;   // 가운데 버튼 땜
    case WM_MOUSEWHEEL:                                     // 휠 델타 값 가져오기
        wheelDelta = GET_WHEEL_DELTA_WPARAM(wParam);
        break;
    }

    // std::cout << "Mouse : " << Input::MouseX << ", " << Input::MouseY << std::endl;
    // std::cout << "Mouse Delta : " << Input::MouseDeltaX << ", " << Input::MouseDeltaY << std::endl;
    // std::cout << "wheelDelta Delta : " << Input::wheelDelta << std::endl;
    // std::cout << "Left Button: " << leftButtonDown << std::boolalpha << std::endl;
    // std::cout << "Right Button: " << rightButtonDown << std::boolalpha << std::endl;
    // std::cout << "Middle Button: " << middleButtonDown << std::boolalpha << std::endl;
}

void Input::ResetMouseOnOutOfBounds()
{
    leftButtonDown = false;
    rightButtonDown = false;
    middleButtonDown = false;
    IsTrackingMouse = false;
    IsMouseInside = false;
}