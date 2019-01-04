#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastgui_gui_awd_not_setup : public CConditionObject
	{
	public:
		CIFast_IFast_ifastgui_gui_awd_not_setup() { }
		~CIFast_IFast_ifastgui_gui_awd_not_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_NOT_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Desktop application is not properly configured to interact with AWD on this workstation. Select another profile and report this message to a System Administrator if desktop application is required to interact with AWD on this workstation.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("DSTCCanada NT Desktop has not been properly configured to interact with AWD on this workstation. Select another profile and report this message to a System Administrator if DSTCCanada NT Desktop is required to interact with AWD on this workstation.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("DSTCCanada NT Desktop wurde nicht richtig für die Arbeit mit AWD auf dieser Workstation konfiguriert.. Wählen Sie ein anderes Profil und geben Sie diese Meldung an den Systemadministrator weiter, wenn DSTCCanada NT Desktop auf dieser Workstation mit AWD z")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("DSTCCanada NT Desktop no se ha configurado correctamente para que interactúe con AWD en esta estación de trabajo. Seleccione otro perfil e informe este mensaje a un administrador del sistema si se requiere que DSTC Canada NT Desktop interactúe con AWD en")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'application bureautique n'est pas bien configurée pour interagir avec AWD sur ce poste de travail. Choisissez un autre profil et signalez ce message à un administrateur de système si l'application bureautique est requise pour interagir avec AWD sur ce p")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Desktop DSTCCanada NT is niet juist geconfigureerd om voor de interactie met AWD op dit werkstation. Selecteer een ander profiel en meld dit bericht aan een systeembeheerder als de desktop DSTCCanada NT is vereist voor de interactie met AWD op dit werksta")); }

        // Actions
	};
}



