#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_eom_month_end : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_eom_month_end() { }
		~CIFast_IFast_ifastcbo_err_rif_eom_month_end() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_EOM_MONTH_END")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Effective Date is 29th, 30th or 31st. If End of Month, should be set to 'Yes\", please change manually.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Scheduled payment already processed. End Of Month takes effect on following month.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Planmäßige Zahlung bereits verarbeitet. Monatsende wirkt sich auf Folgemonat aus.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Pago programado ya procesado. Fin de mes tiene efecto el mes siguiente.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La date d'entrée en vigueur est le 29, le 30 ou le 31. Si le champ Fin de mois devrait être réglé à Oui, veuillez le changer manuellement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Geplande betaling is al verwerkt. Einde van maand wordt volgende maand van kracht")); }

        // Actions
	};
}



