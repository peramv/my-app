#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_invalid_rein_dollar : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_invalid_rein_dollar() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_invalid_rein_dollar() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_REIN_DOLLAR")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize reinvest dollar.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize reinvest dollar.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt Dollar-Wiederanlage nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The system does not recognize reinvest dollar.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas le dollar réinvesti.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("The system does not recognize reinvest dollar")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify reinvest dollar and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify reinvest dollar and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Dollar-Wiederanlage und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verifique el monto de reinversión y vuelva a introducirlo.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le dollar réinvesti et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het herinvesteringsbedrag en voer dit opnieuw in")); }
	};
}



