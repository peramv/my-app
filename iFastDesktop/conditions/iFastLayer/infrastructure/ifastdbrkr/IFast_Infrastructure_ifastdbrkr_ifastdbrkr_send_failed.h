#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_send_failed : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_send_failed() { }
		~CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_send_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_SEND_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this account number.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this account number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diese Kontonummer nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este número de cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce numéro de compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent dit accountnummer niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify account number and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify account number and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Kontonummer und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify account number and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le numéro de compte et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het accountnummer en voer dit opnieuw in")); }
	};
}



