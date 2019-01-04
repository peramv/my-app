#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tax_amount_negative : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tax_amount_negative() { }
		~CIFast_IFast_ifastcbo_err_tax_amount_negative() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TAX_AMOUNT_NEGATIVE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Amount cannot be negative.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tax Amount cannot be negative.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant d'imposition ne peut être négatif.")); }

        // Actions
	};
}



