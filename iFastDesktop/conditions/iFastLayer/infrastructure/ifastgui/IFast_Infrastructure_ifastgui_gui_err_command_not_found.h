#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_err_command_not_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_err_command_not_found() { }
		~CIFast_Infrastructure_ifastgui_gui_err_command_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ERR_COMMAND_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Update invalid for %LABEL%")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Update invalid for '^'")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Aktualisierungen sind nur auf dem MFL-Management-System möglich!")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("¡Sólo se permiten actualizaciones en el sistema de administración MFL!")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Mise à jour invalide pour %LABEL%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Bijwerken ongeldig voor %LABEL%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Verify that event is valid.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Verify that event is valid.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Vérifiez que l'événement est valide.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Controleer of de gebeurtenis geldig is")); }
	};
}



