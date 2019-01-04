#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tranfer_tansaction_resubmitted : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tranfer_tansaction_resubmitted() { }
		~CIFast_IFast_ifastcbo_err_tranfer_tansaction_resubmitted() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANFER_TANSACTION_RESUBMITTED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer Transaction will be resubmitted.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction de transfert sera soumise à nouveau.")); }

        // Actions
	};
}



