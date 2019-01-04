#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_deposit_type_23_not_support : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_deposit_type_23_not_support() { }
		~CIFast_IFast_ifastcbo_err_deposit_type_23_not_support() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DEPOSIT_TYPE_23_NOT_SUPPORT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Deposit type 23 for commission rebate is not currently supported.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Depot-Typ 23 für Provisions-Abzug wird momentan nicht unterstützt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El sistema no soporta actualmente el depósito tipo 23 para reembolso de la comisión.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le code de dépôt 23 pour la remise de commission n'est pas supporté actuellement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Depositotype 23 voor commissiekorting wordt op dit moment niet ondersteund")); }

        // Actions
	};
}



