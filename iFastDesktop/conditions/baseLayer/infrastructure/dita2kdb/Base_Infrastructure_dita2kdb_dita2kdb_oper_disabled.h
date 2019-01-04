#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_oper_disabled : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_oper_disabled() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_oper_disabled() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_OPER_DISABLED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Operator is disabled.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Operator is disabled.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Der Operator ist gesperrt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El operador está inhabilitado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Opérateur désactivé")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Operator is niet actief")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a supervisor to enable operator ID.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a supervisor to enable operator ID.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Supervisor, um die Operator-ID zu aktivieren.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a supervisor to enable operator ID.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un superviseur pour activer le code d'opérateur.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supervisor om het operator-ID te activeren")); }
	};
}



