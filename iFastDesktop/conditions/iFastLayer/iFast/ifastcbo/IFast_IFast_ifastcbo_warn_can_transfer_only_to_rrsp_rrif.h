#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_can_transfer_only_to_rrsp_rrif : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_can_transfer_only_to_rrsp_rrif() { }
		~CIFast_IFast_ifastcbo_warn_can_transfer_only_to_rrsp_rrif() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_CAN_TRANSFER_ONLY_TO_RRSP_RRIF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("From this account you can transfer only to RRSP or RRIF account.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les transferts depuis ce compte ne sont possibles que vers un compte REER ou FERR.")); }

        // Actions
	};
}



