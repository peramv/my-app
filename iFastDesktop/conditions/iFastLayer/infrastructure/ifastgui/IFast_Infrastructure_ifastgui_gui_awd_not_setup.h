﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastgui_gui_awd_not_setup : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastgui_gui_awd_not_setup() { }
		~CIFast_Infrastructure_ifastgui_gui_awd_not_setup() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_AWD_NOT_SETUP")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastgui")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem because invalid data was passed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem because invalid data was passed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein internes Problem besteht, da ungültige Daten weitergegeben wurden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno porque se aprobaron datos no válidos.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne parce que des données invalides ont été saisies.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem omdat er ongeldige gegevens zijn doorgegeven")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



