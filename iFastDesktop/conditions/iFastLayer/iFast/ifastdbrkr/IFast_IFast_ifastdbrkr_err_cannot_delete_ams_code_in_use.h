#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cannot_delete_ams_code_in_use : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cannot_delete_ams_code_in_use() { }
		~CIFast_IFast_ifastdbrkr_err_cannot_delete_ams_code_in_use() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_DELETE_AMS_CODE_IN_USE")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot delete AMS Code that is in use.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Ein AMS-Code, der verwendet wird, kann nicht gelöscht werden.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede eliminar el código AMS que se está utilizando.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de supprimer un code de service de gestion de portefeuille en cours d'utilisation.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Gebruikte BBD-code kan niet worden gewist")); }

        // Actions
	};
}



