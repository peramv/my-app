#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_tr_not_allow_from_taxtype_to_taxtype : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_tr_not_allow_from_taxtype_to_taxtype() { }
		~CIFast_IFast_ifastcbo_err_tr_not_allow_from_taxtype_to_taxtype() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_TR_NOT_ALLOW_FROM_TAXTYPE_TO_TAXTYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Transfer not allowed from tax type %FROMTAXTYPE% to tax type %TOTAXTYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Transfert non autorisé de type d’impôt %FROMTAXTYPE% à type d’impôt %TOTAXTYPE%.")); }

        // Actions
	};
}



