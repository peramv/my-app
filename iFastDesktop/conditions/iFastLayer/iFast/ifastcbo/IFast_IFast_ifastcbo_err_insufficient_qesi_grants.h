#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_insufficient_qesi_grants : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_insufficient_qesi_grants() { }
		~CIFast_IFast_ifastcbo_err_insufficient_qesi_grants() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INSUFFICIENT_QESI_GRANTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Insufficient QESI Grants.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Subventions IQEE insuffisantes")); }

        // Actions
	};
}



