#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_search_forms_class : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_search_forms_class() { }
		~CIFast_IFast_ifastgui_gui_search_forms_class() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_SEARCH_FORMS_CLASS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Forms cannot create OLE class object.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Forms cannot create OLE class object.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Formulare können OLE-Klassenobjekt nicht erstellen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Los formularios no pueden crear objeto de clase OLE.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les formulaires ne peuvent créer un objet de classe OLE.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Formulieren kunnen geen OLE klasseobjedt maken")); }

        // Actions
	};
}



