#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deposits_not_allowed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deposits_not_allowed() { }
		~CIFast_IFast_ifastcbo_err_deposits_not_allowed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPOSITS_NOT_ALLOWED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Deposits not allowed in closing period.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Deposits not allowed in closing period.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Einzahlungen in der Abschlussphase nicht zugelassen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se permiten depósitos durante el período de cierre.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les dépôts ne sont pas autorisés pendant la période de fermeture.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Deposito's zijn niet toegestaan in sluitingsperiode")); }

        // Actions
	};
}



