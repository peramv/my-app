#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_ad_unknown_access_profile : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_ad_unknown_access_profile() { }
		~CIFast_Infrastructure_ifastdbrkr_err_ad_unknown_access_profile() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AD_UNKNOWN_ACCESS_PROFILE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The system does not recognize accumulator years.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("The system does not recognize accumulator years.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das System erkennt diese Aufzinsungsjahre nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no reconoce los años de acumulación.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le système ne reconnaît pas les années accumulées.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het systeem herkent accumulatiejaren niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify accumulator years and re-enter.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify accumulator years and re-enter.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Überprüfen Sie die Aufzinsungsjahre und geben Sie sie erneut ein.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Verify accumulator years and re-enter.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez les années accumulées et réessayez.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer de accumulatiejaren en voer deze opnieuw in")); }
	};
}



