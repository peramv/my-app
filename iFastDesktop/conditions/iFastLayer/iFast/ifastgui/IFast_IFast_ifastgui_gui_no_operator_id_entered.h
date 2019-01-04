#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_no_operator_id_entered : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_no_operator_id_entered() { }
		~CIFast_IFast_ifastgui_gui_no_operator_id_entered() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_NO_OPERATOR_ID_ENTERED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("No operator ID entered.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Aucune identification d'operateur n'a ete saisie")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Keine Operator-ID eingegeben")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se introdujo la identificación del operador")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Aucun code d'opérateur n'a été saisi.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is geen operator-ID opgegeven")); }

        // Actions
	};
}



