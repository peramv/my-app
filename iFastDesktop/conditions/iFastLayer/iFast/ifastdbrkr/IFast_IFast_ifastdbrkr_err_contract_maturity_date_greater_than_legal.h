#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_contract_maturity_date_greater_than_legal : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_contract_maturity_date_greater_than_legal() { }
		~CIFast_IFast_ifastdbrkr_err_contract_maturity_date_greater_than_legal() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONTRACT_MATURITY_DATE_GREATER_THAN_LEGAL")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Contract Maturity Date cannot be greater than the legal maturity date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Vertrags-Fälligkeitsdatum darf nicht nach dem gesetzlichen Fälligkeitsdatum liegen")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de vencimiento del contrato no puede ser posterior a la fecha de vencimiento legal")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'échéance du contrat ne peut être postérieure à la date d'échéance légale.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De vervaldatum van de overeenkomst mag niet later zijn dan de wettelijke vervaldatum")); }

        // Actions
	};
}



