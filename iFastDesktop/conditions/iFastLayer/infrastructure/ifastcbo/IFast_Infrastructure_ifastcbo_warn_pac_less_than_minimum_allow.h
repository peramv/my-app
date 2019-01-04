#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastcbo_warn_pac_less_than_minimum_allow : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastcbo_warn_pac_less_than_minimum_allow() { }
		~CIFast_Infrastructure_ifastcbo_warn_pac_less_than_minimum_allow() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("WARN_PAC_LESS_THAN_MINIMUM_ALLOW")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Work Order CBE Key was not found.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Work Order CBE Key was not found.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Arbeitsauftrag-CBE-Schlüssel nicht gefunden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se encontró la clave CBE de la orden de trabajo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La clé CBE de l'ordre électronique est introuvable.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Werkorder CBE-sleutel is niet gevonden")); }

        // Actions
	};
}



