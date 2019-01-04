#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_no_check_on_taxrate_for_non_dollar_amttype : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_no_check_on_taxrate_for_non_dollar_amttype() { }
		~CIFast_IFast_ifastcbo_warn_no_check_on_taxrate_for_non_dollar_amttype() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_NO_CHECK_ON_TAXRATE_FOR_NON_DOLLAR_AMTTYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Tax Rates can not be checked when the Trade Amount is not Dollars.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Tax Rates can not be checked when the Trade Amount is not Dollars.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No Checking on tax rates for trade amount type is not amount.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les taux d'imposition ne peuvent être vérifiés lorsque le montant de la transaction n'est pas en dollars.")); }

        // Actions
	};
}



