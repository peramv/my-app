#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_acct_transfer_in_flag_enable : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_acct_transfer_in_flag_enable() { }
		~CIFast_IFast_ifastcbo_err_acct_transfer_in_flag_enable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_TRANSFER_IN_FLAG_ENABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Transfer In Flag is enabled.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kennzeichen für Konto-Transfer ist aktiviert.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El flag de transferencia a la cuenta está habilitado")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le signal de transfert entrant du compte est désactivé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vlag voor accountoverdracht in is ingeschakeld")); }

        // Actions
	};
}



