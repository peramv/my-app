#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_rdsp_cannot_cancel_reconciled_external_transfer_in : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_rdsp_cannot_cancel_reconciled_external_transfer_in() { }
		~CIFast_IFast_ifastdbrkr_err_rdsp_cannot_cancel_reconciled_external_transfer_in() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DBRKR_RDSP_CANNOT_CANCEL_RECONCILED_EXTERNAL_TRANSFER_IN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Reconciled External RDSP Transfer-In transaction cannot be cancelled.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Reconciled External RDSP Transfer-In transaction cannot be cancelled.")); }

        // Actions
	};
}



