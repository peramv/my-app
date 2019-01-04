#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_search_encorr_dispatch : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_search_encorr_dispatch() { }
		~CIFast_IFast_ifastgui_gui_search_encorr_dispatch() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_SEARCH_ENCORR_DISPATCH")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("OLE Dispatch Error.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("OLE Dispatch Error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("OLE Verteiler-Fehler.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de despacho OLE.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur de répartition OLE")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("OLE-verzendingsfout")); }

        // Actions
	};
}



