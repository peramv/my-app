#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_sin_missing_for_spouse : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_sin_missing_for_spouse() { }
		~CIFast_IFast_ifastcbo_err_sin_missing_for_spouse() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_SIN_MISSING_FOR_SPOUSE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("A Spousal entity must be set up with a valid SIN.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein Ehepartner-Objekt mit einer gültigen SIN muss erstellt werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Debe configurarse una entidad conyugal con un SIN válido")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'entité conjointe doit être réglée avec un NAS valide.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Een echtelijke eenheid moet worden ingesteld met een geldig SIN")); }

        // Actions
	};
}



