#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_redempt_amt_exceeded_qesi_amt_received : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_redempt_amt_exceeded_qesi_amt_received() { }
		~CIFast_IFast_ifastcbo_err_redempt_amt_exceeded_qesi_amt_received() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_REDEMPT_AMT_EXCEEDED_QESI_AMT_RECEIVED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Redemption Amount has exceeded the total QESI Amount that was received.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant de rachat a excédé le montant total IQEE reçu.")); }

        // Actions
	};
}



