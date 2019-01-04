#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_anti_dilution_levy_default_rate_does_not_exist : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_anti_dilution_levy_default_rate_does_not_exist() { }
		~CIFast_IFast_ifastcbo_err_anti_dilution_levy_default_rate_does_not_exist() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ANTI_DILUTION_LEVY_DEFAULT_RATE_DOES_NOT_EXIST")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Percentage can be 0 only when Default Fee rate exists for Fund/Class.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Fee Percentage can be 0 only when Default Fee rate exists for Fund/Class.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Fee Percentage can be 0 only when Default Fee rate exists for Fund/Class.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le pourcentage de frais ne peut être 0 que lorsqu'un taux de commission par défaut existe pour le fonds/la classe.")); }

        // Actions
	};
}



