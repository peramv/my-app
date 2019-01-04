#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_xparser_err_too_many_usid_tags : public CConditionObject
	{
	public:
		CBase_Ifds_xparser_err_too_many_usid_tags() { }
		~CBase_Ifds_xparser_err_too_many_usid_tags() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TOO_MANY_USID_TAGS")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The XML‚ÌƒŠƒNƒGƒXƒg‚É‹–—e”ˆÈã‚Ìƒ†[ƒU[ƒZƒbƒVƒ‡ƒ“‚Ì‚h‚cƒ^ƒO‚ª•t‚¢‚Ä‚¢‚Ü‚·B")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die XML-Nachfrage hat zu viele Benutzersitzungs-ID-Kennzeichen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La solicitud XML tiene demasiadas etiquetas de identificación de sesión de usuarios")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le XML?????N?G?X?g???–—e”???????[?U[?Z?b?V???“???h?c?^?O??•t??????????B")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De XML-opdracht heeft te veel ID-tags voor gebruikerssessies")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("XML‚ÌƒŠƒNƒGƒXƒg‚ðŠm”F‚µ‚Ä‰º‚³‚¢B")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("XML‚ÌƒŠƒNƒGƒXƒg‚ðŠm”F‚µ‚Ä‰º‚³‚¢?B")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("XML?????N?G?X?g???m”F??????????B")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



