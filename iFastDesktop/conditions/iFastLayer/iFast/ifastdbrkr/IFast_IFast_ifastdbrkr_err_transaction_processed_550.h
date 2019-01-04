#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_transaction_processed_550 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_transaction_processed_550() { }
		~CIFast_IFast_ifastdbrkr_err_transaction_processed_550() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRANSACTION_PROCESSED_550")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transaction has not been  fully processed yet.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Transaction has not been  fully processed yet.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La transaction n'a pas encore été entièrement traitée.")); }

        // Actions
	};
}



