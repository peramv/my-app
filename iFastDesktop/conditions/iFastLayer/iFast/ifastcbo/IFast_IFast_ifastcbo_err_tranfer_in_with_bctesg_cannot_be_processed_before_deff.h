#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tranfer_in_with_bctesg_cannot_be_processed_before_deff : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tranfer_in_with_bctesg_cannot_be_processed_before_deff() { }
		~CIFast_IFast_ifastcbo_err_tranfer_in_with_bctesg_cannot_be_processed_before_deff() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSFER_IN_WITH_BCTESG_CANNOT_BE_PROCESSED_BEFORE_DEFF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer in trades with BCTESG amount cannot be processed before August 15, 2015.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert des montants de SEEEFCB ne peut être traité avant le 1er août 2015.")); }


        // Actions
	};
}



