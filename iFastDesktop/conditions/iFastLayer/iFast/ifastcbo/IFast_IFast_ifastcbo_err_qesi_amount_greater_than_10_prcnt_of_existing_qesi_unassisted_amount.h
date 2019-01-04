#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_qesi_amount_greater_than_10_prcnt_of_existing_qesi_unassisted_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_qesi_amount_greater_than_10_prcnt_of_existing_qesi_unassisted_amount() { }
		~CIFast_IFast_ifastcbo_err_qesi_amount_greater_than_10_prcnt_of_existing_qesi_unassisted_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_QESI_AMOUNT_GREATER_THAN_10_PRCNT_OF_EXISTING_QESI_UNASSISTED_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("QESI Amount cannot be greater than 10% of existing QESI Unassisted amount for the beneficiary and tax year.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant IQEE ne peut être supérieur de plus de 10 % au montant IQEE non subventionné existant pour le bénéficiaire et l'année d'imposition.")); }

        // Actions
	};
}



