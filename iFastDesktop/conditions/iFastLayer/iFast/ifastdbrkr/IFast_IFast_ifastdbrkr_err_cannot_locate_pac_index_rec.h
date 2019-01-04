#pragma once

#include "ConditionObject.h"

namespace CND
{
	class CIFast_IFast_ifastdbrkr_err_cannot_locate_pac_index_rec : public CConditionObject
	{
	public:
		CIFast_IFast_ifastdbrkr_err_cannot_locate_pac_index_rec() { }
		~CIFast_IFast_ifastdbrkr_err_cannot_locate_pac_index_rec() { }

	public:
		// General
		virtual DString GetConditionName() const { return DString(I_("ERR_CANNOT_LOCATE_PAC_INDEX_REC")); }
		virtual DString GetGroupName() const { return DString(I_("iFast")); }
		virtual DString GetModuleName() const { return DString(I_("ifastdbrkr")); }
		virtual int GetSeverity() const { return 6; }

		// Messages
		virtual DString GetMessage_EN_US() const { return DString(I_("Cannot locate PAC-Index record.")); }
		virtual DString GetMessage_DE_DE() const { return DString(I_("Kann PAC-Indexeintrag nicht lokalisieren")); }
		virtual DString GetMessage_ES_ES() const { return DString(I_("No se puede ubicar el registro de índice PAC")); }
		virtual DString GetMessage_FR_CA() const { return DString(I_("Impossible de repérer l'enregistrement d'indexation PAC.")); }
		virtual DString GetMessage_NL_NL() const { return DString(I_("Record VGC-Index is niet gevonden")); }

        // Actions
	};
}



