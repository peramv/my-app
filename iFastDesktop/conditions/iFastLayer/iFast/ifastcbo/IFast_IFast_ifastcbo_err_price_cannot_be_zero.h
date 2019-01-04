#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_price_cannot_be_zero : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_price_cannot_be_zero() { }
		~CIFast_IFast_ifastcbo_err_price_cannot_be_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PRICE_CANNOT_BE_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Price can not be zero")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Price can not be zero")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le prix ne peut être zéro.")); }

        // Actions
	};
}



