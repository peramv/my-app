#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_effective_date_contract_earlier_than_effective_date_mfaccount : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_effective_date_contract_earlier_than_effective_date_mfaccount() { }
		~CIFast_IFast_ifastcbo_err_effective_date_contract_earlier_than_effective_date_mfaccount() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_EFFECTIVE_DATE_CONTRACT_EARLIER_THAN_EFFECTIVE_DATE_MFACCOUNT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective date of Contract must be later than Effective date of Account.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Effective date of Contract must must be later than Effective date of Account.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Effektivdatum des Vertrags muss nach dem Effektivdatum des MF-Kontos liegen. Bitte geben Sie es neu ein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de entrada en vigencia del contrato debe ser posterior a la fecha de entrada en vigencia de la cuenta MF. Por favor vuelva a introducir los datos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur du contrat doit être postérieure à la date d'entrée en vigueur du compte.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ingangsdatum van overeenkomst moet later zijn dan de ingangsdatum van het MF-account.  Vul opnieuw in")); }

        // Actions
	};
}



