#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_Infrastructure_ifastdbrkr_err_controls_name_record_entityid_not_found : public CConditionObject
	{
	public:
		CIFast_Infrastructure_ifastdbrkr_err_controls_name_record_entityid_not_found() { }
		~CIFast_Infrastructure_ifastdbrkr_err_controls_name_record_entityid_not_found() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CONTROLS_NAME_RECORD_ENTITYID_NOT_FOUND")); }
		virtual DString GetGroupName() const { return DString(I_("Infrastructure")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

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
		virtual DString GetAction_ES_ES() const { return DString(I_("Don't do that.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Ne faites pas cela.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Doe dit niet")); }
	};
}



