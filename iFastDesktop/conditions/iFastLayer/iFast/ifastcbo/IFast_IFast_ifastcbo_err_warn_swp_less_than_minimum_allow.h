#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_swp_less_than_minimum_allow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_swp_less_than_minimum_allow() { }
		~CIFast_IFast_ifastcbo_err_warn_swp_less_than_minimum_allow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_SWP_LESS_THAN_MINIMUM_ALLOW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Minimum allowable SWP amount for fund %FUNDNAME% is %AMOUNT%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Minimum allowable SWP amount for fund %FUNDNAME% is %AMOUNT%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Minimum allowable SWP amount for fund %FUNDNAME% is %AMOUNT%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de PRP minimal autorisé pour le fonds %FUNDNAME% est de %AMOUNT%.")); }

        // Actions
	};
}



