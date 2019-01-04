#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Infrastructure_dicbocore_err_invalid_use_of_official_group : public CConditionObject
	{
	public:
		CBase_Infrastructure_dicbocore_err_invalid_use_of_official_group() { }
		~CBase_Infrastructure_dicbocore_err_invalid_use_of_official_group() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_USE_OF_OFFICIAL_GROUP")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicbocore")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There is an internal problem.  Official group processing not allowed.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("There is an internal problem.  Official group processing not allowed.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Es gibt ein internes Problem.  Offizielle Gruppenverarbeitung ist nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Hay un problema interno.  No se permite el procesamiento por grupos oficial.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a un problème interne. Le traitement du groupe officiel n'est pas autorisé.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er is een intern probleem.  Officiële groepsverwerking is niet toegestaan")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



