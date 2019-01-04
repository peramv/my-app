#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicbocore_err_holiday_file : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicbocore_err_holiday_file() { }
		~CIFast_Infrastructure_dicbocore_err_holiday_file() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_HOLIDAY_FILE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem because a holiday file could not be read.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem because a holiday file could not be read.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem, da eine Urlaubsdatei nicht gelesen werden konnte.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno porque no se pudo leer un archivo de feriado.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne parce qu'un fichier de jour férié n'a pas pu être lu.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem omdat een vakantiebestand niet kon worden gelezen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report the following: check system for the iwsholid.dat file.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contact a support representative and report the following: check system for the iwsholid.dat file.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm Folgendes mit. Durchsuchen Sie das System nach der Datei „iwsholid.dat“")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report the following: check system for the iwsholid.dat file.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez le message suivant : vérifiez le système pour le fichier iwsholid.dat.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld het volgende: controleer het systeem op het bestand iwsholid.dat")); }
	};
}



