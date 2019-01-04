#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicore_dilocal_jni_exception_locate : public CConditionObject
	{
	public:
		CBase_Ifds_dicore_dilocal_jni_exception_locate() { }
		~CBase_Ifds_dicore_dilocal_jni_exception_locate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DILOCAL_JNI_EXCEPTION_LOCATE")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("Update invalid for %LABEL%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aktualisierung ungültig für %LABEL%")); }

        // Actions
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify that event is valid.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie, ob das Ereignis gültig ist.")); }
	};
}



