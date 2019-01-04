#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_acq_fee_calc_during_run : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_acq_fee_calc_during_run() { }
		~CIFast_IFast_ifastdbrkr_err_acq_fee_calc_during_run() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACQ_FEE_CALC_DURING_RUN")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Acq/Admin Fee Calculated during Night Run.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Berechnung der Acq/Admin–Provision während des Nachtdurchlaufs")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Calcular cargo por adquisición/comisión por administración durante la ejecución nocturna.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Calcul des frais d'acquisition/d'administration pendant l'exécution de nuit")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Berekenen van aankoop- en administratiekosten tijdens nachtelijke uitvoering")); }

        // Actions
	};
}



