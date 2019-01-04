#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cannot_add_new_cif : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cannot_add_new_cif() { }
		~CIFast_IFast_ifastcbo_err_cannot_add_new_cif() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_ADD_NEW_CIF")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot add a CIF id. This is system generated.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible d'ajouter un code de FRC. Il est généré par le système.")); }

        // Actions
	};
}



