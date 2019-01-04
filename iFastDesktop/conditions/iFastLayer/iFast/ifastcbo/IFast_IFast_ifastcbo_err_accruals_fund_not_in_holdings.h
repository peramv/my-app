#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_accruals_fund_not_in_holdings : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_accruals_fund_not_in_holdings() { }
		~CIFast_IFast_ifastcbo_err_accruals_fund_not_in_holdings() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACCRUALS_FUND_NOT_IN_HOLDINGS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Selected fund is not in Account Holdings.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ausgewählter Fonds ist nicht in den Kontobeteiligungen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El fondo seleccionado no está entre las inversiones de la cuenta.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le fonds sélectionné n'est pas dans le portefeuille du compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geselecteerde fonds bevindt zich niet in accountvermogens")); }

        // Actions
	};
}



