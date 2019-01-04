﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_gui_gui_err_domodal_failed : public CConditionObject
	{
	public:
		CBase_Ifds_gui_gui_err_domodal_failed() { }
		~CBase_Ifds_gui_gui_err_domodal_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("GUI_ERR_DOMODAL_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("gui")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem. DoModal failed for %DIALOG%.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem. DoModal failed for %DIALOG%.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Neues Konto kann mit einem Beendet- oder Gelöscht-Status nicht erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("There is an internal problem. DoModal failed for %DIALOG%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Échec de DoModal pour %DIALOG%.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem. DoModal is mislukt voor %DIALOG%.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht.")); }
	};
}



