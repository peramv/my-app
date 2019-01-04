#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_gi_selected_total_not_100 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_gi_selected_total_not_100() { }
		~CIFast_IFast_ifastcbo_err_gi_selected_total_not_100() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_GI_SELECTED_TOTAL_NOT_100")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Selected percentages must sum up to 100%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les pourcentages sélectionnés doivent totaliser 100 %.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please correct")); }
	};
}



