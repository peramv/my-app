#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_operator_not_passed : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_operator_not_passed() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_operator_not_passed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_OPERATOR_NOT_PASSED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This tax type is not locked in.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("This tax type is not locked in.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Steuerart ist nicht festgelegt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Este tipo tributario no está bloqueado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ce type d'imposition n'est pas immobilisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Dit belastingtype is niet vergrendeld")); }

        // Actions
	};
}



