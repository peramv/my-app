#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_full_withdraw_for_omnibus_acct : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_full_withdraw_for_omnibus_acct() { }
		~CIFast_IFast_ifastcbo_err_full_withdraw_for_omnibus_acct() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FULL_WITHDRAW_FOR_OMNIBUS_ACCT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Full withdrawal is not allowed for ominibus account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Les retraits pour solde ne sont pas autorisés pour les comptes globaux")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eine volle Abbuchung ist nicht erlaubt bei einem Gemeinschaftskonto.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten retiros totales para la cuenta Omnibus")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le retrait total n'est pas autorisé pour un compte omnibus.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Volledige opname is niet toegestaan voor verzamelaccount")); }

        // Actions
	};
}



