#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_jumbo_price_not_applicable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_jumbo_price_not_applicable() { }
		~CIFast_IFast_ifastcbo_err_jumbo_price_not_applicable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_JUMBO_PRICE_NOT_APPLICABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 1; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Jumbo price is not applicable.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Jumbo price is not applicable.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le prix négociable n'est pas applicable.")); }

        // Actions
	};
}



