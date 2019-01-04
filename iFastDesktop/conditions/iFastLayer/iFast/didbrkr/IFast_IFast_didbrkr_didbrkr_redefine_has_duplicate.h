#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_didbrkr_didbrkr_redefine_has_duplicate : public CConditionObject
	{
	public:
		CIFast_IFast_didbrkr_didbrkr_redefine_has_duplicate() { }
		~CIFast_IFast_didbrkr_didbrkr_redefine_has_duplicate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_REDEFINE_HAS_DUPLICATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Spousal Contributor may only be set up for Spousal account types.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Spousal Contributor may only be set up for Spousal account types.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ehelicher Beitragender (06) kann nur für Ehe-Kontoarten erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El aportante conyugal (06) sólo puede configurarse para tipos de cuenta Conyugal.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un cotisant conjoint ne peut être réglé que pour les comptes de type conjoint.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Echtelijke bijdrager (06) kan alleen worden ingesteld voor Echtelijke accounttypes")); }

        // Actions
	};
}



