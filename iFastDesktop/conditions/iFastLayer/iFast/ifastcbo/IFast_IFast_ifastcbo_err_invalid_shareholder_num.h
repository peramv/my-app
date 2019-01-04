#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_invalid_shareholder_num : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_invalid_shareholder_num() { }
		~CIFast_IFast_ifastcbo_err_invalid_shareholder_num() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_INVALID_SHAREHOLDER_NUM")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Invalid shareholder number.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ungültige Aktionärsnummer.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Número de accionista no válido.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Numéro d'actionnaire invalide")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Ongeldig aandeelhoudersnummer")); }

        // Actions
	};
}



