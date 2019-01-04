﻿#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_mkt_index_detail_exists : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_mkt_index_detail_exists() { }
		~CIFast_IFast_ifastdbrkr_err_mkt_index_detail_exists() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MKT_INDEX_DETAIL_EXISTS")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Market Index Detail already exists.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Market Index Detail already exists.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Market Index Detail already exists.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Les détails de l'indice du marché existent déjà.")); }

        // Actions
	};
}



