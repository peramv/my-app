﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_xparser_xp_unknown_exception : public CConditionObject
	{
	public:
		CBase_Ifds_xparser_xp_unknown_exception() { }
		~CBase_Ifds_xparser_xp_unknown_exception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("XP_UNKNOWN_EXCEPTION")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  An unknown exception was caught.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Doppelte Kontonummer. Bitte überprüfen und neu eingeben.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  Se detectó una excepción desconocida.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Une exception inconnue a été détectée.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  Er is een onbekende exceptie aangetroffen.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Notifique de este mensaje a un representante de soporte técnico.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht.")); }
	};
}



