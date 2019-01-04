#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_duplicate_mkt_index_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_duplicate_mkt_index_code() { }
		~CIFast_IFast_ifastcbo_err_duplicate_mkt_index_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_DUPLICATE_MKT_INDEX_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Duplicate Market Index Code.  (%CODE%).")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Duplicate Market Index Code.  (%CODE%).")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Duplicate Market Index Code.  (%CODE%).")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Copie de code d'indice du marché (%CODE%)")); }

        // Actions
	};
}



