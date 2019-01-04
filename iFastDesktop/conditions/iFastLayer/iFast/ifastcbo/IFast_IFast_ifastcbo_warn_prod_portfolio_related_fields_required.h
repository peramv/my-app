#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_prod_portfolio_related_fields_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_prod_portfolio_related_fields_required() { }
		~CIFast_IFast_ifastcbo_warn_prod_portfolio_related_fields_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PROD_PORTFOLIO_RELATED_FIELDS_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Portfolio Name and Plan Name are mandatory fields.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les noms de portefeuille et de régime sont requis.")); }

        // Actions
	};
}



