#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_security_violation : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_security_violation() { }
		~CIFast_IFast_ifastgui_gui_security_violation() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_SECURITY_VIOLATION")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("You don't have security rights to search for %MSG% using %MSGA%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Vous ne disposez pas des droits de securite pour %MSG% en utilisant %MSGA%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Sie haben keine Sicherheitsrechte, um nach %MSG% mit %MSGA% zu suchen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Usted no tiene derechos de seguridad para buscar %MSG% utilizando %MSGA%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Vous n'avez pas les droits de sécurité pour rechercher %MSG% en utilisant %MSGA%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("U hebt geen beveiligingsrechten om te zoeken naar %MSG% met %MSGA%")); }

        // Actions
	};
}



