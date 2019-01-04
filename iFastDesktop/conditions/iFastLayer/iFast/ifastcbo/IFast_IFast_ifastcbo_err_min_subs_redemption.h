#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_min_subs_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_min_subs_redemption() { }
		~CIFast_IFast_ifastcbo_err_min_subs_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MIN_SUBS_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount is less than minimum subsequent redemption of %MINIMUM_AMT% for fund %FUND% and class %CLASS%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag liegt unter der minimalen Folgetilgung von %MINIMUM_AMT% für Fonds %FUND% und Klasse %CLASS%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Amount is less than minimum subsequent redemption of %MINIMUM_AMT% for fund %FUND% and class %CLASS%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant est inférieur au rachat subséquent minimal de %MINIMUM_AMT% pour le fonds %FUND% et la classe %CLASS%.")); }

        // Actions
	};
}



