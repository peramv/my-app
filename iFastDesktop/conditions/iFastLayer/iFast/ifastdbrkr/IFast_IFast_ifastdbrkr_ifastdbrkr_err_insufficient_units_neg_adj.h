#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_insufficient_units_neg_adj : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_insufficient_units_neg_adj() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_insufficient_units_neg_adj() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_INSUFFICIENT_UNITS_NEG_ADJ")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Insufficient Units for Neg ID Adjustment.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Insufficient Units for Neg ID Adjustment.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Unités insuffisantes pour l'ajustement du code négatif")); }

        // Actions
	};
}



