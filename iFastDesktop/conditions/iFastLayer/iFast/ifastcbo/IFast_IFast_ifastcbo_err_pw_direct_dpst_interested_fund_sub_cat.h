#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pw_direct_dpst_interested_fund_sub_cat : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pw_direct_dpst_interested_fund_sub_cat() { }
		~CIFast_IFast_ifastcbo_err_pw_direct_dpst_interested_fund_sub_cat() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PW_DIRECT_DPST_INTERESTED_FUND_SUB_CAT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption with direct deposit payment type for interest fund required Investor Authorization with interest fund option.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un rachat avec un type de paiement par dépôt direct pour un fonds d'intérêt requiert l'autorisation de l'investisseur et l'option de fonds d'intérêt.")); }

        // Actions
	};
}



