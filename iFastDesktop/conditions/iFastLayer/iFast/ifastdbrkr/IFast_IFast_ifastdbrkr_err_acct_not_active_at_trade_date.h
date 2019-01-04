#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_acct_not_active_at_trade_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_acct_not_active_at_trade_date() { }
		~CIFast_IFast_ifastdbrkr_err_acct_not_active_at_trade_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_NOT_ACTIVE_AT_TRADE_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Not Active at Trade Date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto am Handelsdatum  nicht aktiv.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La cuenta no está activa a la fecha de transacción.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Compte inactif en date de transaction")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Account is niet actief op handelsdatum")); }

        // Actions
	};
}



