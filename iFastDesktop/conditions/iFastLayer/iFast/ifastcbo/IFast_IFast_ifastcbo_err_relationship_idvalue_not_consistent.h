#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_relationship_idvalue_not_consistent : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_relationship_idvalue_not_consistent() { }
		~CIFast_IFast_ifastcbo_err_relationship_idvalue_not_consistent() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_RELATIONSHIP_IDVALUE_NOT_CONSISTENT")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Relationship %RELATIONSHIP% requires consistent ID value for mandatory ID type.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("La relation %RELATIONSHIP% requiert une valeur de code compatible avec le type de code obligatoire.")); }

        // Actions
	};
}



