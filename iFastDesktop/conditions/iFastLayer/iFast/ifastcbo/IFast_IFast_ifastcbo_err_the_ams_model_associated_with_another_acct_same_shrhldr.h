#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_the_ams_model_associated_with_another_acct_same_shrhldr : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_the_ams_model_associated_with_another_acct_same_shrhldr() { }
		~CIFast_IFast_ifastcbo_err_the_ams_model_associated_with_another_acct_same_shrhldr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_THE_AMS_MODEL_ASSOCIATED_WITH_ANOTHER_ACCT_SAME_SHRHLDR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The AMS Model is associated with another account under same shareholder.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le Modèle AMS est associé à un autre compte pour le même actionnaire.")); }

        // Actions
	};
}



