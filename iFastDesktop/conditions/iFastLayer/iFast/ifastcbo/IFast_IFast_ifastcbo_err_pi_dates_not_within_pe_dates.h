#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_pi_dates_not_within_pe_dates : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_pi_dates_not_within_pe_dates() { }
		~CIFast_IFast_ifastcbo_err_pi_dates_not_within_pe_dates() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PI_DATES_NOT_WITHIN_PE_DATES")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Either pay to entity does not exist, or effective date and/or stop date not within pay to entity date range.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le Paiement à l'entité n'existe pas, ou la date d'entrée en vigueur ou la date d'arrêt ne sont pas dans la plage de dates de Paiement à l'entité.")); }

        // Actions
	};
}



