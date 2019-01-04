﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_systematic_process_date : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_systematic_process_date() { }
		~CIFast_IFast_ifastdbrkr_err_systematic_process_date() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SYSTEMATIC_PROCESS_DATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective date results in Next Process Date prior to last run date.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Bei diesem Effektivdatum liegt das Nächstes-Verfahren-Datum vor dem Letzter-Durchlauf-Datum!")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La fecha de entrada en vigencia da como resultado una fecha de siguiente proceso anterior a la última ejecución")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur doit être postérieure à la date du prochain traitement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ingangsdatum resulteert in volgende verwerkingsdatum die eerder ligt dan de laatste uitvoeringsdatum!")); }

        // Actions
	};
}



