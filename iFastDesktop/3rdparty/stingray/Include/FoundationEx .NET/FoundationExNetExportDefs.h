///////////////////////////////////////////////////////////////////////////////
// FoundationExExportDefs.h
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

#if !defined __FOUNDATIONEXNETEXPORTDEFS__H__
#define __FOUNDATIONEXNETEXPORTDEFS__H__

namespace sflexnet
{

//-----------------------------------------------//
// Stingray Foundation Library Extension         //
//-----------------------------------------------//

#ifdef _SFLEXNETDLL
	#ifdef _SFLEXNET_EXPORT_IMPL
		#define FOUNDATIONEXNET_API __declspec( dllexport )
		//		#pragma message("FOUNDATIONEXNET_API: dllexport")
		#define FOUNDATIONEXNET_GLOBAL_FUNC_API(rettype)	extern "C" rettype __declspec(dllexport) 
	#else
		#define FOUNDATIONEXNET_API __declspec( dllimport ) 
		//      #pragma message("FOUNDATIONEXNET_API: dllimport")
		// Reference to a GLOBAL Function 
		#define FOUNDATIONEXNET_GLOBAL_FUNC_API(rettype)	extern "C" rettype	__declspec(dllimport)
	#endif
#else //  !_SFLEXNETDLL
	#define FOUNDATIONEXNET_API
	// Reference to a GLOBAL Function, these must be inline definitions with no 
	// function prototype.
	#define FOUNDATIONEXNET_GLOBAL_FUNC_API(rettype)     extern "C" rettype __cdecl // Don't mangle the name. Must use __cdecl here.

#endif // _SFLEXNETDLL

#ifdef _SFLEXNETDLL

/////////////////////////////////////////////////////////////////////////////
// Window message map handling

	#if(_MSC_VER >= 1310) // Visual Studio 2003 +

		#ifdef _AFXDLL
			#define FOUNDATIONEXNET_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				FOUNDATIONEXNET_API static const AFX_MSGMAP* PASCAL GetThisMessageMap(); \
				FOUNDATIONEXNET_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else // !_AFXDLL
			#define FOUNDATIONEXNET_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static const AFX_MSGMAP messageMap; \
				FOUNDATIONEXNET_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif

	#elif(_MSC_VER == 1200) // MSVC6

		#ifdef _AFXDLL
			#define FOUNDATIONEXNET_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				FOUNDATIONEXNET_API static const AFX_MSGMAP* PASCAL _GetBaseMessageMap(); \
				FOUNDATIONEXNET_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#else
			#define FOUNDATIONEXNET_DECLARE_MESSAGE_MAP() \
			private: \
				static const AFX_MSGMAP_ENTRY _messageEntries[]; \
			protected: \
				static AFX_DATA const AFX_MSGMAP messageMap; \
				FOUNDATIONEXNET_API virtual const AFX_MSGMAP* GetMessageMap() const; \

		#endif


	#else // !_MSC_VER >= 1310

		#define FOUNDATIONEXNET_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()

	#endif

	//////////////////////////////////////////////////////////////////////////////
	// Helper macros for declaring CRuntimeClass compatible classes
	#if(_MSC_VER >= 1310) 

		#ifdef _AFXDLL
			#define FOUNDATIONEXNET_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATIONEXNET_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const CRuntimeClass class##class_name; \
				FOUNDATIONEXNET_API static CRuntimeClass* PASCAL GetThisClass(); \
				FOUNDATIONEXNET_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _FOUNDATIONEXNET_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATIONEXNET_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static CRuntimeClass class##class_name; \
				FOUNDATIONEXNET_API static CRuntimeClass* PASCAL GetThisClass(); \
				FOUNDATIONEXNET_API virtual CRuntimeClass* GetRuntimeClass() const; 

		#else // !_AFXDLL

			#define FOUNDATIONEXNET_DECLARE_DYNAMIC(class_name) \
			public: \
				static const CRuntimeClass class##class_name; \
				FOUNDATIONEXNET_API virtual CRuntimeClass* GetRuntimeClass() const;
			
			#define _FOUNDATIONEXNET_DECLARE_DYNAMIC(class_name) \
			public: \
				static CRuntimeClass class##class_name; \
				FOUNDATIONEXNET_API virtual CRuntimeClass* GetRuntimeClass() const;

		#endif // MFC DLL/LIB

	#elif(_MSC_VER == 1200)

		#ifdef _AFXDLL
			#define FOUNDATIONEXNET_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATIONEXNET_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATIONEXNET_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _FOUNDATIONEXNET_DECLARE_DYNAMIC(class_name) \
			protected: \
				FOUNDATIONEXNET_API static CRuntimeClass* PASCAL _GetBaseClass(); \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATIONEXNET_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#else
			#define FOUNDATIONEXNET_DECLARE_DYNAMIC(class_name) \
			public: \
				static const AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATIONEXNET_API virtual CRuntimeClass* GetRuntimeClass() const; \

			#define _FOUNDATIONEXNET_DECLARE_DYNAMIC(class_name) \
			public: \
				static AFX_DATA CRuntimeClass class##class_name; \
				FOUNDATIONEXNET_API virtual CRuntimeClass* GetRuntimeClass() const; \

		#endif // _AFXDLL

	#else

		#define FOUNDATIONEXNET_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)

	#endif // Declare Dynamic

		// not serializable, but dynamically constructable
		#define FOUNDATIONEXNET_DECLARE_DYNCREATE(class_name) \
			FOUNDATIONEXNET_DECLARE_DYNAMIC(class_name) \
			FOUNDATIONEXNET_API static CObject* PASCAL CreateObject();

		#define _FOUNDATIONEXNET_DECLARE_DYNCREATE(class_name) \
			_FOUNDATIONEXNET_DECLARE_DYNAMIC(class_name) \
			FOUNDATIONEXNET_API static CObject* PASCAL CreateObject();

		#define FOUNDATIONEXNET_DECLARE_SERIAL(class_name) \
			_FOUNDATIONEXNET_DECLARE_DYNCREATE(class_name) \
			AFX_API friend FOUNDATIONEXNET_API CArchive& AFXAPI operator>>(CArchive& ar, class_name* &pOb);

	// end Helper Macros

#else // !_SFLEXNETDLL

	#define FOUNDATIONEXNET_DECLARE_MESSAGE_MAP()			DECLARE_MESSAGE_MAP()
	#define FOUNDATIONEXNET_DECLARE_DYNAMIC(class_name)	DECLARE_DYNAMIC(class_name)
	#define FOUNDATIONEXNET_DECLARE_DYNCREATE(class_name)	DECLARE_DYNCREATE(class_name)
	#define FOUNDATIONEXNET_DECLARE_SERIAL(class_name)		DECLARE_SERIAL(class_name)
	
#endif // _SFLEXNETDLL

} // namespace sflex

#endif // __FOUNDATIONEXNETEXPORTDEFS__H__