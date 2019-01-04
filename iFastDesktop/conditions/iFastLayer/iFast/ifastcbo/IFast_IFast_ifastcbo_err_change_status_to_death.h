#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_change_status_to_death : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_change_status_to_death() { }
		~CIFast_IFast_ifastcbo_err_change_status_to_death() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CHANGE_STATUS_TO_DEATH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Account balance must be 0 to change status to death.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kontostand muss 0 sein, um den Status auf Tod ändern zu können.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El saldo de la cuenta debe ser 0 para cambiar el estado a fallecimiento.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le solde du compte doit être à zéro pour changer le statut pour Décès.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Accountsaldo moet 0 zijn om de status in overleden te kunnen wijzigen")); }

        // Actions
	};
}



