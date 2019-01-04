#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastbp_bp_err_multi_aggregated_order : public CConditionObject
	{
	public:
		CIFast_IFast_ifastbp_bp_err_multi_aggregated_order() { }
		~CIFast_IFast_ifastbp_bp_err_multi_aggregated_order() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("BP_ERR_MULTI_AGGREGATED_ORDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastbp")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple aggregated order found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Multiple aggregated order found.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Plusieurs ordres globaux ont été trouvés.")); }

        // Actions
	};
}



