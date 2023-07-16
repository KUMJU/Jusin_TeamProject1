#include "stdafx.h"
#include "Field.h"

Field::Field()
{
}

Field::~Field()
{
}

void Field::Initialize()
{
    m_liWall.push_back({ 0, 0, 100, WINCY });
    m_liWall.push_back({ WINCX - 100, 0, WINCX, WINCY });
    m_liWall.push_back({ 0, 0, WINCX, 100 });
    m_liWall.push_back({ 0, 0, 100, WINCY });
}

int Field::Update()
{
    return 0;
}

void Field::Render(HDC hDC)
{
}

void Field::Release()
{
}
