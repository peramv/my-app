#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_input_account_is_not_rif : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_input_account_is_not_rif() { }
		~CIFast_Infrastructure_ifastdbrkr_err_input_account_is_not_rif() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INPUT_ACCOUNT_IS_NOT_RIF")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this management code.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this management code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diesen Managementcode nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este código de administración.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce code de gestion.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent deze beheercode niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify management code and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify management code and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Management-Code und geben Sie ihn erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify management code and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le code de gestion et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de beheercode en voer deze opnieuw in")); }
	};
}



