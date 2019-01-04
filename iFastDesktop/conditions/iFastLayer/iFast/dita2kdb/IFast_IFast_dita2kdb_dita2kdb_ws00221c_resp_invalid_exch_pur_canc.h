#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_exch_pur_canc : public CConditionObject
	{
	public:
		CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_exch_pur_canc() { }
		~CIFast_IFast_dita2kdb_dita2kdb_ws00221c_resp_invalid_exch_pur_canc() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DITA2KDB_WS00221C_RESP_INVALID_EXCH_PUR_CANC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("dita2kdb")); }
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



