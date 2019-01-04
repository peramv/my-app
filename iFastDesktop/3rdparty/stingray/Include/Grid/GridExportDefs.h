///////////////////////////////////////////////////////////////////////////////
// GridExportDefs.h
//
// Copyright (c) 1997-2012 Rogue Wave Software, Inc.  All Rights Reserved.
//
// This computer software is owned by Rogue Wave Software, Inc. and is protected by
// U.S. copyright laws and other laws and by international treaties. This
// computer software is furnished by Rogue Wave Software, Inc. pursuant to a written
// license agreement and may be used, copied, transmitted, and stored
// only in accordance with the terms of such license agreement and with
// the inclusion of the above copyright notice.  This computer software or
// any other copies thereof may not be provided or otherwise made available
// to any other person.
//
// U.S. Government Restricted Rights.  This computer software:
//      (a) was developed at private expense and is in all respects the
//          proprietary information of Rogue Wave Software, Inc.;
//      (b) was not developed with government funds;
//      (c) is a trade secret of Rogue Wave Software, Inc. for all purposes of the
//          Freedom of Information Act; and
//      (d) is a commercial item and thus, pursuant to Section 12.212
//          of the Federal Acquisition Regulations (FAR) and DFAR
//          Supplement Section 227.7202, Government’s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////

#if !defined __GRIDEXPORTDEFS__H__
#define __GRIDEXPORTDEFS__H__

//-------------------------------------//
// Objective Grid                      //
//-------------------------------------//

#ifdef _GXDLL
	#ifdef _OG_EXPORT_IMPL
		#define GRID_API __declspec( dllexport )
//		#pragma message("GRID_API: dllexport")
	#else
		#define GRID_API __declspec( dllimport ) 
//		#pragma message("GRID_API: dllimport")
	#endif
#else //  !_GXDLL
	#define GRID_API
#endif

#ifdef _GXDLL

/////////////////////////////////////////////////////////////////////////////
// Window message map handling

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

		#ifdef _AFXDLL
			#define GRID_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRID_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				GRID_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRID_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				GRID_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define GRID_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRID_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				GRID_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define GRID_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				GRID_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#else // !_MSC_VER >= 1310

		#define GRID_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes
	#if(_MSC_VER >= 1310)

		#ifdef _AFXDLL
			#define GRID_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRID_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				GRID_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const; 
			
			#define _GRID_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRID_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				GRID_API static CRuntimeClass* PASCAL GetThisClass(); \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define GRID_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _GRID_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const;

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define GRID_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRID_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRID_DECLARE_DYNAMIC(class_name) \
			protected: \
				GRID_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define GRID_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _GRID_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				GRID_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define GRID_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic
		
		// not serializable, but dynamically constructable
		#define GRID_DECLARE_DYNCREATE(class_name) \
			GRID_DECLARE_DYNAMIC(class_name) \
			GRID_API static CObject* PASCAL CreateObject();
		
		#define _GRID_DECLARE_DYNCREATE(class_name) \
			_GRID_DECLARE_DYNAMIC(class_name) \
			GRID_API static CObject* PASCAL CreateObject();

		#define GRID_DECLARE_SERIAL(class_name) \
			_GRID_DECLARE_DYNCREATE(class_name) \
			AFX_API friend GRID_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

		#define GRID_DECLARE_CONTROL(class_name) \
			protected: \
				GRID_API static CGXControlClass* PASCAL _GetControlBaseClass(); \
			public: \
				static GX_DATA CGXControlClass ctrl##class_name; \
				GRID_API virtual CGXControlClass* GetControlClass() const; \

		#define GRID_IMPLEMENT_CONTROL(class_name, base_class_name) \
			CGXControlClass* PASCAL class_name::_GetControlBaseClass() \
				{ return CONTROL_CLASS(base_class_name); } \
				GX_DATADEF CGXControlClass class_name::ctrl##class_name = { \
			#class_name, &class_name::_GetControlBaseClass }; \
			CGXControlClass* class_name::GetControlClass() const \
				{ return &class_name::ctrl##class_name; } \


		//Declare Register/////////////////////////////////
		#define GRID_DECLARE_REGISTER() \
		public: \
			GRID_API static LPCTSTR AFXAPI RegisterClass(); \
			GRID_API static void AFXAPI UnregisterClass(); \
			GRID_API static LPCTSTR AFXAPI RegisterClass(HINSTANCE hInstance); \
			GRID_API static void AFXAPI UnregisterClass(HINSTANCE hInstance); \
		protected: \
			GRID_API static LRESULT CALLBACK AFX_EXPORT WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); \
			GRID_API virtual void PostNcDestroy();
		// END GRID_DECLARE_REGISTER


		#ifdef _WIN64

			#define GRID_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
				LPCTSTR AFXAPI class_name::RegisterClass() \
				{ \
					WNDCLASS wndcls;  \
					LPCTSTR szName = _T(#class_name) ; \
					if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
						return szName; \
					wndcls.style = _style ; \
					wndcls.lpfnWndProc = class_name::WndProcHook ; \
					wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
					wndcls.hInstance = AfxGetInstanceHandle() ; \
					wndcls.hIcon = icon ; \
					wndcls.hCursor = cursor ; \
					wndcls.hbrBackground = background ; \
					wndcls.lpszMenuName = NULL ; \
					wndcls.lpszClassName = szName ; \
					if (!::RegisterClass(&wndcls)) \
						AfxThrowResourceException() ; \
					return szName ;  } \
				LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
				{ \
					WNDCLASS wndcls;  \
					LPCTSTR szName = _T(#class_name) ; \
					if (::GetClassInfo(hInstance, szName, &wndcls)) \
						return szName; \
					wndcls.style = _style ; \
					wndcls.lpfnWndProc = class_name::WndProcHook ; \
					wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
					wndcls.hInstance = hInstance ; \
					wndcls.hIcon = icon ; \
					wndcls.hCursor = cursor ; \
					wndcls.hbrBackground = background ; \
					wndcls.lpszMenuName = NULL ; \
					wndcls.lpszClassName = szName ; \
					if (!::RegisterClass(&wndcls)) \
						AfxThrowResourceException() ; \
					return szName ;  } \
				LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
				{ \
					class_name * pWnd = new class_name(); \
					pWnd->Attach(hWnd); \
					GXGetAppState()->m_ctlusrState.m_ctrlmap[pWnd] = 1; \
					::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (SEC_LONG)AfxWndProc); \
					return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
				void AFXAPI class_name::UnregisterClass() \
				{ \
					::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
				void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
				{ \
					::UnregisterClass( _T(#class_name) , hInstance );  } \
				void class_name::PostNcDestroy() \
				{ \
					WORD w; \
					if (GXGetAppState()->m_ctlusrState.m_ctrlmap.Lookup(this, w)) \
					{ \
						delete this; \
						GXGetAppState()->m_ctlusrState.m_ctrlmap.RemoveKey(this); \
					} \
				}
			// END GRID_IMPLEMENT_REGISTER

		#else	//WIN32

			#define GRID_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
				LPCTSTR AFXAPI class_name::RegisterClass() \
				{ \
					WNDCLASS wndcls;  \
					LPCTSTR szName = _T(#class_name) ; \
					if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
						return szName; \
					wndcls.style = _style ; \
					wndcls.lpfnWndProc = class_name::WndProcHook ; \
					wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
					wndcls.hInstance = AfxGetInstanceHandle() ; \
					wndcls.hIcon = icon ; \
					wndcls.hCursor = cursor ; \
					wndcls.hbrBackground = background ; \
					wndcls.lpszMenuName = NULL ; \
					wndcls.lpszClassName = szName ; \
					if (!::RegisterClass(&wndcls)) \
						AfxThrowResourceException() ; \
					return szName ;  } \
				LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
				{ \
					WNDCLASS wndcls;  \
					LPCTSTR szName = _T(#class_name) ; \
					if (::GetClassInfo(hInstance, szName, &wndcls)) \
						return szName; \
					wndcls.style = _style ; \
					wndcls.lpfnWndProc = class_name::WndProcHook ; \
					wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
					wndcls.hInstance = hInstance ; \
					wndcls.hIcon = icon ; \
					wndcls.hCursor = cursor ; \
					wndcls.hbrBackground = background ; \
					wndcls.lpszMenuName = NULL ; \
					wndcls.lpszClassName = szName ; \
					if (!::RegisterClass(&wndcls)) \
						AfxThrowResourceException() ; \
					return szName ;  } \
				LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
				{ \
					class_name * pWnd = new class_name(); \
					pWnd->Attach(hWnd); \
					GXGetAppState()->m_ctlusrState.m_ctrlmap[pWnd] = 1; \
					::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)AfxWndProc); \
					return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
				void AFXAPI class_name::UnregisterClass() \
				{ \
					::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
				void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
				{ \
					::UnregisterClass( _T(#class_name) , hInstance );  } \
				void class_name::PostNcDestroy() \
				{ \
					WORD w; \
					if (GXGetAppState()->m_ctlusrState.m_ctrlmap.Lookup(this, w)) \
					{ \
						delete this; \
						GXGetAppState()->m_ctlusrState.m_ctrlmap.RemoveKey(this); \
					} \
				}
			// END GRID_IMPLEMENT_REGISTER

		#endif	//_WIN64
		//Declare Register/////////////////////////////////

	// end Helper Macros

#else // !_GXDLL Static Library

	#define GRID_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define GRID_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)
	#define GRID_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define GRID_DECLARE_SERIAL(class_name)		DECLARE_SERIAL(class_name)

	#define GRID_DECLARE_CONTROL(class_name) \
		public: \
			static CGXControlClass GXNEAR ctrl##class_name; \
			virtual CGXControlClass* GetControlClass() const; \

	#define GRID_IMPLEMENT_CONTROL(class_name, base_class_name) \
		CGXControlClass GXNEAR class_name::ctrl##class_name = { \
		#class_name, CONTROL_CLASS(base_class_name) }; \
		CGXControlClass* class_name::GetControlClass() const \
			{ return &class_name::ctrl##class_name; } \

	//Declare Register/////////////////////////////////
	#define GRID_DECLARE_REGISTER() \
		public: \
			GRID_API static LPCTSTR AFXAPI RegisterClass(); \
			GRID_API static void AFXAPI UnregisterClass(); \
			GRID_API static LPCTSTR AFXAPI RegisterClass(HINSTANCE hInstance); \
			GRID_API static void AFXAPI UnregisterClass(HINSTANCE hInstance); \
			GRID_API static CMapPtrToWord GXNEAR _gxregmap; \
		protected: \
			GRID_API static LRESULT CALLBACK AFX_EXPORT WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); \
			GRID_API virtual void PostNcDestroy();
		// END GRID_DECLARE_REGISTER

	#ifdef _WIN64

		#define GRID_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
			CMapPtrToWord GXNEAR class_name::_gxregmap; \
			LPCTSTR AFXAPI class_name::RegisterClass() \
			{ \
				WNDCLASS wndcls;  \
				LPCTSTR szName = _T(#class_name) ; \
				if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
					return szName; \
				wndcls.style = _style ; \
				wndcls.lpfnWndProc = class_name::WndProcHook ; \
				wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
				wndcls.hInstance = AfxGetInstanceHandle() ; \
				wndcls.hIcon = icon ; \
				wndcls.hCursor = cursor ; \
				wndcls.hbrBackground = background ; \
				wndcls.lpszMenuName = NULL ; \
				wndcls.lpszClassName = szName ; \
				if (!::RegisterClass(&wndcls)) \
					AfxThrowResourceException() ; \
				return szName ;  } \
			LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
			{ \
				WNDCLASS wndcls;  \
				LPCTSTR szName = _T(#class_name) ; \
				if (::GetClassInfo(hInstance, szName, &wndcls)) \
					return szName; \
				wndcls.style = _style ; \
				wndcls.lpfnWndProc = class_name::WndProcHook ; \
				wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
				wndcls.hInstance = hInstance ; \
				wndcls.hIcon = icon ; \
				wndcls.hCursor = cursor ; \
				wndcls.hbrBackground = background ; \
				wndcls.lpszMenuName = NULL ; \
				wndcls.lpszClassName = szName ; \
				if (!::RegisterClass(&wndcls)) \
					AfxThrowResourceException() ; \
				return szName ;  } \
			LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
			{ \
				class_name * pWnd = new class_name(); \
				pWnd->Attach(hWnd); \
				_gxregmap[pWnd] = 1; \
				::SetWindowLongPtr(hWnd, GWLP_WNDPROC, (SEC_LONG)AfxWndProc); \
				return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
			void AFXAPI class_name::UnregisterClass() \
			{ \
				::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
			void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
			{ \
				::UnregisterClass( _T(#class_name) , hInstance );  } \
			void class_name::PostNcDestroy() \
			{ \
				WORD w; \
				if (_gxregmap.Lookup(this, w)) \
				{ \
					delete this; \
					_gxregmap.RemoveKey(this); \
				} \
			}
		// END GRID_IMPLEMENT_REGISTER

	#else	//WIN32

		#define GRID_IMPLEMENT_REGISTER(class_name, _style, icon, cursor, background) \
			CMapPtrToWord GXNEAR class_name::_gxregmap; \
			LPCTSTR AFXAPI class_name::RegisterClass() \
			{ \
				WNDCLASS wndcls;  \
				LPCTSTR szName = _T(#class_name) ; \
				if (::GetClassInfo(AfxGetInstanceHandle(), szName, &wndcls)) \
					return szName; \
				wndcls.style = _style ; \
				wndcls.lpfnWndProc = class_name::WndProcHook ; \
				wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
				wndcls.hInstance = AfxGetInstanceHandle() ; \
				wndcls.hIcon = icon ; \
				wndcls.hCursor = cursor ; \
				wndcls.hbrBackground = background ; \
				wndcls.lpszMenuName = NULL ; \
				wndcls.lpszClassName = szName ; \
				if (!::RegisterClass(&wndcls)) \
					AfxThrowResourceException() ; \
				return szName ;  } \
			LPCTSTR AFXAPI class_name::RegisterClass(HINSTANCE hInstance) \
			{ \
				WNDCLASS wndcls;  \
				LPCTSTR szName = _T(#class_name) ; \
				if (::GetClassInfo(hInstance, szName, &wndcls)) \
					return szName; \
				wndcls.style = _style ; \
				wndcls.lpfnWndProc = class_name::WndProcHook ; \
				wndcls.cbClsExtra = wndcls.cbWndExtra = 0 ; \
				wndcls.hInstance = hInstance ; \
				wndcls.hIcon = icon ; \
				wndcls.hCursor = cursor ; \
				wndcls.hbrBackground = background ; \
				wndcls.lpszMenuName = NULL ; \
				wndcls.lpszClassName = szName ; \
				if (!::RegisterClass(&wndcls)) \
					AfxThrowResourceException() ; \
				return szName ;  } \
			LRESULT CALLBACK AFX_EXPORT class_name::WndProcHook(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) \
			{ \
				class_name * pWnd = new class_name(); \
				pWnd->Attach(hWnd); \
				_gxregmap[pWnd] = 1; \
				::SetWindowLong(hWnd, GWL_WNDPROC, (DWORD)AfxWndProc); \
				return ::CallWindowProc(AfxWndProc, hWnd, msg, wParam, lParam); } \
			void AFXAPI class_name::UnregisterClass() \
			{ \
				::UnregisterClass( _T(#class_name) , AfxGetInstanceHandle() );  } \
			void AFXAPI class_name::UnregisterClass(HINSTANCE hInstance) \
			{ \
				::UnregisterClass( _T(#class_name) , hInstance );  } \
			void class_name::PostNcDestroy() \
			{ \
				WORD w; \
				if (_gxregmap.Lookup(this, w)) \
				{ \
					delete this; \
					_gxregmap.RemoveKey(this); \
				} \
			}
		// END GRID_IMPLEMENT_REGISTER

	#endif	// _WIN64

	//Declare Register/////////////////////////////////

#endif // GRID

#endif // __GRIDEXPORTDEFS__H__