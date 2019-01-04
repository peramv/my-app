#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_didbrkr_didbrkr_read_size_failed : public CConditionObject
	{
	public:
		CIFast_IFast_didbrkr_didbrkr_read_size_failed() { }
		~CIFast_IFast_didbrkr_didbrkr_read_size_failed() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("DIDBRKR_READ_SIZE_FAILED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("didbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Wire Order Number must be numeric.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Wire Order Number must be numeric.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Telegrafische Bestellnummer muss nummerisch sein")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El campo de número de orden de transferencia cablegráfica debe ser numérico")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le numéro d'ordre électronique doit être numérique.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Nummer telegrafische order moet numeriek zijn")); }

        // Actions
	};
}



