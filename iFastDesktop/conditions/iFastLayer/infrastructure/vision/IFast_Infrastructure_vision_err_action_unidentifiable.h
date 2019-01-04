#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_vision_err_action_unidentifiable : public CConditionObject
	{
	public:
		CIFast_Infrastructure_vision_err_action_unidentifiable() { }
		~CIFast_Infrastructure_vision_err_action_unidentifiable() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ACTION_UNIDENTIFIABLE")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("vision")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("AWD logoff was not successful.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("AWD logoff was not successful.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("AWD-Abmeldung war nicht erfolgreich.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La desconexión de AWD no fue exitosa.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec d'ouverture de session AWD")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Afmelden bij AWD is niet gelukt")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Contactez un representant en assitance technique et communiquez-lui ce message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Wenden Sie sich an einen Support-Mitarbeiter und teilen Sie ihm die Meldung mit.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Neem contact op met een supportmedewerker en meld dit bericht")); }
	};
}



