﻿#include "DummyButton.h"
#include "Components/Base/GameObject.h"
#include "Utils/DebugUtility.h"
#include <string>

void DummyButton::OnCreate()
{
	owner->GetTransform().SetUnityCoords(false);
	button = owner->AddComponent<Button>();
	fpsText = owner->AddComponent<TextRenderer>();
}

void DummyButton::OnStart()
{
	D2D1_SIZE_F imageSize = button->GetNormalImage()->GetResource()->GetBitmap()->GetSize();
	button->SetRect(imageSize.width, imageSize.height);
	button->AddOnClickEvent(std::bind(&DummyButton::OnClick, this));
	button->AddOnClickEvent([&]() { SetValue(100); });

	Vector2 start = Vector2::Zero();
	Vector2 end = { 2,3 };
	Vector2 dir = (end - start).Normalize();
	fpsText->SetViewportPosition(0.05f, 0.2f);
}

void DummyButton::OnUpdate()
{
	std::wstring str = std::to_wstring(Singleton<DebugUtility>::GetInstance().GetFPSCount());
	fpsText->SetText(str);
	
}

void DummyButton::OnFixedUpdate()
{
	
}

void DummyButton::OnDestroy()
{
	
}

void DummyButton::OnClick()
{
	std::cout << "Button 클릭됨" << std::endl;
}

void DummyButton::SetValue(int value)
{
	std::cout << "클릭 전 value : " << this->value << std::endl;
	this->value = value;
	std::cout << "클릭 후 value : " << this->value << std::endl;
}