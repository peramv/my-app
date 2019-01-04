#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_total_tax_amount_greater_than_amount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_total_tax_amount_greater_than_amount() { }
		~CIFast_IFast_ifastcbo_err_total_tax_amount_greater_than_amount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TOTAL_TAX_AMOUNT_GREATER_THAN_AMOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Total Tax Amount cannot be greater than Amount.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Total Tax Amount cannot be greater than Amount.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant d'imposition total ne peut être supérieur au montant.")); }

        // Actions
	};
}



