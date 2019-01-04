#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unable_to_delete_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unable_to_delete_record() { }
		~CIFast_IFast_ifastdbrkr_err_unable_to_delete_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_DELETE_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to delete record.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to delete record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eintrag kann nicht gelöscht werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible eliminar registro")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de supprimer l'enregistrement")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record kon niet worden gewist")); }

        // Actions
	};
}



