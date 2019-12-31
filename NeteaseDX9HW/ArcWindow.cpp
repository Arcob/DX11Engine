#include "ArcWindow.h"
#include "ArcTool.h"

namespace DX11Engine {

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);//��̬�ص�����
	static ArcWindow *applicationHandle;

	ArcWindow::ArcWindow(std::string name, int width, int height) {
		this->m_handle = 0;
		this->m_name = name;
		this->m_width = width;
		this->m_height = height;
		this->escPushed = false;
		ZeroMemory(&m_msg, sizeof(MSG));
	}

	size_t ArcWindow::GetHandle() {
		return m_handle;
	}

	bool ArcWindow::DX11createWindow() {
		WNDCLASSEX wnd;
		LPCWSTR lpcname = ArcTool::stringToLPCWSTR(this->m_name);
		applicationHandle = this;
		m_hinstance = GetModuleHandle(NULL);
		wnd.cbClsExtra = 0;
		wnd.cbSize = sizeof(WNDCLASSEX);
		wnd.cbWndExtra = 0;
		wnd.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
		wnd.hCursor = LoadCursor(NULL, IDC_ARROW);
		wnd.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		wnd.hIconSm = wnd.hIcon;
		wnd.hInstance = m_hinstance;
		wnd.lpfnWndProc = WndProc;
		wnd.lpszClassName = lpcname;
		wnd.lpszMenuName = lpcname;
		wnd.style = CS_VREDRAW | CS_HREDRAW;

		//ע�ᴰ��
		if (!RegisterClassEx(&wnd))
		{
			MessageBox(NULL, L"ע�ᴰ��ʧ��", L"error", 0);
			return false;
		}
		HWND tempHandle = CreateWindowEx(WS_EX_APPWINDOW, lpcname, lpcname, WS_OVERLAPPEDWINDOW, 0, 0, this->m_width, this->m_height, NULL, NULL, m_hinstance, NULL);
		//��ʾ����������Ϊ����
		ShowWindow(tempHandle, SW_SHOW);
		UpdateWindow(tempHandle);
		m_handle = reinterpret_cast<size_t>(tempHandle);
		return true;
	}

	void ArcWindow::TreatMessage(bool &isRunning) {
		if (PeekMessage(&m_msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&m_msg);
			DispatchMessage(&m_msg);
		}
		if (m_msg.message == WM_QUIT)
		{
			isRunning = false;
		}
		else//����esc��Ҳ�˳�
		{
			isRunning = !escPushed;
		}
	}

	static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
			//������Ϣ����MessageHandler����
		default:
			return applicationHandle->MessageHandler(hwnd, message, wparam, lparam);
		}
	}

	LRESULT CALLBACK ArcWindow::MessageHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		switch (message)
		{
			//��ⰴ����Ϣ
		case WM_KEYDOWN:
			if (wparam == VK_ESCAPE)//�û������˳���
				escPushed = true;
			return 0;

			//������Ϣ����windowsȱʡ����
		default:
			return DefWindowProc(hwnd, message, wparam, lparam);
		}
	}
}