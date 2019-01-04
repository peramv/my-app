#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_num_needed_for_close_account : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_num_needed_for_close_account() { }
		~CIFast_IFast_ifastcbo_err_account_num_needed_for_close_account() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_NUM_NEEDED_FOR_CLOSE_ACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account number must be specified when closing an account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontonummer muss angegeben werden, wenn ein Konto geschlossen wird")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe especificarse el número de cuenta al cerrar una cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro de compte doit être spécifié lors de la fermeture d'un compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountnummer moet worden opgegeven als het account wordt gesloten")); }

        // Actions
	};
}



