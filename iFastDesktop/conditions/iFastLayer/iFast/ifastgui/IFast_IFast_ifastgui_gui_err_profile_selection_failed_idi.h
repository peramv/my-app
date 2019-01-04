#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_err_profile_selection_failed_idi : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_err_profile_selection_failed_idi() { }
		~CIFast_IFast_ifastgui_gui_err_profile_selection_failed_idi() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ERR_PROFILE_SELECTION_FAILED_IDI")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Profile selection has failed. \n%QUEUE1%.\n Select another Profile.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Profile selection has failed. \n%QUEUE1%.\n Select another Profile.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Profilauswahl ist fehlgeschlagen. \n%QUEUE1%.\n Wählen Sie ein anderes Profil.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Ha fallado la selección de perfil. \n%QUEUE1%.\n Seleccione otro perfil.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La sélection de profil a échoué. \n%QUEUE1%.\n Sélectionnez un autre profil.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Profielselectie is mislukt! \n%QUEUE1%.\n Selecteer een ander profiel")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Report this message to a System Administrator")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Communiquez ce message a l'administrateur systeme")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Geben Sie diese Meldung an einen Systemadministrator weiter")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Report this message to a System Administrator")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Signalez ce message à un administrateur de système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Meld dit bericht aan een systeembeheerder")); }
	};
}



