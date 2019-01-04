#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_type_must_same : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_type_must_same() { }
		~CIFast_IFast_ifastcbo_err_account_type_must_same() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_TYPE_MUST_SAME")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Type of the from account and the to account must be the same.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontoart des Von-Kontos und des Zu-Kontos müssen übereinstimmen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El tipo de cuenta de la cuenta de origen y de la cuenta de destino deben ser iguales.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le type de comptes source et cible doit être le même.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accounttype van het van-account en het naar-account moeten hetzelfde zijn")); }

        // Actions
	};
}



