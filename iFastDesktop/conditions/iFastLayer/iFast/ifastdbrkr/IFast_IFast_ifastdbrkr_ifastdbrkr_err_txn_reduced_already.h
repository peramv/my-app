#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_ifastdbrkr_err_txn_reduced_already : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_ifastdbrkr_err_txn_reduced_already() { }
		~CIFast_IFast_ifastdbrkr_ifastdbrkr_err_txn_reduced_already() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("IFASTDBRKR_ERR_TXN_REDUCED_ALREADY")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction has been reduced already.  Cannot cancel.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaction has been reduced already.  Cannot cancel.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction a déjà été réduite. Annulation impossible.")); }

        // Actions
	};
}



