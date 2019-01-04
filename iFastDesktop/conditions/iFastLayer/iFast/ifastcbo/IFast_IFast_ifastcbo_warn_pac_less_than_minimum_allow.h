#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_warn_pac_less_than_minimum_allow : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_warn_pac_less_than_minimum_allow() { }
		~CIFast_IFast_ifastcbo_warn_pac_less_than_minimum_allow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PAC_LESS_THAN_MINIMUM_ALLOW")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Minimum allowable PAC amount for fund %FUNDNAME% is %AMOUNT%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Minimum allowable PAC amount for fund %FUNDNAME% is %AMOUNT%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Minimal erlaubte PAC-Anzahl für Fonds %FUNDNAME% beträgt  %AMOUNT%.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El monto de PAC mínimo permitido para el fondo %FUNDNAME% es %AMOUNT%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le montant minimal de PAC autorisé pour le fonds %FUNDNAME% est de %AMOUNT%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Toegestane minimale VGC-bedrag voor fonds %FUNDNAME% is %AMOUNT%")); }

        // Actions
	};
}



