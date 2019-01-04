#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redcode_and_taxjuris_do_not_match_for_beneficiary : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redcode_and_taxjuris_do_not_match_for_beneficiary() { }
		~CIFast_IFast_ifastcbo_err_redcode_and_taxjuris_do_not_match_for_beneficiary() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDCODE_AND_TAXJURIS_DO_NOT_MATCH_FOR_BENEFICIARY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption code and Tax Jurisdiction do not match for beneficiary %EntityID%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Redemption code and Tax Jurisdiction do not match for beneficiary %EntityID%.")); }

        // Actions
	};
}



