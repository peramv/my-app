#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_fee_accrual_information_available : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_fee_accrual_information_available() { }
		~CIFast_IFast_ifastdbrkr_err_no_fee_accrual_information_available() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_FEE_ACCRUAL_INFORMATION_AVAILABLE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No fee accrual information available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Informationen über aufgelaufene Provisionen verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay información disponible sobre las comisiones acumuladas.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune information sur l'augmentation des frais n'est disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen gegevens over kostengroei beschikbaar")); }

        // Actions
	};
}



