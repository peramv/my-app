#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_transaction_status : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_transaction_status() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_transaction_status() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_TRANSACTION_STATUS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid transaction status")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Statut de transaction invalide")); }

        // Actions
	};
}



