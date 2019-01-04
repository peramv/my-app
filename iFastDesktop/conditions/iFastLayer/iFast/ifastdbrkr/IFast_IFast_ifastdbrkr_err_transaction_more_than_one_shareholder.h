#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_transaction_more_than_one_shareholder : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_transaction_more_than_one_shareholder() { }
		~CIFast_IFast_ifastdbrkr_err_transaction_more_than_one_shareholder() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSACTION_MORE_THAN_ONE_SHAREHOLDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction includes more than one shareholder, cannot cancel.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaction includes more than one shareholder, cannot cancel.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction implique plus d'un actionnaire, annulation impossible.")); }

        // Actions
	};
}



