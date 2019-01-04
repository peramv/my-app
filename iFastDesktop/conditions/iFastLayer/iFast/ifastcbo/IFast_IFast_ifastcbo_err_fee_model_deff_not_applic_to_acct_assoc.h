#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_fee_model_deff_not_applic_to_acct_assoc : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_fee_model_deff_not_applic_to_acct_assoc() { }
		~CIFast_IFast_ifastcbo_err_fee_model_deff_not_applic_to_acct_assoc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FEE_MODEL_DEFF_NOT_APPLIC_TO_ACCT_ASSOC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Fee Model Effective Date change will not be applied to the tree.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La modification de la date d'effet du modèle de frais ne sera pas appliquée à l'arbre.")); }

        // Actions
	};
}



