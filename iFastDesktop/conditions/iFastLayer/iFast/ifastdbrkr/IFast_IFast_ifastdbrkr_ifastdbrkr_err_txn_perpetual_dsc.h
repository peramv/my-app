#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_txn_perpetual_dsc : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_txn_perpetual_dsc() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_txn_perpetual_dsc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_TXN_PERPETUAL_DSC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction has Perpetual DSC Fees but no Family.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaction has Perpetual DSC Fees but no Family.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction a des FAR perpétuels mais aucune famille.")); }

        // Actions
	};
}



