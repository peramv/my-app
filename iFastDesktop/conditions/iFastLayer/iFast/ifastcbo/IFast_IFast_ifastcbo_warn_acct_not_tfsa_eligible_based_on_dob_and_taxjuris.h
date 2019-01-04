#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_acct_not_tfsa_eligible_based_on_dob_and_taxjuris : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_acct_not_tfsa_eligible_based_on_dob_and_taxjuris() { }
		~CIFast_IFast_ifastcbo_warn_acct_not_tfsa_eligible_based_on_dob_and_taxjuris() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_ACCT_NOT_TFSA_ELIGIBLE_BASED_ON_DOB_AND_TAXJURIS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account is not TFSA eligible, based on date of birth and tax jurisdiction.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le compte n'est pas admissible au CELI pour l'achat, l'âge minimum n'est pas attaint.")); }

        // Actions
	};
}