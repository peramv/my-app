﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CBase_Ifds_didbrkr_didbrkr_redefine_has_duplicate : public CConditionObject
	{
	public:
		CBase_Ifds_didbrkr_didbrkr_redefine_has_duplicate() { }
		~CBase_Ifds_didbrkr_didbrkr_redefine_has_duplicate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_REDEFINE_HAS_DUPLICATE")); }
		virtual DString GetGroupName() const { return DString(I_("ifds")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("CBO %NAME% not defined in the current context.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ehelicher Beitragender (06) kann nur für Ehe-Kontoarten erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("CBO %NAME% not defined in the current context.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'optimisation de coûts %NAME% n'est pas définie dans le contexte actuel.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("CBO %NAME% not defined in the current context.")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Please consult the API documentation.")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Veuillez consulter la documentation API.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Please consult the API documentation.")); }
	};
}



