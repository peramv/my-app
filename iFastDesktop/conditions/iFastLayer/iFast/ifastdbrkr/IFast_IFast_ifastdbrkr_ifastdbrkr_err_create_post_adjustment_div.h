#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_create_post_adjustment_div : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_create_post_adjustment_div() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_create_post_adjustment_div() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_CREATE_POST_ADJUSTMENT_DIV")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Please create 'Post Adjustment Dividend' for this transaction.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Please create 'Post Adjustment Dividend' for this transaction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Veuillez créer l'enregistrement du dividende de l'ajustement pour cette transaction.")); }

        // Actions
	};
}



