#include <windows.h>
#include "SysHook.h"
#include <jni.h>

HINSTANCE hInst = NULL;

JavaVM * jvm = NULL;
jobject hookObj_kb = NULL;
jobject hookObj_ms = NULL;
jobject g_kl = NULL;

jmethodID processKeyID_kb = NULL;
jmethodID processKeyID_ms = NULL;
DWORD hookThreadId = 0;


LONG	g_mouseLocX = -1;	// x-location of mouse position
LONG	g_mouseLocY = -1;	// y-location of mouse position


extern "C" 
BOOL APIENTRY DllMain(HINSTANCE _hInst, DWORD reason, LPVOID reserved) 
{
	switch (reason) 
	{
		case DLL_PROCESS_ATTACH:
		printf("C++: DllMain - DLL_PROCESS_ATTACH.\n");
		hInst = _hInst;
		break;
		default:
		break;
	}

return TRUE;
}



LRESULT CALLBACK MouseTracker(int nCode, WPARAM wParam, LPARAM lParam)
{
	JNIEnv * env;
	KBDLLHOOKSTRUCT * p = (KBDLLHOOKSTRUCT *)lParam;
	
	if (jvm->AttachCurrentThread((void **)&env, NULL) >= 0) 
	{
		
		if (nCode==HC_ACTION) 
		{
		MOUSEHOOKSTRUCT* pStruct = (MOUSEHOOKSTRUCT*)lParam;
		if (pStruct->pt.x != g_mouseLocX || pStruct->pt.y != g_mouseLocY)
		{
			env->CallVoidMethod(hookObj_ms, processKeyID_ms, (jint)pStruct->pt.x,(jint)pStruct->pt.y, g_kl);
			g_mouseLocX = pStruct->pt.x;
			g_mouseLocY = pStruct->pt.y;
		}
		
	}
		
		
	}
	else 
	{
		printf("C++: LowLevelKeyboardProc - Error on the attach current thread.\n");
	}
		
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}





LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) 
{
	JNIEnv * env;
	KBDLLHOOKSTRUCT * p = (KBDLLHOOKSTRUCT *)lParam;
	
	if (jvm->AttachCurrentThread((void **)&env, NULL) >= 0) 
	{
		switch (wParam) 
		{
			case WM_KEYDOWN:
			case WM_SYSKEYDOWN:
     		env->CallVoidMethod(hookObj_kb, processKeyID_kb, (jboolean)TRUE, p->vkCode,g_kl);
			break;
			case WM_KEYUP:
			case WM_SYSKEYUP:
            env->CallVoidMethod(hookObj_kb, processKeyID_kb, (jboolean)FALSE, p->vkCode,g_kl);
			break;
			default:
			break;
		}
	}
	else 
	{
		printf("C++: LowLevelKeyboardProc - Error on the attach current thread.\n");
	}
	
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

void MsgLoop() 
{
	MSG message;
	while (GetMessage(&message, NULL, 0, 0)) 
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}



JNIEXPORT void JNICALL Java_SysHook_registerHook(JNIEnv * env, jobject obj,jobject kl) 
{
	HHOOK hookHandle_ms = SetWindowsHookEx(WH_MOUSE_LL, MouseTracker, hInst, 0);
	HHOOK hookHandle_kb = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelKeyboardProc, hInst, 0);
	

	g_kl = kl;
	
	if (hookHandle_ms == NULL) 
	{
		printf("C++: Java_SysHook_registerKeyHook - Hook failed!\n");
		return;
	}
	else 
	{
		printf("C++: Java_SysHook_registerKeyHook - Hook successful\n");
	}
	
	if (hookHandle_kb == NULL) 
	{
		printf("C++: Java_SysHook_registerKeyHook - Hook failed!\n");
		return;
	}
	else 
	{
		printf("C++: Java_SysHook_registerKeyHook - Hook successful\n");
	}
	
	hookObj_kb = env->NewGlobalRef(obj);
	jclass cls_kb = env->GetObjectClass(hookObj_kb);
	processKeyID_kb = env->GetMethodID(cls_kb, "processKey", "(ZILGlobalEventListener;)V");
		
	hookObj_ms = env->NewGlobalRef(obj);
	jclass cls_ms = env->GetObjectClass(hookObj_ms);
	processKeyID_ms = env->GetMethodID(cls_ms, "mouseMoved", "(IILGlobalEventListener;)V");
	
	env->GetJavaVM(&jvm);
	hookThreadId = GetCurrentThreadId();
	
	MsgLoop();
	
	if (!UnhookWindowsHookEx(hookHandle_kb))
	{
		printf("C++: Java_SysHook_registerKeyHook - Unhook failed\n");
	}
	else
	{
		printf("C++: Java_SysHook_registerKeyHook - Unhook successful\n");
	}
	
	if (!UnhookWindowsHookEx(hookHandle_ms))
	{
		printf("C++: Java_SysHook_registerKeyHook - Unhook failed\n");
	}
	else
	{
		printf("C++: Java_SysHook_registerKeyHook - Unhook successful\n");
	}
}




JNIEXPORT void JNICALL Java_SysHook_unRegisterHook(JNIEnv *env, jobject object) 
{
	if (hookThreadId == 0)
	return;
	
	printf("C++: Java_SysHook_unRegisterKeyHook - call PostThreadMessage.\n");
	PostThreadMessage(hookThreadId, WM_QUIT, 0, 0L);
}
