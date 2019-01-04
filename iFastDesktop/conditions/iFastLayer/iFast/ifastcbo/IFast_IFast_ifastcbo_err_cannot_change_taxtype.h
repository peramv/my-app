#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cannot_change_taxtype : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cannot_change_taxtype() { }
		~CIFast_IFast_ifastcbo_err_cannot_change_taxtype() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_CHANGE_TAXTYPE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Update to this tax type is not allowed.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Une mise à jour pour ce type d'imposition n'est pas autorisée.")); }

        // Actions
	};
}



