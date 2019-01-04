#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_mkt_index_exists_with_index_code : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_mkt_index_exists_with_index_code() { }
		~CIFast_IFast_ifastdbrkr_err_mkt_index_exists_with_index_code() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_MKT_INDEX_EXISTS_WITH_INDEX_CODE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Market Index already exists with specified Index Code.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Market Index already exists with specified Index Code.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Market Index already exists with specified Index Code.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Un indice du marché existe déjà avec le code d'indexation spécifié.")); }

        // Actions
	};
}



