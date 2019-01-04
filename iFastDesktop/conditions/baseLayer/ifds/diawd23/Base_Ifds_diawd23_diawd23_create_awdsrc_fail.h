#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_diawd23_diawd23_create_awdsrc_fail : public CConditionObject
	{
	public:
		CBase_Ifds_diawd23_diawd23_create_awdsrc_fail() { }
		~CBase_Ifds_diawd23_diawd23_create_awdsrc_fail() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIAWD23_CREATE_AWDSRC_FAIL")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("diawd23")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Field %NAME% not defined in the current context.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Mindestens ein aktives Kontoinhaber (01)-Objekt muss für die Kunden-Konto-Zuweisung erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Field %NAME% not defined in the current context.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le champ %NAME% n'est pas défini dans le contexte actuel.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Field %NAME% not defined in the current context.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez consulter la documentation API.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Please consult the API documentation.")); }
	};
}



