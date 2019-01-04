#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_min_subs_purchase : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_min_subs_purchase() { }
		~CIFast_IFast_ifastcbo_err_min_subs_purchase() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MIN_SUBS_PURCHASE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount is less than minimum subsequent purchase of %MINIMUM_AMT% for fund %FUND% and class %CLASS%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag liegt unter dem minimalen Folge-Kauf von %MINIMUM_AMT% für Fonds %FUND% und Klasse %CLASS%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Amount is less than minimum subsequent purchase of %MINIMUM_AMT% for fund %FUND% and class %CLASS%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant est inférieur à l'achat subséquent minimal de %MINIMUM_AMT% pour le fonds %FUND% et la classe %CLASS%.")); }

        // Actions
	};
}



