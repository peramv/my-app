#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dita2kdb_dita2kdb_invalid_corr_code : public CConditionObject
	{
	public:
		CBase_Infrastructure_dita2kdb_dita2kdb_invalid_corr_code() { }
		~CBase_Infrastructure_dita2kdb_dita2kdb_invalid_corr_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_INVALID_CORR_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid correspondence code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Invalid correspondence code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Korrespondenzcode.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Código de correspondencia no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de correspondance invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige correspondentiecode")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify correspondence code and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify correspondence code and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Korrespondenz-Code und geben Sie ihn erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify correspondence code and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code de correspondance et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de correspondentiecode en voer deze opnieuw in")); }
	};
}



