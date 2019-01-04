#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_maybe_min_init_purchase : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_maybe_min_init_purchase() { }
		~CIFast_IFast_ifastcbo_err_warn_maybe_min_init_purchase() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_MAYBE_MIN_INIT_PURCHASE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Initial purchase amount for fund %FUND% and class %CLASS% may be less than minimum: %MINIMUM_AMT%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Anfänglicher Kaufbetrag für Fonds %FUND% und Klasse %CLASS% kann unter dem Minimum liegen: %MINIMUM_AMT%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto de compra inicial para el fondo %FUND% y la clase %CLASS% puede ser inferior al mínimo: %MINIMUM_AMT%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant d'achat initial pour le fonds %FUND% et la classe %CLASS% pourrait être inférieur au minimum : %MINIMUM_AMT%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Eerste aankoopbedrag voor fonds %FUND% en categorie %CLASS% mag minder zijn dan het minimum: %MINIMUM_AMT%")); }

        // Actions
	};
}



