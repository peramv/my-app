#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicore_dilocal_jni_exception_createjvm : public CConditionObject
	{
	public:
		CBase_Ifds_dicore_dilocal_jni_exception_createjvm() { }
		~CBase_Ifds_dicore_dilocal_jni_exception_createjvm() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DILOCAL_JNI_EXCEPTION_CREATEJVM")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_FR_FR() const { return DString(I_("No updates to apply for %CLASS% with key %KEY%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine anwendbaren Aktualisierungen für %CLASS% mit Schlüssel %KEY%.")); }

        // Actions
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
	};
}



