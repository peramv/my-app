#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_full_withdrawals_not_allowed_for_omnibus_accounts : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_full_withdrawals_not_allowed_for_omnibus_accounts() { }
		~CIFast_IFast_ifastcbo_err_full_withdrawals_not_allowed_for_omnibus_accounts() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FULL_WITHDRAWALS_NOT_ALLOWED_FOR_OMNIBUS_ACCOUNTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Full withdrawals not allowed for omnibus accounts.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Vollständige Abhebung für Gemeinschaftskonten nicht erlaubt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten retiros totales para las cuentas Omnibus")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les retraits totaux de sont pas autorisés pour les comptes omnibus.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volledige opname is niet toegestaan voor een verzamelaccount")); }

        // Actions
	};
}



