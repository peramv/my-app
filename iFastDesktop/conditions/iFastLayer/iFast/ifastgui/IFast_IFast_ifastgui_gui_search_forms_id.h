﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_search_forms_id : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_search_forms_id() { }
		~CIFast_IFast_ifastgui_gui_search_forms_id() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_SEARCH_FORMS_ID")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Forms creation error.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Forms creation error.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Formularerstellungs-Fehler.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Error de creación de formularios.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Erreur de création de formulaires")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Fout bij maken van formulieren")); }

        // Actions
	};
}



