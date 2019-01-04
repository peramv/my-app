#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_xparser_err_fielddetails_tag : public CConditionObject
	{
	public:
		CBase_Ifds_xparser_err_fielddetails_tag() { }
		~CBase_Ifds_xparser_err_fielddetails_tag() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_FIELDDETAILS_TAG")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The XML ‚ÌƒŠƒNƒGƒXƒg‚ÉŠÔˆá‚Á‚ÄƒtƒH[ƒ}ƒbƒg‚³‚ê‚½ƒtƒB[ƒ‹ƒhÚ×‚Ìƒ^ƒO‚ª•t‚¢‚Ä‚¢‚Ü‚·B")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Die XML-Nachfrage hat ein fehlerhaft formatiertes Felddetails-Kennzeichen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("La solicitud XML tiene una etiqueta fielddetails formateada no válida")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le XML ?????N?G?X?g???????????t?H[?}?b?g???????t?B[???h?????^?O??•t??????????B")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("De XML-opdracht heeft een slecht ingedeelde tag voor velddetails")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("XML‚ÌƒŠƒNƒGƒXƒg‚ðŠm”F‚µ‚Ä‰º‚³‚¢B")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("XML‚ÌƒŠƒNƒGƒXƒg‚ðŠm”F‚µ‚Ä‰º‚³‚¢?B")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("XML?????N?G?X?g???m”F??????????B")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("NULL")); }
	};
}



