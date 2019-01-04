#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_pac_index_locked_by_another_user : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_pac_index_locked_by_another_user() { }
		~CIFast_IFast_ifastdbrkr_err_pac_index_locked_by_another_user() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_PAC_INDEX_LOCKED_BY_ANOTHER_USER")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("PAC-Index record is locked by another user.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("PAC-Indexeintrag ist durch einen anderen Benutzer gesperrt")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("El registro de índice PAC está bloqueado por otro usuario")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("L'enregistrement d'indexation PAC est verrouillé par un autre utilisateur.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record VGC-Index is vergrendeld door een andere gebruiker")); }

        // Actions
	};
}



