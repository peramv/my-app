#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_xparser_err_no_action_type : public CConditionObject
	{
	public:
		CBase_Ifds_xparser_err_no_action_type() { }
		~CBase_Ifds_xparser_err_no_action_type() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_NO_ACTION_TYPE")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("xparser")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("The XML Action element doesn't have the attribute type")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Das XML-Aktions-Element hat den Attributtyp nicht.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El elemento XML Action no tiene el tipo de atributo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'élément d'action XML n'a pas le bon type d'attribut.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Het element XML Action heeft het kenmerktype niet")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("XML‚ÌƒŠƒNƒGƒXƒg‚ðŠm”F‚µ‚Ä‰º‚³‚¢B")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("XML‚ÌƒŠƒNƒGƒXƒg‚ðŠm”F‚µ‚Ä‰º‚³‚¢?B")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("XML?????N?G?X?g???m”F??????????B")); }
	};
}



