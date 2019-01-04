#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_dicore_dicore_profile_alread_exists : public CConditionObject
	{
	public:
		CBase_Ifds_dicore_dicore_profile_alread_exists() { }
		~CBase_Ifds_dicore_dicore_profile_alread_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_PROFILE_ALREAD_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The XML ‚ÌƒŠƒNƒGƒXƒg‚É‚ÌƒRƒ“ƒeƒCƒ“ƒi[‚h‚cƒ^ƒO‚ª‘½‰ß‚¬‚éB")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die XML-Nachfrage hat zu viele Container-ID-Kennzeichen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La solicitud XML tiene demasiadas etiquetas de identificación de contenedor")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le XML ?????N?G?X?g?????R?“?e?C?“?i[?h?c?^?O??‘???????B")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De XML-opdracht heeft te veel ID-tags voor containers")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("XML‚ÌƒŠƒNƒGƒXƒg‚ðŠm”F‚µ‚Ä‰º‚³‚¢B")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("XML‚ÌƒŠƒNƒGƒXƒg‚ðŠm”F‚µ‚Ä‰º‚³‚¢?B")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("XML?????N?G?X?g???m”F??????????B")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



