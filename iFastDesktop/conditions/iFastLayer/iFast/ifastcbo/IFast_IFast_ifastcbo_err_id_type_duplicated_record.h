#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_id_type_duplicated_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_id_type_duplicated_record() { }
		~CIFast_IFast_ifastcbo_err_id_type_duplicated_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_ID_TYPE_DUPLICATED_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("There are duplicated records of %IDTYPE%.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Il y a des copies d'enregistrements de %IDTYPE%.")); }

        // Actions
	};
}



