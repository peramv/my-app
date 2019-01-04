#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastcbo_err_cannot_delete_fixed_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastcbo_err_cannot_delete_fixed_record() { }
		~CIFast_IFast_ifastcbo_err_cannot_delete_fixed_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_DELETE_FIXED_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastcbo")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot delete a fixed record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein festgelegter Eintrag kann nicht gelöscht werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede eliminar un registro fijo.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de supprimer un enregistrement fixe.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Vast record kan niet worden gewist")); }

        // Actions
	};
}



