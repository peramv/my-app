#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_amtcode_for_investment_allocation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_amtcode_for_investment_allocation() { }
		~CIFast_IFast_ifastcbo_err_invalid_amtcode_for_investment_allocation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_AMTCODE_FOR_INVESTMENT_ALLOCATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid amount code for investment allocation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültiger Betragscode für Investment-Zuweisung")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Código de monto no válido para asignación de inversiones")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Code de montant invalide pour la répartition d'investissement")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldige bedragcode voor beleggingsallocatie")); }

        // Actions
	};
}



