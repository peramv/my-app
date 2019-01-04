#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rrif_lif_rate_puid : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rrif_lif_rate_puid() { }
		~CIFast_IFast_ifastcbo_err_rrif_lif_rate_puid() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RRIF_LIF_RATE_PUID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("%RATE_PUID% is not Percent, system does not have calculation Values.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("%RATE_PUID% ist nicht Prozent, System hat keine Berechnungswerte.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("%RATE_PUID% no es un porcentaje, el sistema no tiene valores de cálculo")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("%RATE_PUID% n'est pas un pourcentage, le système n'a pas les valeurs de calcul.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("%RATE_PUID% is geen percentage, het systeem heeft geen berekeningswaarden")); }

        // Actions
	};
}



