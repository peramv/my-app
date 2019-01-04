#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_mkt_index_rec_locked : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_mkt_index_rec_locked() { }
		~CIFast_IFast_ifastdbrkr_err_mkt_index_rec_locked() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MKT_INDEX_REC_LOCKED")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("MktIndexDetail record is locked, try again later.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("MktIndexDetail record is locked, try again later.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("MktIndexDetail record is locked, try again later.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement des détails de l'indice du marché est verrouillé, réessayez plus tard.")); }

        // Actions
	};
}



