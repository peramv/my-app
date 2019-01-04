#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_rif_bad_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_rif_bad_record() { }
		~CIFast_IFast_ifastcbo_err_rif_bad_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RIF_BAD_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 4; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Only Good records can be modified.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Only Good records can be modified.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Nur sofort verfügbare Einträge können geändert werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Sólo pueden modificase los registros válidos")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Seuls les enregistrements Bons peuvent être modifiés.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Er kunnen alleen Goed-records worden gewijzigd")); }

        // Actions
	};
}



