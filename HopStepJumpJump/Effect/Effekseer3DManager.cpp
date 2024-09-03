#include "Effekseer3DManager.h"
#include "Effect.h"

#include "../Object/ObjectBase.h"

#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cassert>


Effekseer3DManager::Effekseer3DManager()
{
	CsvLoad::GetInstance().EffectLoad(m_dataTable);
}

Effekseer3DManager::~Effekseer3DManager()
{
	/*èàóùñ≥Çµ*/
}

void Effekseer3DManager::Update()
{
}

void Effekseer3DManager::Draw()
{
}

void Effekseer3DManager::Add(const char* fileName, PlayType type, ObjectBase* pObject, VECTOR pos, VECTOR rot)
{
}

void Effekseer3DManager::Delete()
{
}
