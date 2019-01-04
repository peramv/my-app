#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_start_date_before_last_process_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_start_date_before_last_process_date() { }
		~CIFast_IFast_ifastcbo_err_start_date_before_last_process_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_START_DATE_BEFORE_LAST_PROCESS_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective Date must be after the Last Process Date of PAC/Savings Plan.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Effektivdatum muss größer als das Letztes-Verfahren-Datum des PAC/Spar-Plans sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de entrada en vigencia debe ser posterior a la fecha de último proceso del plan PAC/ahorros.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur doit être postérieure à la dernière date de traitement du PAC/régime d'épargne.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ingangsdatum moet later zijn dan de laatste verwerkingsdatum van het VGC/Savings Plan")); }

        // Actions
	};
}



