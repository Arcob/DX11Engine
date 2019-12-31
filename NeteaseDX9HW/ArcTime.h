#pragma once
namespace DX11Engine {

	class ArcTime //获取时间依赖ArcFrameWork中的计时函数
	{
	public:
		void static Init(float startTime);
		void static Update(float curTime);
		const static float DeltaTime();//单位秒
		const static float TimeFromStart();//单位秒

	private:
		static float m_deltaTime;
		static float m_fixedDeltaTime;  // 这俩暂时没用先放着
		static float m_timeScale;  // 这俩暂时没用先放着
		static float m_startTime;
		static float m_lastFrameTime;
	};

}

