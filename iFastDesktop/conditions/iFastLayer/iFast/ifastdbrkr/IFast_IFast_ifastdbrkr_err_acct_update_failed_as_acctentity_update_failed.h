#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_acct_update_failed_as_acctentity_update_failed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_acct_update_failed_as_acctentity_update_failed() { }
		~CIFast_IFast_ifastdbrkr_err_acct_update_failed_as_acctentity_update_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCT_UPDATE_FAILED_AS_ACCTENTITY_UPDATE_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account update failed due to problem with Account Entity update.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Account update failed due to problem with Account Entity update.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Konto-Aktualisierung fehlgeschlagen wegen Problem mit Konto-Objekt-Aktualisierung.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Falló la actualización de la cuenta debido a un problema con la actualización de la entidad de cuenta")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La mise à jour du compte a échoué en raison d'un problème avec la mise à jour de l'entité du compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Account kon niet worden bijgewerkt, er zijn problemen met het bijwerken van accounteenheden")); }

        // Actions
	};
}



