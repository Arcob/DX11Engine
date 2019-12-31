#include "ArcTime.h"

namespace DX11Engine {

	float ArcTime::m_deltaTime = 0.000001f;  // 担心出现除0问题默认为略大于0
	float ArcTime::m_fixedDeltaTime = 0.02f;
	float ArcTime::m_timeScale = 1.0f;
	float ArcTime::m_startTime = 0.0f;
	float ArcTime::m_lastFrameTime = 0.0f;

	const float ArcTime::DeltaTime() {
		return m_deltaTime / 1000;
	}

	const float ArcTime::TimeFromStart() {
		return m_lastFrameTime / 1000;
	}

	void ArcTime::Init(float startTime) {
		m_startTime = startTime;
		m_lastFrameTime = startTime;
	}

	void ArcTime::Update(float curTime) {
		m_deltaTime = curTime - m_lastFrameTime;
		if (m_deltaTime <= 0) {
			m_deltaTime = 0.000001f;
		}
		m_lastFrameTime = curTime;
	}
}