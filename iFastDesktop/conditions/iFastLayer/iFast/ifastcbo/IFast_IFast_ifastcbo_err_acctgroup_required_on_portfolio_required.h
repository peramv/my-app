#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acctgroup_required_on_portfolio_required : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acctgroup_required_on_portfolio_required() { }
		~CIFast_IFast_ifastcbo_err_acctgroup_required_on_portfolio_required() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCTGROUP_REQUIRED_ON_PORTFOLIO_REQUIRED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Shareholder Group \\ Account Group is mandatory on Portfolio Required Environment")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le groupe du détenteur/du compte est obligatoire dans un environnement où le portefeuille est requis.")); }

        // Actions
	};
}



