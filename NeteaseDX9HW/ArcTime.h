#pragma once
namespace DX11Engine {

	class ArcTime //��ȡʱ������ArcFrameWork�еļ�ʱ����
	{
	public:
		void static Init(float startTime);
		void static Update(float curTime);
		const static float DeltaTime();//��λ��
		const static float TimeFromStart();//��λ��

	private:
		static float m_deltaTime;
		static float m_fixedDeltaTime;  // ������ʱû���ȷ���
		static float m_timeScale;  // ������ʱû���ȷ���
		static float m_startTime;
		static float m_lastFrameTime;
	};

}

