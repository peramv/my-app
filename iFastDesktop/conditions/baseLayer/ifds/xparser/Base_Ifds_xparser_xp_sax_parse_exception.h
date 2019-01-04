#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_xparser_xp_sax_parse_exception : public CConditionObject
	{
	public:
		CBase_Ifds_xparser_xp_sax_parse_exception() { }
		~CBase_Ifds_xparser_xp_sax_parse_exception() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("XP_SAX_PARSE_EXCEPTION")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Request parsing failed: %SAXMSG%")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Zugeteilte Systematische Pläne sind für Clanplan-Konten nicht erlaubt.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Request parsing failed: %SAXMSG%")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Échec de demande d'analyse : %SAXMSG%")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Request parsing failed: %SAXMSG%")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Contact a support representative and report this message.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Communiquez avec un représentant technique et signalez ce message.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Contact a support representative and report this message.")); }
	};
}



