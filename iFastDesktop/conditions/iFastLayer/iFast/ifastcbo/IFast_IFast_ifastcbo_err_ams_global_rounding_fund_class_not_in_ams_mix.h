#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_ams_global_rounding_fund_class_not_in_ams_mix : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_ams_global_rounding_fund_class_not_in_ams_mix() { }
		~CIFast_IFast_ifastcbo_err_ams_global_rounding_fund_class_not_in_ams_mix() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMS_GLOBAL_ROUNDING_FUND_CLASS_NOT_IN_AMS_MIX")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Rounding Fund/Class must be part of the AMS mix.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Rounding Fund/Class must be part of the AMS mix.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds/la classe d'arrondissement doit faire partie de la composition de service de gestion de portefeuille.")); }

        // Actions
	};
}



