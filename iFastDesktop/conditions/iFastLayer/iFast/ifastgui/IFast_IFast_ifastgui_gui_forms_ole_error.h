#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_forms_ole_error : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_forms_ole_error() { }
		~CIFast_IFast_ifastgui_gui_forms_ole_error() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_FORMS_OLE_ERROR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("OLE Automation Error:%OLEMSG%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("OLE Automation Error:%OLEMSG%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("OLE-Automationsfehler: %OLEMSG%")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de automatización OLE:%OLEMSG%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur d'automatisation OLE : %OLEMSG%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("OLE-automatiseringsfout:%OLEMSG%")); }

        // Actions
	};
}



