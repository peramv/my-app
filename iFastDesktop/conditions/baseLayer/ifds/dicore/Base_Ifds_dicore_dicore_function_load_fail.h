#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicore_dicore_function_load_fail : public CConditionObject
	{
	public:
		CBase_Ifds_dicore_dicore_function_load_fail() { }
		~CBase_Ifds_dicore_dicore_function_load_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_FUNCTION_LOAD_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Object required in list")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.  Ungültiger Versuch, CBO für Feld %FIELD% zu verwenden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Object required in list")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Objet requis dans la liste")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Object required in list")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Check system")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Check system")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Check system")); }
	};
}



