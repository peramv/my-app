#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicore_dilocal_jni_exception_execute : public CConditionObject
	{
	public:
		CBase_Ifds_dicore_dilocal_jni_exception_execute() { }
		~CBase_Ifds_dicore_dilocal_jni_exception_execute() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DILOCAL_JNI_EXCEPTION_EXECUTE")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Ansicht-Datenobjekte registriert.")); }

        // Actions
		virtual DString GetAction_DE_DE() const { return DString(I_("Check system")); }
	};
}



