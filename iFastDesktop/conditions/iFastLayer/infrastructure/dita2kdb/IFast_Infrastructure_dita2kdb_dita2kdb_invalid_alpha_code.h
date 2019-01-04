#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_alpha_code : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_alpha_code() { }
		~CIFast_Infrastructure_dita2kdb_dita2kdb_invalid_alpha_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_ALPHA_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this alpha code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this alpha code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diesen Alphacode nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este código alfabético.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce code alphabétique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent deze alfabetische code niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify alpha code and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify alpha code and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Alphacode und geben Sie ihn erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify alpha code and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code alphabétique et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de alfacode en voer deze opnieuw in")); }
	};
}



