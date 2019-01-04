#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cannot_delete_amscode_in_mstr : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cannot_delete_amscode_in_mstr() { }
		~CIFast_IFast_ifastdbrkr_err_cannot_delete_amscode_in_mstr() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_DELETE_AMSCODE_IN_MSTR")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot Delete - AMS Code exists in AMS Master list.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kann nicht gelöscht werden – AMS-Code existiert in AMS-Mstr-Liste.")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede eliminar. El código AMS existe en la lista AMS-Mstr.")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Suppression impossible – le code de service de gestion de portefeuille existe dans la liste principale du service de gestion de portefeuille.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Kan niet worden gewist - BBD-code bestaat in BBD-hoofdlijst")); }

        // Actions
	};
}



