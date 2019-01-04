#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_eft_to_chq_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_eft_to_chq_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_eft_to_chq_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EFT_TO_CHQ_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Changing payment type from EFT to Cheque not allowed for The Trade.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le changement de type de paiement de TEF à Chèque n'est pas autorisé pour la transaction.")); }

        // Actions
	};
}



