///////////////////////////////////////////////////////////////////////////////
// FoundationExportDefs.h
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
//          Supplement Section 227.7202, Government�s use, duplication or
//          disclosure of the computer software is subject to the restrictions
//          set forth by Rogue Wave Software, Inc.
//
///////////////////////////////////////////////////////////////////////////////

#if !defined __FOUNDATIONEXPORTDEFS__H__
#define __FOUNDATIONEXPORTDEFS__H__

//-------------------------------------//
// Stingray Foundation Library         //
//-------------------------------------//

#ifdef _SFLDLL
	#ifdef _SFL_EXPORT_IMPL
		#define FOUNDATION_API __declspec( dllexport )
		//		#pragma message("FOUNDATION_API: dllexport")
		#define FOUNDATION_GLOBAL_FUNC_API(rettype)	extern "C" rettype __declspec(dllexport) 
	#else
		#define FOUNDATION_API __declspec( dllimport ) 
		//      #pragma message("FOUNDATION_API: dllimport")
		// Reference to a GLOBAL Function 
		#define FOUNDATION_GLOBAL_FUNC_API(rettype)	extern "C" rettype	__declspec(dllimport)
	#endif
#else //  !_SFLDLL
	#define FOUNDATION_API
	// Reference to a GLOBAL Function, these must be inline definitions with no 
	// function prototype.
	#define FOUNDATION_GLOBAL_FUNC_API(rettype)     extern "C" rettype __cdecl // Don't mangle the name. Must use __cdecl here.

#endif

#ifdef _SFLDLL

/////////////////////////////////////////////////////////////////////////////
// Window message map handling

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

		#ifdef _AFXDLL
			#define FOUNDATION_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				FOUNDATION_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				FOUNDATION_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else // !_AFXDLL
			#define FOUNDATION_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				FOUNDATION_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define FOUNDATION_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				FOUNDATION_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				FOUNDATION_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define FOUNDATION_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				FOUNDATION_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif


	#else // !_MSC_VER >= 1310

		#define FOUNDATION_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes
	#if(_MSC_VER >= 1310) 

		#ifdef _AFXDLL
			#define FOUNDATION_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATION_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				FOUNDATION_API static CRuntimeClass* PASCAL GetThisClass(); \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _FOUNDATION_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATION_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				FOUNDATION_API static CRuntimeClass* PASCAL GetThisClass(); \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define FOUNDATION_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _FOUNDATION_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const;

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define FOUNDATION_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATION_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _FOUNDATION_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATION_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define FOUNDATION_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _FOUNDATION_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATION_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define FOUNDATION_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic

		// not serializable, but dynamically constructable
		#define FOUNDATION_DECLARE_DYNCREATE(class_name) \
			FOUNDATION_DECLARE_DYNAMIC(class_name) \
			FOUNDATION_API static CObject* PASCAL CreateObject();

		#define _FOUNDATION_DECLARE_DYNCREATE(class_name) \
			_FOUNDATION_DECLARE_DYNAMIC(class_name) \
			FOUNDATION_API static CObject* PASCAL CreateObject();

		#define FOUNDATION_DECLARE_SERIAL(class_name) \
			_FOUNDATION_DECLARE_DYNCREATE(class_name) \
			AFX_API friend FOUNDATION_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

	// end Helper Macros

#else // !_SFLDLL

	#define FOUNDATION_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define FOUNDATION_DECLARE_DYNAMIC(class_name)		DECLARE_DYNAMIC(class_name)
	#define FOUNDATION_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define FOUNDATION_DECLARE_SERIAL(class_name)		DECLARE_SERIAL(class_name)
	
#endif // _SFLDLL

#endif // __FOUNDATIONEXPORTDEFS__H__