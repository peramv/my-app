#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_settle_type_individual_not_allow_through_fundserv : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_settle_type_individual_not_allow_through_fundserv() { }
		~CIFast_IFast_ifastcbo_err_settle_type_individual_not_allow_through_fundserv() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLE_TYPE_INDIVIDUAL_NOT_ALLOW_THROUGH_FUNDSERV")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settlement Type Individual is not allowed if trade is settled through FundSERV")); }

        // Actions
	};
}



