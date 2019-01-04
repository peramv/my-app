#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_settle_type_block_not_allow_not_through_fundserv : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_settle_type_block_not_allow_not_through_fundserv() { }
		~CIFast_IFast_ifastcbo_warn_settle_type_block_not_allow_not_through_fundserv() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SETTLE_TYPE_BLOCK_NOT_ALLOW_NOT_THROUGH_FUNDSERV")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Settlement Type Block is not allowed if trade is not settled through FundSERV")); }

        // Actions
	};
}



