#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_tis_cost_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_tis_cost_type() { }
		~CIFast_IFast_ifastcbo_err_invalid_tis_cost_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_TIS_COST_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only MANUAL TIS/Cost Type allowed")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seul le type de revenu imposable par action/de prix MANUEL est autorisé.")); }

        // Actions
	};
}



