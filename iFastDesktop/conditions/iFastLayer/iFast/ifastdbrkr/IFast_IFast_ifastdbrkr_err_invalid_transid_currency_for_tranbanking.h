#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_invalid_transid_currency_for_tranbanking : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_invalid_transid_currency_for_tranbanking() { }
		~CIFast_IFast_ifastdbrkr_err_invalid_transid_currency_for_tranbanking() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_TRANSID_CURRENCY_FOR_TRANBANKING")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Currency value is required for Last trade banking information; Transaction ID must be blank.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Währungswert ist erforderlich für Letzter-Handel-Bankinginformation; Transaktions-ID muss leer sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Se requiere el valor de la divisa para la información bancaria de la última operación; la identificación de transacción debe estar en blanco")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur de monnaie est requise pour l'information bancaire sur la dernière transaction; le champ du code de transaction doit être vide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Valutawaarde is vereist voor bankgegevens laatste handel; transactie-ID moet leeg zijn")); }

        // Actions
	};
}



