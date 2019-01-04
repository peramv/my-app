#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_max_amount_less_than_unused_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_max_amount_less_than_unused_amount() { }
		~CIFast_IFast_ifastcbo_err_rif_max_amount_less_than_unused_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_MAX_AMOUNT_LESS_THAN_UNUSED_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Max Annual Amount should be greater than Unused Amount.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant annuel maximal devrait être supérieur au montant non utilisé.")); }

        // Actions
	};
}



