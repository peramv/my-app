#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_transaction_number : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_transaction_number() { }
		~CIFast_IFast_ifastdbrkr_err_no_transaction_number() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_TRANSACTION_NUMBER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No such Transaction Number.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun numéro de transaction semblable")); }

        // Actions
	};
}



