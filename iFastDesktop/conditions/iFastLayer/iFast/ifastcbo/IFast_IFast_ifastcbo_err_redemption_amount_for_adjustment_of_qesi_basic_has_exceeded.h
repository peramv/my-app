#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redemption_amount_for_adjustment_of_qesi_basic_has_exceeded : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redemption_amount_for_adjustment_of_qesi_basic_has_exceeded() { }
		~CIFast_IFast_ifastcbo_err_redemption_amount_for_adjustment_of_qesi_basic_has_exceeded() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDEMPTION_AMOUNT_FOR_ADJUSTMENT_OF_QESI_BASIC_HAS_EXCEEDED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption amount for Adjustment of QESI Basic has exceeded the total amount that was received.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de rachat pour l'ajustement de l'IQEE de base a excédé le montant total reçu.")); }

        // Actions
	};
}



