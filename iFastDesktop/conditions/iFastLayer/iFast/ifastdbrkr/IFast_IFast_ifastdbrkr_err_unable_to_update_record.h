#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_unable_to_update_record : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_unable_to_update_record() { }
		~CIFast_IFast_ifastdbrkr_err_unable_to_update_record() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_UNABLE_TO_UPDATE_RECORD")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 7; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Unable to update record.")); }
		virtual DString GetMessage_FR_FR() const { return DString(I_("Unable to update record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Eintrag kann nicht aktualisiert werden")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("Imposible actualizar registro")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de mettre à jour l'enregistrement.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record kon niet worden bijgewerkt")); }

        // Actions
		virtual DString GetAction_EN_US() const { return DString(I_("Try later")); }
		virtual DString GetAction_FR_FR() const { return DString(I_("Try later")); }
		virtual DString GetAction_DE_DE() const { return DString(I_("Versuchen Sie es später noch einmal")); }
		virtual DString GetAction_ES_ES() const { return DString(I_("Try later")); }
		virtual DString GetAction_FR_CA() const { return DString(I_("Essayez plus tard.")); }
		virtual DString GetAction_NL_NL() const { return DString(I_("Probeer het later opnieuw")); }
	};
}



