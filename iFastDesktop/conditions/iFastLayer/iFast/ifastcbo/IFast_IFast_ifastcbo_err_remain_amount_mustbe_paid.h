#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_remain_amount_mustbe_paid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_remain_amount_mustbe_paid() { }
		~CIFast_IFast_ifastcbo_err_remain_amount_mustbe_paid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REMAIN_AMOUNT_MUSTBE_PAID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The remaining minimum amount %amount% must be paid first.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("The remaining minimum amount %amount% must be paid first.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("The remaining minimum amount %amount% must be paid first.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant minimal restant %amount% doit d'abord être payé.")); }

        // Actions
	};
}



