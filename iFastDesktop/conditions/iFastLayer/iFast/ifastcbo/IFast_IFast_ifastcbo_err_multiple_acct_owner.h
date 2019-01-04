#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_multiple_acct_owner : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_multiple_acct_owner() { }
		~CIFast_IFast_ifastcbo_err_multiple_acct_owner() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MULTIPLE_ACCT_OWNER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Multiple Accountholder entities not allowed for this type of account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Entites Titulaires de comptes (01) multiples non autorisées pour ce type de compte.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mehrfach-Kontoinhaber (01)-Objekte sind für diesen Kontotyp nicht zugelassen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten entidades de titular de cuenta múltiples (01) en este tipo de cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les entités à multiples titulaires de compte n'ont pas accès à ce type de compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Meerdere eenheden voor accounthouder (01) zijn niet toegestaan in dit type account")); }

        // Actions
	};
}



