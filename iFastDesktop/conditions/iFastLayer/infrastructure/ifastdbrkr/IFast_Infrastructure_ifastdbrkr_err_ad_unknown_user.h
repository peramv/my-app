#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_ad_unknown_user : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_ad_unknown_user() { }
		~CIFast_Infrastructure_ifastdbrkr_err_ad_unknown_user() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_UNKNOWN_USER")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize start year.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize start year.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt dieses Startjahr nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce el año de inicio.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas l'année de début.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent beginjaar niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify start year and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify start year and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie das Startjahr und geben Sie es erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify start year and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez l'année de début et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer het beginjaar en voer dit opnieuw in")); }
	};
}



