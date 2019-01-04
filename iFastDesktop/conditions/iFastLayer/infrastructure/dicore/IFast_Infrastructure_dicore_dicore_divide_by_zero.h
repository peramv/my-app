#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_dicore_dicore_divide_by_zero : public CConditionObject
	{
	public:
		CIFast_Infrastructure_dicore_dicore_divide_by_zero() { }
		~CIFast_Infrastructure_dicore_dicore_divide_by_zero() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DICORE_DIVIDE_BY_ZERO")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("dicore")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Attempt to divide a MathString object by zero.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Attempt to divide a MathString object by zero.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Versuch, ein MathString-Objekt durch Null zu teilen.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Attempt to divide a MathString object by zero.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Tentative de division de l'objet de chaîne mathématique par zéro")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er wordt geprobeerd om een MathString-object door 0 te delen")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Don't do that.")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Don't do that.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Tun Sie das nicht.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("No haga eso.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Ne faites pas cela.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Doe dit niet")); }
	};
}



