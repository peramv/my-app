#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_amount_is_over_threshold : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_amount_is_over_threshold() { }
		~CIFast_IFast_ifastcbo_err_amount_is_over_threshold() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_AMOUNT_IS_OVER_THRESHOLD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount is over the threshold trade amount limit of %threshold%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Amount is over the threshold trade amount limit of %threshold%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant est supérieur à la limite du montant de transaction seuil de %threshold%.")); }

        // Actions
	};
}



