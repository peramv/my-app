#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_mgmtco_err_no_management_companies_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_mgmtco_err_no_management_companies_found() { }
		~CIFast_Infrastructure_ifastgui_gui_mgmtco_err_no_management_companies_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_MGMTCO_ERR_NO_MANAGEMENT_COMPANIES_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is a severe problem with SYSTRAN.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is a severe problem with SYSTRAN.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein schweres Problem in SYSTRAN.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema grave con SYSTRAN.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un grave problème avec SYSTRAN.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een ernstig probleem met SYSTRAN")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact the TA2000 Support Center and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact the TA2000 Support Center and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an das TA2000-Support-Center und teilen Sie die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact the TA2000 Support Center and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec le service d'assistance TA2000 et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met het TA2000 Support Center en meld dit bericht")); }
	};
}



