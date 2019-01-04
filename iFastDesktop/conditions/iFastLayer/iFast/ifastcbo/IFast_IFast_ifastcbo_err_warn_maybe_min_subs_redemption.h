#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_maybe_min_subs_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_maybe_min_subs_redemption() { }
		~CIFast_IFast_ifastcbo_err_warn_maybe_min_subs_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_MAYBE_MIN_SUBS_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount may be less than minimum subsequent redemption: %MINIMUM_AMT% for fund %FUND% and class %CLASS%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag kann unter der minimalen Folgetilgung liegen: %MINIMUM_AMT% für Fonds %FUND% und Klasse %CLASS%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto puede ser inferior al rescate posterior mínimo %MINIMUM_AMT% para el fondo %FUND% y la clase %CLASS%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant pourrait être inférieur au rachat subséquent minimal : %MINIMUM_AMT% pour le fonds %FUND% et la classe %CLASS%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag kan lager zijn dan minimale volgende aflossing: %MINIMUM_AMT% voor fonds FUND% en categorie %CLASS%")); }

        // Actions
	};
}



