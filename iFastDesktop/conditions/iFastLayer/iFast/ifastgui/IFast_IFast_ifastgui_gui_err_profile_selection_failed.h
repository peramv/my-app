#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_err_profile_selection_failed : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_err_profile_selection_failed() { }
		~CIFast_IFast_ifastgui_gui_err_profile_selection_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ERR_PROFILE_SELECTION_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Profile selection has failed.  Select another Profile.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Profile selection has failed.  Select another Profile.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Profilauswahl ist fehlgeschlagen.  Wählen Sie ein anderes Profil.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Ha fallado la selección de perfil.  Seleccione otro perfil.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La sélection de profil a échoué. Sélectionnez un autre profil.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Profielselectie is mislukt!  Selecteer een ander profiel")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Report this message to a System Administrator")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Communiquez ce message a l'administrateur systeme")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie diese Meldung an einen Systemadministrator weiter")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Report this message to a System Administrator")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Signalez ce message à un administrateur de système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Meld dit bericht aan een systeembeheerder")); }
	};
}



