#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_no_related_chui_functions : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_no_related_chui_functions() { }
		~CIFast_IFast_ifastdbrkr_err_no_related_chui_functions() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_RELATED_CHUI_FUNCTIONS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No related CHUI functions available.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("No related CHUI functions available.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine verwandten CHUI-Funktionen verfügbar")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No hay funciones CHUI relacionadas disponibles")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucune fonction CHUI n'est disponible.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er zijn geen verwante CHUI-functies beschikbaar")); }

        // Actions
	};
}



