#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_account_designation_must_same_and_is_not_1 : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_account_designation_must_same_and_is_not_1() { }
		~CIFast_IFast_ifastcbo_err_account_designation_must_same_and_is_not_1() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCOUNT_DESIGNATION_MUST_SAME_AND_IS_NOT_1")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account Designation of the from account and the to account must be the same and cannot be client.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AcctDesignation des Von-Kontos und des Zu-Kontos müssen übereinstimmen und können nicht Kunde sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La designación de cuenta de la cuenta de origen y de la cuenta de destino deben ser iguales y no puede ser cliente")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La désignation des comptes source et cible doit être la même et ne peut être Client.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountbestemming van het van-account en het naar-account moeten hetzelfde zijn en kunnen geen klant zijn")); }

        // Actions
	};
}



