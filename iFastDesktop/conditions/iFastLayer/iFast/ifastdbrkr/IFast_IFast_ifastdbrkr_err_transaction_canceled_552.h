#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_transaction_canceled_552 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_transaction_canceled_552() { }
		~CIFast_IFast_ifastdbrkr_err_transaction_canceled_552() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSACTION_CANCELED_552")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction has been cancelled.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaction has been cancelled.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction a été annulée.")); }

        // Actions
	};
}



