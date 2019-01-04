// This is a part of the Objective Grid Pro C++ Library.
// Copyright � 1999-2004 Quovadx, Inc.  All Rights Reserved.
// 
// 
// This computer software is owned by Quovadx, Inc. and is protected by 
// U.S. copyright laws and other laws and by international treaties. This 
// computer software is furnished by Quovadx, Inc. pursuant to a written 
// license agreement and may be used, copied, transmitted, and stored 
// only in accordance with the terms of such license agreement and with 
// the inclusion of the above copyright notice.  This computer software or 
// any other copies thereof may not be provided or otherwise made available 
// to any other person.
// 
// U.S. Government Restricted Rights.  This computer software: 
//      (a) was developed at private expense and is in all respects the 
//          proprietary information of Quovadx, Inc.; 
//      (b) was not developed with government funds; 
//      (c) is a trade secret of Quovadx, Inc. for all purposes of the 
//          Freedom of Information Act; and 
//      (d) is a commercial item and thus, pursuant to Section 12.212 
//          of the Federal Acquisition Regulations (FAR) and DFAR 
//          Supplement Section 227.7202, Government�s use, duplication or 
//          disclosure of the computer software is subject to the restrictions 
//          set forth by Quovadx, Inc.
//
//
// This source code is only intended as a supplement to
// the Objective Grid Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding
// the Objective Grid product.
//
// Author: Daniel Jebaraj
//

// [VC7] Modified the runtime macros for VC7.

#ifndef _GXEXMAC_H__
#define _GXEXMAC_H__

#define GXEXRUNTIME_CLASS(class_name, temp_arg, temp_arg1) ((CRuntimeClass*)(&class_name<temp_arg, temp_arg1>::class##class_name))

#ifdef _AFXDLL // AFXDLL

#if (_MFC_VER >= 0x0700) // VC7

#define GXEXIMPLEMENT_RUNTIMECLASS(class_name, base_class_name, temp_arg, temp_arg1, wSchema, pfnNew)\
template<class temp_arg, class temp_arg1>\
CRuntimeClass* PASCAL class_name<temp_arg, temp_arg1>::GetThisClass()\
	{ return _RUNTIME_CLASS_T2(class_name, temp_arg, temp_arg1); }\
template<class temp_arg,  class temp_arg1>\
const AFX_DATADEF CRuntimeClass class_name<temp_arg, temp_arg1>::class##class_name = {\
		#class_name, sizeof(class##class_name), wSchema, pfnNew,\
		&base_class_name::GetThisClass, NULL };\
template<class temp_arg,  class temp_arg1>\
CRuntimeClass* class_name<temp_arg, temp_arg1>::GetRuntimeClass() const\
	{ return _RUNTIME_CLASS_T2(class_name, temp_arg, temp_arg1); }

#define GXEXDERIMPLEMENT_RUNTIMECLASS(class_name, base_class_name, temp_arg, temp_arg1, wSchema, pfnNew)\
CRuntimeClass* PASCAL class_name::GetThisClass()\
	{ return _RUNTIME_CLASS(class_name); }\
const AFX_DATADEF CRuntimeClass class_name::class##class_name = {\
	#class_name, sizeof(class##class_name), wSchema, pfnNew,\
	&base_class_name<temp_arg, temp_arg1>::GetThisClass, NULL };\
CRuntimeClass* class_name::GetRuntimeClass() const\
	{ return _RUNTIME_CLASS(class_name); }

#else // VC6

#define GXEXIMPLEMENT_RUNTIMECLASS(class_name, base_class_name, temp_arg, temp_arg1, wSchema, pfnNew)\
template<class temp_arg, class temp_arg1>\
CRuntimeClass* PASCAL class_name<temp_arg, temp_arg1>::_GetBaseClass()\
	{ return RUNTIME_CLASS(base_class_name); }\
template<class temp_arg,  class temp_arg1>\
const AFX_DATADEF CRuntimeClass class_name<temp_arg, temp_arg1>::class##class_name = {\
		#class_name, sizeof(class##class_name), wSchema, pfnNew,\
		&class_name::_GetBaseClass, NULL };\
template<class temp_arg,  class temp_arg1>\
CRuntimeClass* class_name<temp_arg, temp_arg1>::GetRuntimeClass() const\
	{ return GXEXRUNTIME_CLASS(class_name, temp_arg, temp_arg1); }


#define GXEXDERIMPLEMENT_RUNTIMECLASS(class_name, base_class_name, temp_arg, temp_arg1, wSchema, pfnNew)\
CRuntimeClass* PASCAL class_name::_GetBaseClass()\
	{ return GXEXRUNTIME_CLASS(base_class_name, temp_arg, temp_arg1); }\
const AFX_DATADEF CRuntimeClass class_name::class##class_name = {\
	#class_name, sizeof(class##class_name), wSchema, pfnNew,\
	&class_name::_GetBaseClass, NULL };\
CRuntimeClass* class_name::GetRuntimeClass() const\
	{ return RUNTIME_CLASS(class_name); }

#endif

#else // Static Lib (VC6 & VC7)

#define GXEXIMPLEMENT_RUNTIMECLASS(class_name, base_class_name, temp_arg, temp_arg1, wSchema, pfnNew) \
template<class temp_arg, class temp_arg1>\
const AFX_DATADEF CRuntimeClass class_name<temp_arg, temp_arg1>::class##class_name = { \
		#class_name, sizeof(class class_name<temp_arg, temp_arg1>), wSchema, pfnNew, \
			RUNTIME_CLASS(base_class_name), NULL }; \
template<class temp_arg, class temp_arg1>\
CRuntimeClass* class_name<temp_arg, temp_arg1>::GetRuntimeClass() const \
		{ return GXEXRUNTIME_CLASS(class_name, temp_arg, temp_arg1); } \

#define GXEXDERIMPLEMENT_RUNTIMECLASS(class_name, base_class_name, temp_arg, temp_arg1, wSchema, pfnNew) \
const AFX_DATADEF CRuntimeClass class_name::class##class_name = { \
		#class_name, sizeof(class class_name), wSchema, pfnNew, \
			GXEXRUNTIME_CLASS(base_class_name, temp_arg, temp_arg1), NULL }; \
	CRuntimeClass* class_name::GetRuntimeClass() const \
		{ return RUNTIME_CLASS(class_name); }
#endif

#define GXEXIMPLEMENT_DYNAMIC(class_name, base_class_name, temp_arg, temp_arg1) \
	GXEXIMPLEMENT_RUNTIMECLASS(class_name, base_class_name, temp_arg, temp_arg1, 0xFFFF, NULL)

#define GXEXIMPLEMENT_DYNCREATE(class_name, base_class_name, temp_arg, temp_arg1) \
	CObject* PASCAL class_name::CreateObject() \
		{ return new class_name; } \
	GXEXDERIMPLEMENT_RUNTIMECLASS(class_name, base_class_name, temp_arg, temp_arg1, 0xFFFF, \
		class_name::CreateObject)

#define GXEX_TRY(fn)\
try\
{\
	fn ;\
}\
catch(READSEEKEXCEP* pErr)\
{\
	pErr->ReportError();\
	pErr->Destroy();\
}



#endif //_GXEXMAC_H__
