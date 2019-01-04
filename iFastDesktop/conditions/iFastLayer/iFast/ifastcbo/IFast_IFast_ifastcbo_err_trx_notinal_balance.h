#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_trx_notinal_balance : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_trx_notinal_balance() { }
		~CIFast_IFast_ifastcbo_err_trx_notinal_balance() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TRX_NOTINAL_BALANCE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer of Notional balance is only valid between RESP accounts.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le transfert de solde théorique n'est valide qu'entre les comptes REEE.")); }

        // Actions
	};
}



