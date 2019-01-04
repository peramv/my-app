#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_purchase_not_allowed_for_fund : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_purchase_not_allowed_for_fund() { }
		~CIFast_IFast_ifastcbo_err_purchase_not_allowed_for_fund() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PURCHASE_NOT_ALLOWED_FOR_FUND")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Purchase not allowed for Fund")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Achat non autorisé pour le fonds")); }

        // Actions
	};
}



