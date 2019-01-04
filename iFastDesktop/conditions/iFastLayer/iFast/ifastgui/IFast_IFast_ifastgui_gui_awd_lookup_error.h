#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_awd_lookup_error : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_awd_lookup_error() { }
		~CIFast_IFast_ifastgui_gui_awd_lookup_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_LOOKUP_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to perform AWD History process.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Historien-Vorgang kann nicht durchgeführt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible ejecutar el proceso de Historial de AWD.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'exécuter le processus de l'historique AWD.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("AWD-historieverwerking kon niet worden uitgevoerd")); }

        // Actions
	};
}



