#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_spouse_older_birthdate : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_spouse_older_birthdate() { }
		~CIFast_IFast_ifastcbo_err_rif_spouse_older_birthdate() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_SPOUSE_OLDER_BIRTHDATE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 5; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Spouse is older than shareholder.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Spouse should  not be older than shareholder.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ehepartner ist älter als der Aktionär.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El cónyuge es mayor que el accionista.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Le conjoint est plus âgé que l'actionnaire.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Echtgenoot of echtgenote is ouder dan aandeelhouder")); }

        // Actions
	};
}



