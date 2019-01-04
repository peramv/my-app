#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dita2kdb_dita2kdb_oper_not_auth_dlr_br : public CConditionObject
	{
	public:
		CBase_Ifds_dita2kdb_dita2kdb_oper_not_auth_dlr_br() { }
		~CBase_Ifds_dita2kdb_dita2kdb_oper_not_auth_dlr_br() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_OPER_NOT_AUTH_DLR_BR")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("VM returned error code %VAR1%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Broker-Code existiert nicht. Bitte geben Sie neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("VM returned error code %VAR1%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La VM a renvoyé le code d'erreur %VAR1%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("VM returned error code %VAR1%")); }

        // Actions
		virtual DString GetAction_ES_ES() const { return DString(I_("NULL")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



