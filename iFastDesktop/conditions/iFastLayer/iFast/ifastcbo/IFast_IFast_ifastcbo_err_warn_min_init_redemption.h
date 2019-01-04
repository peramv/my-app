﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_warn_min_init_redemption : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_warn_min_init_redemption() { }
		~CIFast_IFast_ifastcbo_err_warn_min_init_redemption() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_WARN_MIN_INIT_REDEMPTION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Amount for fund %FUND% and class %CLASS% is less than minimum initial redemption: %MINIMUM_AMT%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Betrag für Fonds %FUND% und Klasse %CLASS% liegt unter der minimalen Anfangstilgung: %MINIMUM_AMT%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto para el fondo %FUND% y la clase %CLASS% es inferior al rescate inicial mínimo: %MINIMUM_AMT%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant pour le fonds %FUND% et la classe %CLASS% est inférieur au rachat initial minimal : %MINIMUM_AMT%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bedrag voor fonds %FUND% en categorie %CLASS% is minder dan de minimale eerste aflossing: %MINIMUM_AMT%")); }

        // Actions
	};
}



