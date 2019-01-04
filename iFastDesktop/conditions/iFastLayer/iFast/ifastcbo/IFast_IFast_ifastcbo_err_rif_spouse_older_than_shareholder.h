#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_spouse_older_than_shareholder : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_spouse_older_than_shareholder() { }
		~CIFast_IFast_ifastcbo_err_rif_spouse_older_than_shareholder() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_SPOUSE_OLDER_THAN_SHAREHOLDER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Spouse cannot be older than shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ehepartner darf nicht älter als der Aktionär sein.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El cónyuge no puede ser mayor que el accionista.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le conjoint ne peut être plus âgé que l'actionnaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Echtgenoot of echtgenote kan niet ouder zijn dan aandeelhouder")); }

        // Actions
	};
}



