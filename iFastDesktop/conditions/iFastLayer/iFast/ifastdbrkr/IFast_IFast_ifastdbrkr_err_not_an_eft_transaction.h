#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_not_an_eft_transaction : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_not_an_eft_transaction() { }
		~CIFast_IFast_ifastdbrkr_err_not_an_eft_transaction() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NOT_AN_EFT_TRANSACTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Not an EFT transaction.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Not an EFT transaction.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine EFT-Transaktion")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No es una transacción EFT")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Ceci n'est pas une transaction TEF.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geen EFO-transactie")); }

        // Actions
	};
}



