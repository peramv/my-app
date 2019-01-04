#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_rif_samemonthlastprocdateascurbusdate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_rif_samemonthlastprocdateascurbusdate() { }
		~CIFast_IFast_ifastcbo_err_warn_rif_samemonthlastprocdateascurbusdate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_RIF_SameMonthLastProcDateAsCurBusDate")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Scheduled payment already processed. End of month takes effect on following month.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Planmäßige Zahlung bereits verarbeitet. Monatsende wirkt sich auf Folgemonat aus.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Pago programado ya procesado. Fin de mes tiene efecto el mes siguiente.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le paiement à date fixe a déjà été traité. La fin de mois entre en vigueur le mois prochain.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geplande betaling is al verwerkt. Einde van maand wordt volgende maand van kracht")); }

        // Actions
	};
}



