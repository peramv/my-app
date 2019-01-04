#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_rdr_advice_updated : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_rdr_advice_updated() { }
		~CIFast_IFast_ifastcbo_warn_rdr_advice_updated() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_RDR_ADVICE_UPDATED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Default value of RDR Advice flag is changed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La valeur par défaut de l’alerte/l’icône RDR Advice est changée.")); }

        // Actions
	};
}



