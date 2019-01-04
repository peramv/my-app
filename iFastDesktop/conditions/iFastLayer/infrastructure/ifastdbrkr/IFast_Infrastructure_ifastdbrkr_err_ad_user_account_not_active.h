#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_ad_user_account_not_active : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_ad_user_account_not_active() { }
		~CIFast_Infrastructure_ifastdbrkr_err_ad_user_account_not_active() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_USER_ACCOUNT_NOT_ACTIVE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize start month.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize start month.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diesen Startmonat nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce el mes de inicio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas le mois de début.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent beginmaand niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify start month and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify start month and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie den Startmonat und geben Sie ihn erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify start month and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez le mois de début et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de beginmaand en voer deze opnieuw in")); }
	};
}



