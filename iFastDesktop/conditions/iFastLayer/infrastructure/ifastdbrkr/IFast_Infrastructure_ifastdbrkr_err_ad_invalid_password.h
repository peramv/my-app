#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_ad_invalid_password : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_ad_invalid_password() { }
		~CIFast_Infrastructure_ifastdbrkr_err_ad_invalid_password() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_INVALID_PASSWORD")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize this financial institution number.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize this financial institution number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diese Finanzinstitut-Nummer nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce este número de institución financiera.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas ce numéro d'institution financière.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent het nummer van deze financiële instelling niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify financial institution number and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify financial institution number and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Finanzinstitut-Nummer und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify financial institution number and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le numéro d'institution financière et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het nummer van de financiële instelling en voer dit opnieuw in")); }
	};
}



