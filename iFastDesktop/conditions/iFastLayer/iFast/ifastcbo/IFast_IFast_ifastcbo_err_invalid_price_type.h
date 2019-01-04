#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_price_type : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_price_type() { }
		~CIFast_IFast_ifastcbo_err_invalid_price_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_PRICE_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Price type must be 'NAV' for the Redemption Aggregated Order")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Price type must be 'NAV' for the Redemption Aggregated Order")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de prix doit être Valeur de l'actif net pour l'ordre global de rachat.")); }

        // Actions
	};
}



