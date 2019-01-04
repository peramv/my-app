#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_err_not_profile : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_err_not_profile() { }
		~CIFast_IFast_ifastgui_gui_err_not_profile() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ERR_NOT_PROFILE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("This Workstation's configuration does not support profile selection. The predetermined configuration file will be used.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("This Workstation's configuration does not support profile selection. The predetermined configuration file will be used.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die Konfiguration dieser Workstation unterstützt Profilauswahl nicht. Eine vorbestimmte Konfigurationsdatei wird verwendet.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La configuración de esta estación de trabajo no soporta la selección de perfiles. Se utilizará el archivo de configuración predeterminado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La configuration du poste de travail ne supporte pas la sélection de profil. Le fichier de configuration prédéterminée sera utilisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De configuratie van dit werkstation ondersteunt geen profielselectie. Het vooraf vastgestelde configuratiebestand wordt gebruikt")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact your System Administrator.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact your System Administrator.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an den Systemadministrator.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact your System Administrator.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec votre administrateur de système.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met uw systeembeheerder")); }
	};
}



