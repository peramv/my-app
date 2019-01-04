#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_vmreq_failed : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_vmreq_failed() { }
		~CIFast_Infrastructure_ifastdbrkr_ifastdbrkr_vmreq_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_VMREQ_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this date.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt dieses Datum nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce esta fecha.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas cette date.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent deze datum niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify date and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify date and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das Datum und geben Sie es erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify date and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez la date et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de datum en voer deze opnieuw in")); }
	};
}



